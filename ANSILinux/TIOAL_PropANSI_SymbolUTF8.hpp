#pragma once

// Gurantees: no other program works with that terminal (changes its mode, writes,
// reads

#include <termios.h>
#include <cstdio>

#include "../Symbol/Symbol.hpp"
#include "../WriteStream.hpp"
#include "../ReadStream.hpp"
#include "../AdditionalStructs.hpp"
#include "../Error.hpp"
#include "TerminalIOANSILinux.hpp"
#include "../TerminalIO.hpp"

namespace blessings {
  template <>
  class TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI> :
    public TerminalIO<SymbolUTF8, SymbolUTF8> {

    bool inited;
    bool noncanonicalMode;

    WriteStream<SymbolUTF8>* ws;
    //ReadStream<SymbolUTF8>* rs;

    termios storedSettings;

    FILE* file;
  public:
    class Error;
    class InitError;
    class ReadinessError;
    class ArgumentError;
    class IOError;
    class DeviceError;
    class UninitedStateError;

    TerminalIOANSILinux();

    ~TerminalIOANSILinux() throw();

    void Init(FILE* f=stdout);

    //Device info
    MonitorResolution getResolution() {};
    GridPos getCursorPos() {};

    //IO
    void print(SymbolUTF8, Property*);
    void print(SymbolUTF8);
    SymbolUTF8 getSym() {};

    //Screen state
    void clearScreen();

    void newLine();

    void moveCursor(int x, int y);
    void moveCursorTo(int x, int y);

    void hideCursor();
    void showCursor();

    void saveCursorPos() {};
    void restoreCursorPos() {};

    void resetSGR();

    //Terminal info
    int boldSupported() {return 0;};
    int italicsSupported() {return 0;};

    PropertyType getPropertyType() {return PropertyType(PropertyType::ANSI);};

    //Terminal state
    void setDeviceReady();
    void resetDeviceMode();
    bool isDeviceReady() {};

    //Global state
    bool isReady() {return inited && noncanonicalMode;};
  };


  //Errors
  class TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI>::Error :\
    public BlessingsError {};
  class TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI>::InitError :\
    public TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI>::Error {};
  class TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI>::ReadinessError :\
    public TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI>::Error {};
  class TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI>::ArgumentError :\
    public TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI>::Error {};
  class TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI>::IOError :\
    public TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI>::Error {};
  class TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI>::DeviceError :\
    public TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI>::Error {};
  class TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI>::UninitedStateError :\
    public TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI>::ReadinessError {};
}
