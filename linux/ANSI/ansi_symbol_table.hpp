#pragma once

namespace blessings {
  template <class Symbol>
  struct ANSISymbolTable {
    static const Symbol CSISymbol;
    static const Symbol newLineSymbol;
    static const Symbol ESCSymbol;

    static const Symbol spaceSymbol;
    static const Symbol openBracket;
    static const Symbol closeBracket;
    static const Symbol semicolon;
    static const Symbol question;

    static const Symbol zero;
    static const Symbol one;
    static const Symbol two;
    static const Symbol three;
    static const Symbol four;
    static const Symbol five;
    static const Symbol six;
    static const Symbol seven;
    static const Symbol eight;
    static const Symbol nine;

    static const Symbol mSym;
    static const Symbol JSym;
    static const Symbol ASym;
    static const Symbol BSym;
    static const Symbol CSym;
    static const Symbol DSym;
    static const Symbol HSym;
    static const Symbol fSym;
    static const Symbol lSym;
    static const Symbol hSym;
    static const Symbol sSym;
    static const Symbol uSym;
  };
}
