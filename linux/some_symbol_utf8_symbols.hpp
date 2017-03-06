#pragma once

#include "symbol_utf8.hpp"

namespace blessings {
  template <class Symbol>
  struct ANSISymbolTable {
    static const SymbolUTF8 CSISymbol;
    static const SymbolUTF8 newLineSymbol;
    static const SymbolUTF8 ESCSymbol;

    static const SymbolUTF8 spaceSymbol;
    static const SymbolUTF8 openBracket;
    static const SymbolUTF8 closeBracket;
    static const SymbolUTF8 semicolon;
    static const SymbolUTF8 question;

    static const SymbolUTF8 zero;
    static const SymbolUTF8 one;
    static const SymbolUTF8 two;
    static const SymbolUTF8 three;
    static const SymbolUTF8 four;
    static const SymbolUTF8 five;
    static const SymbolUTF8 six;
    static const SymbolUTF8 seven;
    static const SymbolUTF8 eight;
    static const SymbolUTF8 nine;

    static const SymbolUTF8 mSym;
    static const SymbolUTF8 JSym;
    static const SymbolUTF8 ASym;
    static const SymbolUTF8 BSym;
    static const SymbolUTF8 CSym;
    static const SymbolUTF8 DSym;
    static const SymbolUTF8 HSym;
    static const SymbolUTF8 fSym;
    static const SymbolUTF8 lSym;
    static const SymbolUTF8 hSym;
    static const SymbolUTF8 sSym;
    static const SymbolUTF8 uSym;
  };
}
