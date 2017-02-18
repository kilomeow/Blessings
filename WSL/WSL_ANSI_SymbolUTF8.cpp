#include <cstdio>
#include <string>

#include "WriteStreamLinux.hpp"
#include "WSL_ANSI_SymbolUTF8.hpp"
#include "../Symbol.hpp"

namespace Blessings_ns {
  namespace UTF8_ANSI_esc_code_symbols_init {
    const char CSIInit[]={static_cast<char>(0xC2), static_cast<char>(0x9B), '\0'};
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
  }

  const SymbolUTF8 WriteStreamLinux<SymbolUTF8, Property<ColorANSI> >::CSISymbol=\
    SymbolUTF8(UTF8_ANSI_esc_code_symbols_init::CSIInit);
  const SymbolUTF8 WriteStreamLinux<SymbolUTF8, Property<ColorANSI> >::spaceSymbol=\
    SymbolUTF8(UTF8_ANSI_esc_code_symbols_init::spaceInit);
  const SymbolUTF8 WriteStreamLinux<SymbolUTF8, Property<ColorANSI> >::openBracket=\
    SymbolUTF8(UTF8_ANSI_esc_code_symbols_init::openBracketInit);
  const SymbolUTF8 WriteStreamLinux<SymbolUTF8, Property<ColorANSI> >::closeBracket=\
    SymbolUTF8(UTF8_ANSI_esc_code_symbols_init::closeBracketInit);
  const SymbolUTF8 WriteStreamLinux<SymbolUTF8, Property<ColorANSI> >::semicolon=\
    SymbolUTF8(UTF8_ANSI_esc_code_symbols_init::semicolonInit);
  const SymbolUTF8 WriteStreamLinux<SymbolUTF8, Property<ColorANSI> >::question=\
    SymbolUTF8(UTF8_ANSI_esc_code_symbols_init::questionInit);

  const SymbolUTF8 WriteStreamLinux<SymbolUTF8, Property<ColorANSI> >::zero=\
    SymbolUTF8(UTF8_ANSI_esc_code_symbols_init::zeroInit);
  const SymbolUTF8 WriteStreamLinux<SymbolUTF8, Property<ColorANSI> >::one=\
    SymbolUTF8(UTF8_ANSI_esc_code_symbols_init::oneInit);
  const SymbolUTF8 WriteStreamLinux<SymbolUTF8, Property<ColorANSI> >::two=\
    SymbolUTF8(UTF8_ANSI_esc_code_symbols_init::twoInit);
  const SymbolUTF8 WriteStreamLinux<SymbolUTF8, Property<ColorANSI> >::three=\
    SymbolUTF8(UTF8_ANSI_esc_code_symbols_init::threeInit);
  const SymbolUTF8 WriteStreamLinux<SymbolUTF8, Property<ColorANSI> >::four=\
    SymbolUTF8(UTF8_ANSI_esc_code_symbols_init::fourInit);
  const SymbolUTF8 WriteStreamLinux<SymbolUTF8, Property<ColorANSI> >::five=\
    SymbolUTF8(UTF8_ANSI_esc_code_symbols_init::fiveInit);
  const SymbolUTF8 WriteStreamLinux<SymbolUTF8, Property<ColorANSI> >::six=\
    SymbolUTF8(UTF8_ANSI_esc_code_symbols_init::sixInit);
  const SymbolUTF8 WriteStreamLinux<SymbolUTF8, Property<ColorANSI> >::seven=\
    SymbolUTF8(UTF8_ANSI_esc_code_symbols_init::sevenInit);
  const SymbolUTF8 WriteStreamLinux<SymbolUTF8, Property<ColorANSI> >::eight=\
    SymbolUTF8(UTF8_ANSI_esc_code_symbols_init::eightInit);
  const SymbolUTF8 WriteStreamLinux<SymbolUTF8, Property<ColorANSI> >::nine=\
    SymbolUTF8(UTF8_ANSI_esc_code_symbols_init::nineInit);

  const SymbolUTF8 WriteStreamLinux<SymbolUTF8, Property<ColorANSI> >::mSym=\
    SymbolUTF8(UTF8_ANSI_esc_code_symbols_init::mSymInit);
  const SymbolUTF8 WriteStreamLinux<SymbolUTF8, Property<ColorANSI> >::JSym=\
    SymbolUTF8(UTF8_ANSI_esc_code_symbols_init::JSymInit);


  WriteStreamLinux<SymbolUTF8, Property<ColorANSI> >::WriteStreamLinux() {
    file=stdout;

    CSISymbol.writeToFile(file);
    zero.writeToFile(file);
    mSym.writeToFile(file);
  }

  void WriteStreamLinux<SymbolUTF8, Property<ColorANSI> >::clearScreen() {
    CSISymbol.writeToFile(file);
    two.writeToFile(file);
    JSym.writeToFile(file);
  }
}
