#pragma once

// Gurantees: no other program works with that terminal (changes its mode, writes,
// reads

#include <termios.h>
#include <cstdio>
#include <queue>

#include "../additional_structs.hpp"
#include "../error.hpp"
#include "terminal_io_ansi_linux.hpp"
#include "../terminal_io.hpp"

namespace blessings {
  template <typename InS, typename OutS, typename InStr, typename OutStr,
    typename Property>
  class TerminalIOANSILinux :
    public TerminalIO<InS, OutS, InStr, OutStr, Property> {

    bool inited;
    int nonCanonicalMode;
    int echoInhibited;

    WriteStreamLinux* ws;
    //ReadStream<InS>* rs;

    termios storedSettings;

    int fd;
    FILE* file;

    Property currentProperty;
    
    TerminalIO(const TerminalIO&);
    TerminalIO& operator=(const TerminalIO&);
  public:
    class Error : public BlessingsError {};
    class InitError : public Error {};
    class ReInitAttemptError : public Error {};
    class NotInitedError : public Error {};
    class ArgumentError : public Error {};
    class IOError : public Error {};
    class DeviceError : public Error {};
    class BadModeError : public Error {};

    TerminalIOANSILinux();

    ~TerminalIOANSILinux();

    void Init(std::string path="");

    //Device info
    MonitorResolution getResolution(); //TODO: rewrite!

    //IO
    void print(OutS, const Property&);
    void print(OutS);
    void print(const OutStr&);
    
    std::queue<InS> getSymbol(int n=1) {return std::queue<InS>();}; //TODO: rewrite!
    InStr getString(GridPos start);
    void clearInputBuffer() {};

    //Screen state
    void clearScreen();

    void newLine();

    void moveCursor(int x, int y);
    void moveCursorTo(int x, int y);

    void hideCursor();
    void showCursor();

    void saveCursorPos();
    void restoreCursorPos();

    void setSGR(const Property&)
    void resetSGR();

    //Terminal info
    int boldSupported() {return 0;};
    int italicsSupported() {return 0;};

    PropertyType getPropertyType() {return PropertyType(PropertyType::ANSI);};

    //Terminal state
    void setNonCanonicalMode();
    void setCanonicalMode();
    void setEchoInhibition();
    void setEchoForward();

    void resetDeviceMode();

    int isNonCanonical() {return nonCanonicalMode;};
    int isEchoInhibited() {return echoInhibited;};

    bool isInited() {return inited;};
  };
}
