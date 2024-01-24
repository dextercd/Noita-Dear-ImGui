import glob
import sys
import itertools

import more_itertools
import clang
import clang.cindex
from clang.cindex import CursorKind, Type

from docgen.definitions import EnumDef, FunctionSignature, FunctionDef, FileDefinition
from docgen.type_conv import clang_to_lua

# TODO:
# - usertype
# - integrate into build system
# - command line arguments

# LibClang docs: https://libclang.readthedocs.io/en/latest/index.html

def check(c):
    if not c:
        raise Exception("Check failed")


def ci(cursor, indent=""):
    """cursor info"""
    loc = cursor.location
    coord = f"[{loc.file}:{loc.line}:{loc.column}]".ljust(55)
    parts = [
        f"{coord}{indent}",
        cursor.spelling,
        cursor.kind,
        verbose_token_text(cursor),
    ]
    return " ".join(str(p) for p in parts if str(p))


def print_tree(cursor, indent=0):
    print(ci(cursor, "  " * indent))
    for child in cursor.get_children():
        print_tree(child, indent + 1)


def string_literal_value(cursor):
    for c in cursor.walk_preorder():
        if c.kind == CursorKind.STRING_LITERAL:
            return c.spelling.removeprefix('"').removesuffix('"')

def tokens(cursor):
    return [t.spelling for t in cursor.get_tokens()]

def token_text(cursor):
    return "".join(tokens(cursor))

def verbose_token_text(cursor):
    return " ".join(tokens(cursor))


def parse_enum(cursor) -> EnumDef:
    arguments = list(cursor.get_arguments())
    enum = EnumDef(string_literal_value(arguments[0]))
    for name_expr, value_expr in more_itertools.grouper(arguments[1:], 2):
        enum_def = next(value_expr.get_children()).get_definition()
        enum.add_item(string_literal_value(name_expr), enum_def.enum_value)

    return enum


def parse_brace_enum(cursor) -> EnumDef:
    arguments = list(cursor.get_arguments())
    enum = EnumDef(string_literal_value(arguments[0]))
    for enum_list in arguments[1].walk_preorder():
        if enum_list.kind == CursorKind.INIT_LIST_EXPR:
            for item in enum_list.get_children():
                name_expr, value_expr = item.get_children()
                enum_def = value_expr.get_definition()
                enum.add_item(string_literal_value(name_expr), enum_def.enum_value)

            break

    return enum


def parse_lambda(cursor) -> FunctionSignature:
    decl = cursor.type.get_declaration()
    types = [
        cursor.type,
        cursor.type.get_canonical(),
    ]

    def_ = cursor.type.get_declaration()

    call_method = next(def_.get_children())
    assert call_method.spelling == "operator()"

    parameters = [
        (param.spelling, param.type)
        for param in call_method.get_children()
        if param.kind == CursorKind.PARM_DECL
    ]

    return FunctionSignature(
        return_type=call_method.result_type,
        parameters=parameters
    )


def parse_resolve(cursor) -> FunctionSignature:
    children = list(cursor.get_children())
    check(len(children) == 2)
    declref = children[0]
    func = next(children[1].get_children())
    declaration = func.referenced
    assert declaration.kind == CursorKind.FUNCTION_DECL

    parameters = [
        (param.spelling, param.type)
        for param in declaration.get_children()
        if param.kind == CursorKind.PARM_DECL
    ]

    return FunctionSignature(
        return_type=declaration.result_type,
        parameters=parameters,
    )


def parse_overload(cursor) -> list[FunctionSignature]:
    overloads = list(cursor.get_arguments())
    signatures = []
    for overload_ in overloads:
        assert overload_.kind == CursorKind.UNEXPOSED_EXPR
        overload = next(overload_.get_children())
        if overload.kind == CursorKind.LAMBDA_EXPR:
            signatures.append(parse_lambda(overload))
        else:
            try:
                signatures.append(parse_resolve(overload))
            except Exception as e:
                raise

    return signatures


dont_parse_funcs = {
    "BeginChild"
}


def parse_add_function(cursor) -> FunctionDef:
    arguments = list(cursor.get_arguments())
    check(len(arguments) == 2)

    func_name = string_literal_value(arguments[0])
    if func_name in dont_parse_funcs:
        return None

    func = FunctionDef(func_name, signatures=[])
    bound = arguments[1]
    assert bound.kind == CursorKind.UNEXPOSED_EXPR

    bound_child = next(bound.get_children())

    if bound_child.kind == CursorKind.LAMBDA_EXPR:
        func.signatures = [parse_lambda(bound_child)]
    elif bound_child.kind == CursorKind.CALL_EXPR:
        bound_args = list(bound_child.get_children())
        match tokens(bound_child):
            case ["sol", "::", "resolve", *_]:
                func.signatures = [parse_resolve(bound_child)]
            case ["sol", "::", "overload", *_]:
                func.signatures = parse_overload(bound_child)
            case an:
                print("UNKNOWN!!: ", an)
    else:
        raise Exception(f"Unexpected binding {bound.kind}")

    return func


