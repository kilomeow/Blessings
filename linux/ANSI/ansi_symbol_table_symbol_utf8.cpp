#include "../../symbol_utf8/symbol_utf8.hpp"
#include "ansi_symbol_table.hpp"

namespace blessings {
  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::CSISymbol(
  {static_cast<char>(0xC2), static_cast<char>(0x9B)});

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::newLineSymbol(
  {static_cast<char>(0xA)});

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::ESCSymbol(
  {static_cast<char>(0x1B)});


  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::spaceSymbol(
  {static_cast<char>(0x20)});

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::openBracket(
  {static_cast<char>(0x5B)});

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::closeBracket(
  {static_cast<char>(0x5D)});

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::semicolon(
  {static_cast<char>(0x3B)});

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::question(
  {static_cast<char>(0x3F)});


  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::zero(
  {static_cast<char>(0x30)});

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::one(
  {static_cast<char>(0x31)});

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::two(
  {static_cast<char>(0x32)});

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::three(
  {static_cast<char>(0x33)});

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::four(
  {static_cast<char>(0x34)});

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::five(
  {static_cast<char>(0x35)});

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::six(
  {static_cast<char>(0x36)});

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::seven(
  {static_cast<char>(0x37)});

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::eight(
  {static_cast<char>(0x38)});

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::nine(
  {static_cast<char>(0x39)});


  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::mSym(
  {static_cast<char>(0x6D)});

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::JSym(
  {static_cast<char>(0x4A)});

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::ASym(
  {static_cast<char>(0x41)});

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::BSym(
  {static_cast<char>(0x42)});

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::CSym(
  {static_cast<char>(0x43)});

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::DSym(
  {static_cast<char>(0x44)});

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::HSym(
  {static_cast<char>(0x48)});

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::fSym(
  {static_cast<char>(0x66)});

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::lSym(
  {static_cast<char>(0x6C)});

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::hSym(
  {static_cast<char>(0x68)});

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::sSym(
  {static_cast<char>(0x73)});

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::uSym(
  {static_cast<char>(0x75)});
}
