#include "symbol_utf8.hpp"
#include "some_symbol_utf8_symbols.hpp"

namespace blessings {
  template<>
  const char SymbolTable<SymbolUTF8>::CSIInit[]={static_cast<char>(0xC2), static_cast<char>(0x9B), '\0'};
  template<>
  const char SymbolTable<SymbolUTF8>::newLineSymbolInit[]={static_cast<char>(0xA), '\0'};
  template<>
  const char SymbolTable<SymbolUTF8>::ESCInit[]={static_cast<char>(0x1B), '\0'};

  template<>
  const char SymbolTable<SymbolUTF8>::spaceInit[]={static_cast<char>(0x20), '\0'};
  template<>
  const char SymbolTable<SymbolUTF8>::openBracketInit[]={static_cast<char>(0x5B), '\0'};
  template<>
  const char SymbolTable<SymbolUTF8>::closeBracketInit[]={static_cast<char>(0x5D), '\0'};
  template<>
  const char SymbolTable<SymbolUTF8>::semicolonInit[]={static_cast<char>(0x3B), '\0'};
  template<>
  const char SymbolTable<SymbolUTF8>::questionInit[]={static_cast<char>(0x3F), '\0'};

  template<>
  const char SymbolTable<SymbolUTF8>::zeroInit[]={static_cast<char>(0x30), '\0'};
  template<>
  const char SymbolTable<SymbolUTF8>::oneInit[]={static_cast<char>(0x31), '\0'};
  template<>
  const char SymbolTable<SymbolUTF8>::twoInit[]={static_cast<char>(0x32), '\0'};
  template<>
  const char SymbolTable<SymbolUTF8>::threeInit[]={static_cast<char>(0x33), '\0'};
  template<>
  const char SymbolTable<SymbolUTF8>::fourInit[]={static_cast<char>(0x34), '\0'};
  template<>
  const char SymbolTable<SymbolUTF8>::fiveInit[]={static_cast<char>(0x35), '\0'};
  template<>
  const char SymbolTable<SymbolUTF8>::sixInit[]={static_cast<char>(0x36), '\0'};
  template<>
  const char SymbolTable<SymbolUTF8>::sevenInit[]={static_cast<char>(0x37), '\0'};
  template<>
  const char SymbolTable<SymbolUTF8>::eightInit[]={static_cast<char>(0x38), '\0'};
  template<>
  const char SymbolTable<SymbolUTF8>::nineInit[]={static_cast<char>(0x39), '\0'};

  template<>
  const char SymbolTable<SymbolUTF8>::mSymInit[]={static_cast<char>(0x6D), '\0'};
  template<>
  const char SymbolTable<SymbolUTF8>::JSymInit[]={static_cast<char>(0x4A), '\0'};
  template<>
  const char SymbolTable<SymbolUTF8>::ASymInit[]={static_cast<char>(0x41), '\0'};
  template<>
  const char SymbolTable<SymbolUTF8>::BSymInit[]={static_cast<char>(0x42), '\0'};
  template<>
  const char SymbolTable<SymbolUTF8>::CSymInit[]={static_cast<char>(0x43), '\0'};
  template<>
  const char SymbolTable<SymbolUTF8>::DSymInit[]={static_cast<char>(0x44), '\0'};
  template<>
  const char SymbolTable<SymbolUTF8>::HSymInit[]={static_cast<char>(0x48), '\0'};
  template<>
  const char SymbolTable<SymbolUTF8>::fSymInit[]={static_cast<char>(0x66), '\0'};
  template<>
  const char SymbolTable<SymbolUTF8>::lSymInit[]={static_cast<char>(0x6C), '\0'};
  template<>
  const char SymbolTable<SymbolUTF8>::hSymInit[]={static_cast<char>(0x68), '\0'};
  template<>
  const char SymbolTable<SymbolUTF8>::sSymInit[]={static_cast<char>(0x73), '\0'};
  template<>
  const char SymbolTable<SymbolUTF8>::uSymInit[]={static_cast<char>(0x75), '\0'};

  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::CSISymbol=SymbolUTF8(CSIInit);
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::newLineSymbol=SymbolUTF8(newLineSymbolInit);
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::ESCSymbol=SymbolUTF8(ESCInit);

  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::spaceSymbol=SymbolUTF8(spaceInit);
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::openBracket=SymbolUTF8(openBracketInit);
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::closeBracket=SymbolUTF8(closeBracketInit);
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::semicolon=SymbolUTF8(semicolonInit);
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::question=SymbolUTF8(questionInit);

  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::zero=SymbolUTF8(zeroInit);
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::one=SymbolUTF8(oneInit);
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::two=SymbolUTF8(twoInit);
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::three=SymbolUTF8(threeInit);
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::four=SymbolUTF8(fourInit);
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::five=SymbolUTF8(fiveInit);
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::six=SymbolUTF8(sixInit);
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::seven=SymbolUTF8(sevenInit);
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::eight=SymbolUTF8(eightInit);
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::nine=SymbolUTF8(nineInit);

  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::mSym=SymbolUTF8(mSymInit);
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::JSym=SymbolUTF8(JSymInit);
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::ASym=SymbolUTF8(ASymInit);
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::BSym=SymbolUTF8(BSymInit);
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::CSym=SymbolUTF8(CSymInit);
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::DSym=SymbolUTF8(DSymInit);
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::HSym=SymbolUTF8(HSymInit);
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::fSym=SymbolUTF8(fSymInit);
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::lSym=SymbolUTF8(lSymInit);
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::hSym=SymbolUTF8(hSymInit);
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::sSym=SymbolUTF8(lSymInit);
  template<>
  const SymbolUTF8 SymbolTable<SymbolUTF8>::uSym=SymbolUTF8(hSymInit);
}