index = clang.cindex.Index.create(True)
compile_db = clang.cindex.CompilationDatabase.fromDirectory("clang-build")


def get_unit(filepath):
    commands = list(compile_db.getCompileCommands(filepath))
    assert len(commands) == 1
    command = commands[0]
    args = list(command.arguments)
    try:
        # LibClang doesn't like the '--', '<file name>' that's at the end of the args
        file_start = args.index("--")
        args = args[0:file_start]
    except ValueError:
        pass

    # Not sure why this is needed
    args += ["-isystem", "/usr/lib/gcc/i686-w64-mingw32/13.1.0/include/"]

    unit = index.parse(filepath, args=args)

    diags = False
    for d in unit.diagnostics:
        print(d)
        diags = True

    return unit


def print_unit(unit, filepath):
    for cursor in unit.cursor.get_children():
        if not cursor.location.file or cursor.location.file.name != filepath:
            continue

        print_tree(cursor)
        continue


def get_definitions(unit, filepath):
    file_definitions: list[FileDefinition] = []

    for cursor in unit.cursor.walk_preorder():
        if not cursor.location.file or cursor.location.file.name != filepath:
            continue

        if cursor.kind != CursorKind.CALL_EXPR:
            continue

        mem_ref = next(cursor.get_children(), None)
        if not mem_ref or mem_ref.kind != CursorKind.MEMBER_REF_EXPR:
            continue

        def_ = None
        match tokens(mem_ref):
            case [obj, _, "new_enum"]:
                def_ = parse_enum(cursor)

            case [obj, _, "new_enum", "<", *_]:
                def_ = parse_brace_enum(cursor)

            case [obj, _, "set_function"]:
                def_ = parse_add_function(cursor)

        if def_:
            file_definitions.append(
                FileDefinition(
                    filepath=filepath,
                    object_name=obj,
                    definition=def_
                )
            )

    return file_definitions


# Debugging code
if False:
    p = "src/lua_features/imgui_keyboard_input.cpp"
    unit = get_unit(p)
    #print_unit(unit, "src/lua_features/imgui_keyboard_input.cpp")
    get_definitions(unit, p)
    sys.exit(0)


all_definitions = []
for p in glob.glob("src/lua_features/*.cpp"):
    print("Processing", p)
    unit = get_unit(p)
    all_definitions.extend(get_definitions(unit, p))


doc_file = open("imguidoc/imgui_definitions.lua", "w")


def docout(*args, **kwargs):
    kwargs["file"] = doc_file
    return print(*args, **kwargs)

