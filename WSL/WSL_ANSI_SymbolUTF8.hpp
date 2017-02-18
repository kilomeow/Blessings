#pragma once

#include <cstdio>

#include "../AdditionalStructs.hpp"
#include "../SymbolUTF8.hpp"
#include "WriteStreamLinux.hpp"

namespace Blessings_ns {
  template <>
  class WriteStreamLinux<SymbolUTF8, Property<ColorANSI> > {
    FILE* file;
  public:
    WriteStreamLinux();

    void print(SymbolUTF8, PropertyGeneral*) {};

    void clearScreen();

    void newLine() {};

    void moveCursor(int x, int y) {};
    GridPos getCursorPos() {};

    void hideCursor() {};
    void showCursor() {};

    void saveCursorPos() {};
    void restoreCursorPos() {};

    MonitorResolution getResolution() {};

    int boldSupported() {return 0;};
    int italicsSupported() {return 0;};

    ColorType getColorType() {return ColorType::ANSI;};

    static const SymbolUTF8 CSISymbol;
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
  };

  template <>
  class WriteStreamLinux<SymbolUTF8, Property<ColorANSI> >;
}
