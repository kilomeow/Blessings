#include "SymbolUTF8.hpp"
#include "SomeUTF8Symbols.hpp"

namespace blessings::SomeUTF8Symbols {
  const char CSIInit[]={static_cast<char>(0xC2), static_cast<char>(0x9B), '\0'};
  const char newLineSymbolInit[]={static_cast<char>(0xA), '\0'};

  const char spaceInit[]={static_cast<char>(0x20), '\0'};
  const char openBracketInit[]={static_cast<char>(0x5B), '\0'};
  const char closeBracketInit[]={static_cast<char>(0x5D), '\0'};
  const char semicolonInit[]={static_cast<char>(0x3B), '\0'};
  const char questionInit[]={static_cast<char>(0x3F), '\0'};

  const char zeroInit[]={static_cast<char>(0x30), '\0'};
  const char oneInit[]={static_cast<char>(0x31), '\0'};
  const char twoInit[]={static_cast<char>(0x32), '\0'};
  const char threeInit[]={static_cast<char>(0x33), '\0'};
  const char fourInit[]={static_cast<char>(0x34), '\0'};
  const char fiveInit[]={static_cast<char>(0x35), '\0'};
  const char sixInit[]={static_cast<char>(0x36), '\0'};
  const char sevenInit[]={static_cast<char>(0x37), '\0'};
  const char eightInit[]={static_cast<char>(0x38), '\0'};
  const char nineInit[]={static_cast<char>(0x39), '\0'};

  const char mSymInit[]={static_cast<char>(0x6D), '\0'};
  const char JSymInit[]={static_cast<char>(0x4A), '\0'};
  const char ASymInit[]={static_cast<char>(0x41), '\0'};
  const char BSymInit[]={static_cast<char>(0x42), '\0'};
  const char CSymInit[]={static_cast<char>(0x43), '\0'};
  const char DSymInit[]={static_cast<char>(0x44), '\0'};
  const char HSymInit[]={static_cast<char>(0x48), '\0'};
  const char fSymInit[]={static_cast<char>(0x66), '\0'};

  const SymbolUTF8 CSISymbol=SymbolUTF8(CSIInit);
  const SymbolUTF8 newLineSymbol=SymbolUTF8(newLineSymbolInit);

  const SymbolUTF8 spaceSymbol=SymbolUTF8(spaceInit);
  const SymbolUTF8 openBracket=SymbolUTF8(openBracketInit);
  const SymbolUTF8 closeBracket=SymbolUTF8(closeBracketInit);
  const SymbolUTF8 semicolon=SymbolUTF8(semicolonInit);
  const SymbolUTF8 question=SymbolUTF8(questionInit);

  const SymbolUTF8 zero=SymbolUTF8(zeroInit);
  const SymbolUTF8 one=SymbolUTF8(oneInit);
  const SymbolUTF8 two=SymbolUTF8(twoInit);
  const SymbolUTF8 three=SymbolUTF8(threeInit);
  const SymbolUTF8 four=SymbolUTF8(fourInit);
  const SymbolUTF8 five=SymbolUTF8(fiveInit);
  const SymbolUTF8 six=SymbolUTF8(sixInit);
  const SymbolUTF8 seven=SymbolUTF8(sevenInit);
  const SymbolUTF8 eight=SymbolUTF8(eightInit);
  const SymbolUTF8 nine=SymbolUTF8(nineInit);

  const SymbolUTF8 mSym=SymbolUTF8(mSymInit);
  const SymbolUTF8 JSym=SymbolUTF8(JSymInit);
  const SymbolUTF8 ASym=SymbolUTF8(ASymInit);
  const SymbolUTF8 BSym=SymbolUTF8(BSymInit);
  const SymbolUTF8 CSym=SymbolUTF8(CSymInit);
  const SymbolUTF8 DSym=SymbolUTF8(DSymInit);
  const SymbolUTF8 HSym=SymbolUTF8(HSymInit);
  const SymbolUTF8 fSym=SymbolUTF8(fSymInit);
}
