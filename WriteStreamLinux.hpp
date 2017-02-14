#pragma once

#include "WriteStream.hpp"
#include "AdditionalStructs.hpp"
#include "Symbol.hpp"

namespace Blessings_ns {
  template <>
  class WriteStreamLinux<SymbolUTF8, PropertyANSI> {
    FILE* file;

    static const SymbolUTF8 CSISymbol;
  public:
    WriteStreamLinux(); //uses stdout

    void print(SymbolUTF8, PropertyANSI);

    void clearScreen();

    void newLine();

    void moveCursor(int x, int y);
    CursorPos getCursorPos();

    void hideCursor();
    void showCursor();

    void saveCursorPos();
    void restoreCursorPos();

    void clearScreen();

    MonitorResolution getResolution();
  };

  const SymbolUTF8 WriteStreamLinux<SymbolUTF8, PropertyANSI>::CSISymbol=SymbolUTF8({static_cast<char>(0x9), static_cast<char>(0xB), static_cast<char>('\0')});
}
