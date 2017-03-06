#include "symbol_utf8.hpp"
#include "some_symbol_utf8_symbols.hpp"

namespace blessings {
  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::CSISymbol=
  {static_cast<char>(0xC2), static_cast<char>(0x9B), '\0'};

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::newLineSymbol=
  {static_cast<char>(0xA), '\0'};

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::ESCSymbol=
  {static_cast<char>(0x1B), '\0'};


  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::spaceSymbol=
  {static_cast<char>(0x20), '\0'};

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::openBracket=
  {static_cast<char>(0x5B), '\0'};

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::closeBracket=
  {static_cast<char>(0x5D), '\0'};

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::semicolon=
  {static_cast<char>(0x3B), '\0'};

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::question=
  {static_cast<char>(0x3F), '\0'};


  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::zero=
  {static_cast<char>(0x30), '\0'};

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::one=
  {static_cast<char>(0x31), '\0'};

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::two=
  {static_cast<char>(0x32), '\0'};

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::three=
  {static_cast<char>(0x33), '\0'};

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::four=
  {static_cast<char>(0x34), '\0'};

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::five=
  {static_cast<char>(0x35), '\0'};

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::six=
  {static_cast<char>(0x36), '\0'};

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::seven=
  {static_cast<char>(0x37), '\0'};

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::eight=
  {static_cast<char>(0x38), '\0'};

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::nine=
  {static_cast<char>(0x39), '\0'};


  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::mSym=
  {static_cast<char>(0x6D), '\0'};

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::JSym=
  {static_cast<char>(0x4A), '\0'};

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::ASym=
  {static_cast<char>(0x41), '\0'};

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::BSym=
  {static_cast<char>(0x42), '\0'};

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::CSym=
  {static_cast<char>(0x43), '\0'};

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::DSym=
  {static_cast<char>(0x44), '\0'};

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::HSym=
  {static_cast<char>(0x48), '\0'};

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::fSym=
  {static_cast<char>(0x66), '\0'};

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::lSym=
  {static_cast<char>(0x6C), '\0'};

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::hSym=
  {static_cast<char>(0x68), '\0'};

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::sSym=
  {static_cast<char>(0x73), '\0'};

  template<>
  const SymbolUTF8 ANSISymbolTable<SymbolUTF8>::uSym=
  {static_cast<char>(0x75), '\0'};
}
