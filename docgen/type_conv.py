from clang.cindex import TypeKind, Type


def enum_name(name):
    if name.startswith("ImGui"):
        return name.removeprefix("ImGui")

    return name.removeprefix("Im")


def clang_to_lua(typ: Type):
    # ImPlot uses typedefs instead of real enums in its parameters.
    if typ.kind == TypeKind.TYPEDEF:
        if (
            typ.spelling != "ImGuiID"
            and (
                typ.spelling == "ImAxis"
                or typ.spelling.startswith("ImGui")
                or typ.spelling.startswith("ImPlot")
            )
        ):
            return enum_name(typ.spelling)

    if (
        typ.kind == TypeKind.LVALUEREFERENCE or
        typ.kind == TypeKind.RVALUEREFERENCE
    ):
        typ = typ.get_pointee()

    match typ.kind:
        case TypeKind.VOID: return None
        case TypeKind.BOOL: return "boolean"
        case TypeKind.CHAR_U: return "integer"
        case TypeKind.UCHAR: return "integer"
        case TypeKind.CHAR16: return "integer"
        case TypeKind.CHAR32: return "integer"
        case TypeKind.USHORT: return "integer"
        case TypeKind.UINT: return "integer"
        case TypeKind.ULONG: return "integer"
        case TypeKind.ULONGLONG: return "integer"
        case TypeKind.UINT128: return "integer"
        case TypeKind.CHAR_S: return "integer"
        case TypeKind.SCHAR: return "integer"
        case TypeKind.WCHAR: return "integer"
        case TypeKind.SHORT: return "integer"
        case TypeKind.INT: return "integer"
        case TypeKind.LONG: return "integer"
        case TypeKind.LONGLONG: return "integer"
        case TypeKind.INT128: return "integer"
        case TypeKind.FLOAT: return "number"
        case TypeKind.DOUBLE: return "number"
        case TypeKind.LONGDOUBLE: return "number"
        case TypeKind.NULLPTR: return None
        case TypeKind.FLOAT128: return "number"
        case TypeKind.HALF: return "number"
        case TypeKind.ENUM:
            return enum_name(typ.spelling)
        case TypeKind.POINTER:
            pointee = typ.get_pointee()
            if pointee.kind == TypeKind.CHAR_S and pointee.is_const_qualified():
                return "string"

            return clang_to_lua(pointee)
        case TypeKind.RECORD | TypeKind.ELABORATED:
            spelling = typ.spelling
            if spelling.startswith("std::vector<"):
                elem = typ.get_template_argument_type(0)
                return f"{clang_to_lua(elem)}[]"

            if spelling.startswith("std::optional<"):
                vt = typ.get_template_argument_type(0)
                return f"{clang_to_lua(vt)}?"

            if spelling.startswith("std::tuple<"):
                types = [
                    typ.get_template_argument_type(i)
                    for i in range(typ.get_num_template_arguments())
                ]
                return [clang_to_lua(t) for t in types]

            if spelling == "ImPlotPoint":
                return "ImPlot.PlotPoint"

            if spelling == "ImPlotRange":
                return "ImPlot.PlotRange"

            if spelling == "ImPlotRect":
                return "ImPlot.PlotRect"

            if spelling == "sol::basic_table_core<false, sol::basic_reference<false>>":
                return "table"

            if spelling == "sol::basic_object<sol::basic_reference<false>>":
                return "any"

            if spelling == "std::basic_string<char>":
                return "string"

            if spelling == "std::basic_string_view<char>":
                return "string"

            if spelling == "sol::this_state":
                return None

            if spelling == "ImGuiIO":
                return "ImGui.GuiIO"

            if spelling == "ImFont":
                return "ImGui.Font"

            if spelling == "ImGuiStyle":
                return "ImGui.Style"

    canonical = typ.get_canonical()
    if canonical != typ:
        return clang_to_lua(canonical)

    print(f"--Unsuported type: {typ}")
    print(f"--Spelling: {typ.spelling}")
    print(f"--Kind: {typ.kind}")
    return "any"
