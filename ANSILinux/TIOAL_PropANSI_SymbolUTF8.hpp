#pragma once

#include "Termios.hpp"
#include <cstdio>

#include "Symbol.hpp"
#include "../WriteStream.hpp"
#include "../ReadStream.hpp"
#include "ReadStream.hpp"
#include "AdditionalStructs.hpp"

namespace Blessings_ns {
  template <>
  class TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI> :
    public TerminalIO<SymbolUTF8, SymbolUTF8, PropertyANSI> {

    bool inited;
    bool noncanonicalMode;

    WriteStream<SymbolUTF8, PropertyANSI>* ws;
    ReadStream<SymbolUTF8>* rs;

    Termios_ns::termios storedSettings;

    FILE* file;
  public:
    class Error;

    TerminalIOANSILinux();

    void Init(FILE* f=stdout);

    //Device info
    MonitorResolution getResolution getResolution() {};
    GridPos getCursorPos() {};

    //IO
    void print(SymbolUTF8, PropertyGeneral*);
    SymbolUTF8 getSym() {};

    //Screen state
    void clearScreen();

    void newLine();

    void moveCursor(int x, int y);

    void hideCursor() {};
    void showCursor() {};

    void saveCursorPos() {};
    void restoreCursorPos() {};

    void resetSGR();

    //Terminal info
    int boldSupported() {return 0};
    int italicsSupported() {return 0};

    PropertyType getPropertyType() {return PropertyType(PropertyType::ANSI)};

    //Terminal state
    void setDeviceReady();
    void resetDeviceMode();
    bool isDeviceReady();

    //Global state
    bool isReady();
  };
}
