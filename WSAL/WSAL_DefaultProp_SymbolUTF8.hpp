#pragma once

#include <cstdio>
#include "Termios.hpp"

#include "../AdditionalStructs.hpp"
#include "../SymbolUTF8.hpp"
#include "../WriteStream.hpp"
#include "WriteStreamANSILinux.hpp"

namespace Blessings_ns {
  template <>
  class WriteStreamANSILinux<SymbolUTF8, Property<ColorANSI> > :
    public WriteStream<SymbolUTF8> {
    FILE* file;

    Termios_ns::termios storedSettings;
  public:
    class Error;

    WriteStreamANSILinux();

    void print(SymbolUTF8, PropertyGeneral*);

    void clearScreen();

    void newLine();

    void moveCursor(int x, int y);

    void hideCursor() {};
    void showCursor() {};

    void saveCursorPos() {};
    void restoreCursorPos() {};

    int boldSupported() {return 0;};
    int italicsSupported() {return 0;};

    PropertyType getPropertyType() {return ColorType::ANSI;};

    //Pure ANSI/Linux methods
    void setNonCanonTerminalMode(); //rewrite!
    void resetTerminalMode(); //rewrite!

    void resetSGR();
  };
}