docout("""\
---@meta _
error("This is just an definitions file, it's not actually runnable Lua code.")

---@class ImPlot
local ImPlot = {}

---@class ImPlot.PlotPoint
---@field x number
---@field y number
ImPlot.PlotPoint = {}

---@param x number
---@param y number
---@return ImPlot.PlotPoint
function ImPlot.PlotPoint.new(x, y) end


---@class ImPlot.PlotRange
---@field Min number
---@field Max number
ImPlot.PlotRange = {}

---@param min number
---@param max number
---@return ImPlot.PlotRange
function ImPlot.PlotRange.new(min, max) end


---@class ImPlot.PlotRect
---@field X ImPlot.PlotRange
---@field Y ImPlot.PlotRange
ImPlot.PlotRect = {}

---@param x_min number
---@param x_max number
---@param y_min number
---@param y_max number
---@return ImPlot.PlotRect
function ImPlot.PlotRect.new(x_min, x_max, y_min, y_max) end


---@class ImGui
---@field implot ImPlot
local ImGui = {}

---@class ImGui.GuiIO
---@class ImGui.Font


---@class ImGui.ListClipper
---@field DisplayStart integer
---@field DisplayEnd integer
ImGui.ListClipper = {}

---@return ImGui.ListClipper
function ImGui.ListClipper.new() end

---@param items_count integer
---@param items_height number?
function ImGui.ListClipper:Begin(items_count, items_height) end

function ImGui.ListClipper:End() end

---@return boolean
function ImGui.ListClipper:Step() end

---@param item_min integer
---@param item_max integer
function ImGui.ListClipper.IncludeItemsByIndex(item_min, item_max) end

---@param item_index integer
function ImGui.ListClipper.IncludeItemsByIndex(item_index) end


---@class ImGui.Style
---@field Alpha number
---@field DisabledAlpha number
---@field WindowPadding_x number
---@field WindowPadding_y number
---@field WindowRounding number
---@field WindowBorderSize number
---@field WindowMinSize_x number
---@field WindowMinSize_y number
---@field WindowTitleAlign_x number
---@field WindowTitleAlign_y number
---@field WindowMenuButtonPosition Dir
---@field ChildRounding number
---@field ChildBorderSize number
---@field PopupRounding number
---@field PopupBorderSize number
---@field FramePadding_x number
---@field FramePadding_y number
---@field FrameRounding number
---@field FrameBorderSize number
---@field ItemSpacing_x number
---@field ItemSpacing_y number
---@field ItemInnerSpacing_x number
---@field ItemInnerSpacing_y number
---@field CellPadding_x number
---@field CellPadding_y number
---@field TouchExtraPadding_x number
---@field TouchExtraPadding_y number
---@field IndentSpacing number
---@field ColumnsMinSpacing number
---@field ScrollbarSize number
---@field ScrollbarRounding number
---@field GrabMinSize number
---@field GrabRounding number
---@field LogSliderDeadzone number
---@field TabRounding number
---@field TabBorderSize number
---@field TabMinWidthForCloseButton number
---@field TabBarBorderSize number
---@field TableAngledHeadersAngle number
---@field ColorButtonPosition Dir
---@field ButtonTextAlign_x number
---@field ButtonTextAlign_y number
---@field SelectableTextAlign_x number
---@field SelectableTextAlign_y number
---@field SeparatorTextBorderSize number
---@field SeparatorTextAlign_x number
---@field SeparatorTextAlign_y number
---@field SeparatorTextPadding_x number
---@field SeparatorTextPadding_y number
---@field DisplayWindowPadding_x number
---@field DisplayWindowPadding_y number
---@field DisplaySafeAreaPadding_x number
---@field DisplaySafeAreaPadding_y number
---@field DockingSeparatorSize number
---@field MouseCursorScale number
---@field AntiAliasedLines number
---@field AntiAliasedLinesUseTex number
---@field AntiAliasedFill boolean
---@field CurveTessellationTol number
---@field CircleTessellationMaxError number
---@field Color fun(index: integer): (number, number, number, number)?


---@class ImGui.ColumnSortSpecs
---@field ColumnUserID integer
---@field ColumnIndex integer
---@field SortOrder integer
---@field SortDirection SortDirection


---@class ImGui.TableSortSpecs
---@field Specs ImGui.ColumnSortSpecs[]

---@class ImGui.LuaImage
---@field path string
---@field width integer Readonly width of image
---@field height integer Readonly height of image

---@class ModSpec
---@field mod string Name of the mod that wants to use imgui.
---@field version string Version of imgui that the mod requires. e.g. "1.0.0"

---Grants access to the imgui bindings
---@param modspec ModSpec
---@return ImGui
---@nodiscard
function load_imgui(modspec) end


---@param str_id string
---@return boolean
function ImGui.BeginChild(str_id) end

---@param str_id string
---@param size_x number
---@param size_y number
---@return boolean
function ImGui.BeginChild(str_id, size_x, size_y) end

---@param str_id string
---@param size_x number
---@param size_y number
---@param child_flags ChildFlags
---@return boolean
function ImGui.BeginChild(str_id, size_x, size_y, child_flags) end

---@param str_id string
---@param size_x number
---@param size_y number
---@param child_flags ChildFlags
---@param flags WindowFlags
---@return boolean
function ImGui.BeginChild(str_id, size_x, size_y, child_flags, flags) end

---Only available when load_imgui is called with a version number below 1.17.0
---@deprecated
---@param str_id string
---@param size_x number
---@param size_y number
---@param border boolean
---@return boolean
function ImGui.BeginChild(str_id, size_x, size_y, border) end

---Only available when load_imgui is called with a version number below 1.17.0
---@deprecated
---@param str_id string
---@param size_x number
---@param size_y number
---@param border boolean
---@param flags WindowFlags
---@return boolean
function ImGui.BeginChild(str_id, size_x, size_y, border, flags) end
""")

object_to_class_mapping = {
    "imgui": "ImGui",
    "implot": "ImPlot",
}

def param_name(name):
    """Bindings use some parameter names that are Lua keywords. Translate them.
    """
    if name == "repeat":
        return "repeat_"

    return name

for file_def in all_definitions:
    def_ = file_def.definition
    class_ = object_to_class_mapping[file_def.object_name]

    docout()
    docout()

    if isinstance(def_, EnumDef):
        docout(f"---@enum {def_.name}")
        docout(f"{class_}.{def_.name} = {{")
        for name, value in def_.items.items():
            docout(f"    {name} = {value},")
        docout("}")

    if isinstance(def_, FunctionDef):
        first = True
        for sig in def_.signatures:

            if not first:
                # Little bit of spacing between the different overloads
                docout()
            first = False

            params = [
                (name, clang_to_lua(type_))
                for name, type_ in sig.parameters
            ]
            # Exclude none types
            params = [p for p in params if p[1]]

            for name, type_ in params:
                docout(f"---@param {param_name(name)} {type_}")

            ret_types = clang_to_lua(sig.return_type)
            if not isinstance(ret_types, list):
                ret_types = [ret_types]

            for rt in ret_types:
                if rt:
                    docout(f"---@return {rt}")

            param_string = ", ".join(param_name(name) for name, _ in params)

            docout(f"function {class_}.{def_.name}({param_string}) end")
