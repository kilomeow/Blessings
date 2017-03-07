#pragma once

// Gurantees: no other program works with that terminal (changes its mode, writes,
// reads

#include <termios.h>
#include <cstdio>
#include <queue>

#include "../../additional_structs.hpp"
#include "../../error.hpp"
#include "../../terminal_io.hpp"
#include "../write_stream_linux.hpp"

namespace blessings {
  template <typename InS, typename OutS, typename Property>
  class TerminalIOANSILinux : public TerminalIO<InS, OutS, Property> {
    bool inited;
    int nonCanonicalMode;
    int echoInhibited;

    WriteStreamLinux* ws;
    //ReadStream<InS>* rs;

    termios storedSettings;

    int fd;
    FILE* file;

    Property currentProperty;

    TerminalIOANSILinux(const TerminalIOANSILinux&);
    TerminalIOANSILinux& operator=(const TerminalIOANSILinux&);
  public:
    class Error : public BlessingsError {};
    class InitError : public Error {};
    class ReInitAttempt : public Error {};
    class IOError : public Error {};
    class DeviceError : public Error {};
    class BadMode : public Error {};
    class ArgumentError : public Error {};

    TerminalIOANSILinux();

    ~TerminalIOANSILinux();

    void init(std::string path="");
    void disconnect();

    //Device info
    Resolution getResolution();

    //IO
    void print(OutS, const Property&);
    void print(OutS);

    std::queue<InS> getSymbol(int n=1); //TODO: rewrite!
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

    void setSGR(const Property&);
    void resetSGR();

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
