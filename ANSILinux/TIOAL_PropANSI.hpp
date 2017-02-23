#pragma once

// Gurantees: no other program works with that terminal (changes its mode, writes,
// reads

#include <termios.h>
#include <cstdio>
#include <vector>

#include "../Symbol/Symbol.hpp"
#include "../WriteStream.hpp"
#include "../ReadStream.hpp"
#include "../AdditionalStructs.hpp"
#include "../Error.hpp"
#include "TerminalIOANSILinux.hpp"
#include "../TerminalIO.hpp"

namespace blessings {
  template <class InS, class OutS>
  class TerminalIOANSILinux<InS, OutS, PropertyANSI> :
    public TerminalIO<InS, OutS> {

    bool inited;
    bool noncanonicalMode;

    WriteStream<OutS>* ws;
    //ReadStream<InS>* rs;

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

    TerminalIOANSILinux() throw();

    ~TerminalIOANSILinux();

    void Init(FILE* f=stdout);

    //Device info
    MonitorResolution getResolution() {};
    GridPos getCursorPos() {};

    //IO
    void print(OutS, Property*);
    void print(OutS);
    std::vector<InS> getSymbol(); //rewrite!

    //Screen state
    void clearScreen();

    void newLine();

    void moveCursor(int x, int y);
    void moveCursorTo(int x, int y);

    void hideCursor();
    void showCursor();

    void saveCursorPos();
    void restoreCursorPos();

    void resetSGR();

    //Terminal info
    int boldSupported() {return 0;};
    int italicsSupported() {return 0;};

    PropertyType getPropertyType() {return PropertyType(PropertyType::ANSI);};

    //Terminal state
    void setDeviceReady();
    void resetDeviceMode();
    bool isDeviceReady() {return noncanonicalMode;};

    //Global state
    bool isReady() {return inited && noncanonicalMode;};
  };


  //Errors
  template<class InS, class OutS>
  class TerminalIOANSILinux<InS, OutS, PropertyANSI>::Error :\
    public BlessingsError {};
  template<class InS, class OutS>
  class TerminalIOANSILinux<InS, OutS, PropertyANSI>::InitError :\
    public TerminalIOANSILinux<InS, OutS, PropertyANSI>::Error {};
  template<class InS, class OutS>
  class TerminalIOANSILinux<InS, OutS, PropertyANSI>::ReadinessError :\
    public TerminalIOANSILinux<InS, OutS, PropertyANSI>::Error {};
  template<class InS, class OutS>
  class TerminalIOANSILinux<InS, OutS, PropertyANSI>::ArgumentError :\
    public TerminalIOANSILinux<InS, OutS, PropertyANSI>::Error {};
  template<class InS, class OutS>
  class TerminalIOANSILinux<InS, OutS, PropertyANSI>::IOError :\
    public TerminalIOANSILinux<InS, OutS, PropertyANSI>::Error {};
  template<class InS, class OutS>
  class TerminalIOANSILinux<InS, OutS, PropertyANSI>::DeviceError :\
    public TerminalIOANSILinux<InS, OutS, PropertyANSI>::Error {};
  template<class InS, class OutS>
  class TerminalIOANSILinux<InS, OutS, PropertyANSI>::UninitedStateError :\
    public TerminalIOANSILinux<InS, OutS, PropertyANSI>::ReadinessError {};
}
