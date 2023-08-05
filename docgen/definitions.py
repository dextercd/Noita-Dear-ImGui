from dataclasses import dataclass, field

from clang.cindex import Type

@dataclass
class EnumDef:
    name: str
    items: dict[str, int] = field(default_factory=list)

    def __init__(self, name):
        self.name = name
        self.items = {}

    def add_item(self, item_name, value):
        self.items[item_name] = value

    def __repr__(self):
        return "EnumDef(%r) %r" % (self.name, self.items)

@dataclass
class FunctionSignature:
    return_type: Type
    parameters: list[tuple[str, Type]]


@dataclass
class FunctionDef:
    name: str
    signatures: list[FunctionSignature]


@dataclass
class FileDefinition:
    filepath: str
    object_name: str
    definition: any
