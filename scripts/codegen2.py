#! python3

from pypeg2 import *

class BaseType(Keyword):
    grammar = Enum(
        K('int'), K('char'), K('wchar_t'),
        K('char16_t'), K('char32_t'), K('int'),
        K('bool'), K('float'), K('double'),
        K('void')
    )

class Modifier(Keyword):
    grammar = Enum(
        K('short'), K('long'), K('signed'), K('unsigned'),
    )

class CVSpec(Keyword):
    grammar = Enum(K('const'), K('volatile'))

class Indirection(Keyword):
    grammar = Enum(K('*'), K('&'))

class Type(List):
    grammar = (
        attr('typecv', maybe_some(CVSpec)),
        attr('typing', [BaseType, Symbol]),
        attr('pointer_indir', maybe_some(Indirection)),
        attr('varcv', maybe_some(CVSpec)),
        attr('pointee_indir', maybe_some(Indirection))
    )
