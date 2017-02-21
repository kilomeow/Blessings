#pragma once

#include "SymbolUTF8.hpp"

namespace blessings {
  template <class Symbol>
  struct SymbolTable {
    static const char CSIInit[];
    static const char newLineSymbolInit[];
    static const char ESCInit[];

    static const char spaceInit[];
    static const char openBracketInit[];
    static const char closeBracketInit[];
    static const char semicolonInit[];
    static const char questionInit[];

    static const char zeroInit[];
    static const char oneInit[];
    static const char twoInit[];
    static const char threeInit[];
    static const char fourInit[];
    static const char fiveInit[];
    static const char sixInit[];
    static const char sevenInit[];
    static const char eightInit[];
    static const char nineInit[];

    static const char mSymInit[];
    static const char JSymInit[];
    static const char ASymInit[];
    static const char BSymInit[];
    static const char CSymInit[];
    static const char DSymInit[];
    static const char HSymInit[];
    static const char fSymInit[];
    static const char lSymInit[];
    static const char hSymInit[];
    static const char sSymInit[];
    static const char uSymInit[];

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

  template<>
  const char SymbolTable<SymbolUTF8>::CSIInit[];
  template<>
  const char SymbolTable<SymbolUTF8>::newLineSymbolInit[];
  template<>
  const char SymbolTable<SymbolUTF8>::ESCInit[];

  template<>
  const char SymbolTable<SymbolUTF8>::spaceInit[];
  template<>
  const char SymbolTable<SymbolUTF8>::openBracketInit[];
  template<>
  const char SymbolTable<SymbolUTF8>::closeBracketInit[];
  template<>
  const char SymbolTable<SymbolUTF8>::semicolonInit[];
  template<>
  const char SymbolTable<SymbolUTF8>::questionInit[];

  template<>
  const char SymbolTable<SymbolUTF8>::zeroInit[];
  template<>
  const char SymbolTable<SymbolUTF8>::oneInit[];
  template<>
  const char SymbolTable<SymbolUTF8>::twoInit[];
  template<>
  const char SymbolTable<SymbolUTF8>::threeInit[];
  template<>
  const char SymbolTable<SymbolUTF8>::fourInit[];
  template<>
  const char SymbolTable<SymbolUTF8>::fiveInit[];
  template<>
  const char SymbolTable<SymbolUTF8>::sixInit[];
  template<>
  const char SymbolTable<SymbolUTF8>::sevenInit[];
  template<>
  const char SymbolTable<SymbolUTF8>::eightInit[];
  template<>
  const char SymbolTable<SymbolUTF8>::nineInit[];

  template<>
  const char SymbolTable<SymbolUTF8>::mSymInit[];
  template<>
  const char SymbolTable<SymbolUTF8>::JSymInit[];
  template<>
  const char SymbolTable<SymbolUTF8>::ASymInit[];
  template<>
  const char SymbolTable<SymbolUTF8>::BSymInit[];
  template<>
  const char SymbolTable<SymbolUTF8>::CSymInit[];
  template<>
  const char SymbolTable<SymbolUTF8>::DSymInit[];
  template<>
  const char SymbolTable<SymbolUTF8>::HSymInit[];
  template<>
  const char SymbolTable<SymbolUTF8>::fSymInit[];
  template<>
  const char SymbolTable<SymbolUTF8>::lSymInit[];
  template<>
  const char SymbolTable<SymbolUTF8>::hSymInit[];
  template<>
  const char SymbolTable<SymbolUTF8>::sSymInit[];
  template<>
  const char SymbolTable<SymbolUTF8>::uSymInit[];

  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::CSISymbol;
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::newLineSymbol;
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::ESCSymbol;

  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::spaceSymbol;
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::openBracket;
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::closeBracket;
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::semicolon;
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::question;

  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::zero;
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::one;
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::two;
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::three;
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::four;
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::five;
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::six;
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::seven;
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::eight;
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::nine;

  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::mSym;
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::JSym;
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::ASym;
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::BSym;
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::CSym;
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::DSym;
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::HSym;
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::fSym;
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::lSym;
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::hSym;
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::sSym;
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::uSym;
}
