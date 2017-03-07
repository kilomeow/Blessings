#include <cstdio>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include "terminal_io_ansi_linux.hpp"
#include "ansi_symbol_table.hpp"
#include "../write_stream_linux.hpp"
#include "../../additional_structs.hpp"

namespace blessings {
  template<typename InS, typename OutS, typename Property>
  TerminalIOANSILinux<InS, OutS, Property>::TerminalIOANSILinux() :
    inited(false) {};

  template<typename InS, typename OutS, typename Property>
  TerminalIOANSILinux<InS, OutS, Property>::~TerminalIOANSILinux() {
    if (inited) {
      setEchoInhibition();
      resetSGR();
      showCursor();
      resetDeviceMode();
    }
  }

  template<typename InS, typename OutS, typename Property>
  void TerminalIOANSILinux<InS, OutS, Property>::init(std::string path) {
    if (inited) throw ReInitAttempt();

    if (path=="") fd=open(ttyname(1), O_RDWR|O_APPEND);
    else fd=open(path.c_str(), O_RDWR|O_APPEND);

    if (fd==-1) throw InitError();

    file=fdopen(fd, "rw+");
    if (file==nullptr) {
      close(fd);
      throw InitError();
    }

    try {
      ws = new WriteStreamLinux(file);
    }
    catch(...) {
      fclose(file);
      throw InitError();
    }

    int temp=tcgetattr(fd,&storedSettings);
    if (temp!=0) {
      fclose(file);
      throw InitError();
    }

    termios tempSettings=storedSettings;
    tempSettings.c_lflag &=~ECHO;
    tcsetattr(fd,TCSANOW,&tempSettings); //Pray it works

    try {
      ws->write(ANSISymbolTable<OutS>::ESCSymbol);
      ws->write(ANSISymbolTable<OutS>::openBracket);
      ws->write(ANSISymbolTable<OutS>::zero);
      ws->write(ANSISymbolTable<OutS>::mSym);

      ws->flush();
    }
    catch(...) {
      tcsetattr(fd,TCSANOW,&storedSettings);
      fclose(file);
      throw InitError();
    }

    tcsetattr(fd,TCSANOW,&storedSettings); //Pray it works

    inited=true;
    echoInhibited=0;
    nonCanonicalMode=0;

    currentProperty=Property::empty;
  }

  template<typename InS, typename OutS, typename Property>
  void TerminalIOANSILinux<InS, OutS, Property>::disconnect() {
    if(!inited) throw BadMode();

    resetSGR();

    inited=false;
  }

  template<typename InS, typename OutS, typename Property>
  void TerminalIOANSILinux<InS, OutS, Property>::print(\
    OutS sym, const Property& prop) {
    if (!inited) throw BadMode();

    try {
      setSGR(prop);

      ws->write(sym);

      ws->flush();
    }
    catch (...) {
      throw IOError();
    }
  }

  template<typename InS, typename OutS, typename Property>
  void TerminalIOANSILinux<InS, OutS, Property>::print(OutS sym) {
    if (!inited) throw BadMode();

    try {
      setSGR(Property::empty);

      ws->write(sym);

      ws->flush();
    }
    catch (...) {
      throw IOError();
    }
  }

  template<typename InS, typename OutS, typename Property>
  void TerminalIOANSILinux<InS, OutS, Property>::clearScreen() {
    if (!inited) throw BadMode();

    try {
      ws->write(ANSISymbolTable<OutS>::ESCSymbol);
      ws->write(ANSISymbolTable<OutS>::openBracket);
      ws->write(ANSISymbolTable<OutS>::two);
      ws->write(ANSISymbolTable<OutS>::JSym);

      ws->flush();
    }
    catch (...) {
      throw IOError();
    }
  }

  template<typename InS, typename OutS, typename Property>
  void TerminalIOANSILinux<InS, OutS, Property>::newLine() {
    if (!inited) throw BadMode();

    try {
      ws->write(ANSISymbolTable<OutS>::newLineSymbol);

      ws->flush();
    }
    catch (...) {
      throw IOError();
    }
  }

  template<typename InS, typename OutS, typename Property>
  void TerminalIOANSILinux<InS, OutS, Property>::moveCursor(int x, int y) {
    if (!inited) throw BadMode();

    try {
      if (x==0 && y==0) return;

      int xAbs=x<0 ? -x : x;
      int yAbs=y<0 ? -y : y;

      std::string xAbsStr=std::to_string(xAbs);
      std::string yAbsStr=std::to_string(yAbs);

      if (x!=0) {
        ws->write(ANSISymbolTable<OutS>::ESCSymbol);
        ws->write(ANSISymbolTable<OutS>::openBracket);

        for(size_t i=0; i<xAbsStr.size(); ++i) {
          ws->write(xAbsStr[i]);
        }

        if (x<0) ws->write(ANSISymbolTable<OutS>::DSym);
        else ws->write(ANSISymbolTable<OutS>::CSym);
      }

      if (y!=0) {
        ws->write(ANSISymbolTable<OutS>::ESCSymbol);
        ws->write(ANSISymbolTable<OutS>::openBracket);

        for(size_t i=0; i<yAbsStr.size(); ++i) {
          ws->write(yAbsStr[i]);
        }

        if (y>0) ws->write(ANSISymbolTable<OutS>::ASym);
        else ws->write(ANSISymbolTable<OutS>::BSym);
      }

      ws->flush();
    }
    catch (...) {
      throw IOError();
    }
  }

  template<typename InS, typename OutS, typename Property>
  void TerminalIOANSILinux<InS, OutS, Property>::moveCursorTo(int x, int y) {
    if (!inited) throw BadMode();

    if (x<=0 || y<=0) throw ArgumentError();

    try {
      std::string xStr=std::to_string(x);
      std::string yStr=std::to_string(y);

      ws->write(ANSISymbolTable<OutS>::ESCSymbol);
      ws->write(ANSISymbolTable<OutS>::openBracket);

      for(size_t i=0; i<yStr.size(); ++i) {
        ws->write(yStr[i]);
      }

      ws->write(ANSISymbolTable<OutS>::semicolon);

      for(size_t i=0; i<xStr.size(); ++i) {
        ws->write(xStr[i]);
      }

      ws->write(ANSISymbolTable<OutS>::HSym);

      ws->flush();
    }
    catch (...) {
      throw IOError();
    }
  }

  template<typename InS, typename OutS, typename Property>
  void TerminalIOANSILinux<InS, OutS, Property>::resetSGR() {
    if (!inited) throw BadMode();

    try {
      ws->write(ANSISymbolTable<OutS>::ESCSymbol);
      ws->write(ANSISymbolTable<OutS>::openBracket);
      ws->write(ANSISymbolTable<OutS>::zero);
      ws->write(ANSISymbolTable<OutS>::mSym);

      ws->flush();
    }
    catch (...) {
      throw IOError();
    }
  }

  template<typename InS, typename OutS, typename Property>
  void TerminalIOANSILinux<InS, OutS, Property>::hideCursor() {
    if (!inited) throw BadMode();

    try {
      ws->write(ANSISymbolTable<OutS>::ESCSymbol);
      ws->write(ANSISymbolTable<OutS>::openBracket);
      ws->write(ANSISymbolTable<OutS>::question);
      ws->write(ANSISymbolTable<OutS>::two);
      ws->write(ANSISymbolTable<OutS>::five);
      ws->write(ANSISymbolTable<OutS>::lSym);

      ws->flush();
    }
    catch (...) {
      throw IOError();
    }
  }

  template<typename InS, typename OutS, typename Property>
  void TerminalIOANSILinux<InS, OutS, Property>::showCursor() {
    if (!inited) throw BadMode();

    try {
      ws->write(ANSISymbolTable<OutS>::ESCSymbol);
      ws->write(ANSISymbolTable<OutS>::openBracket);
      ws->write(ANSISymbolTable<OutS>::question);
      ws->write(ANSISymbolTable<OutS>::two);
      ws->write(ANSISymbolTable<OutS>::five);
      ws->write(ANSISymbolTable<OutS>::hSym);

      ws->flush();
    }
    catch (...) {
      throw IOError();
    }
  }

  template<typename InS, typename OutS, typename Property>
  void TerminalIOANSILinux<InS, OutS, Property>::saveCursorPos() {
    if (!inited) throw BadMode();

    try {
      ws->write(ANSISymbolTable<OutS>::ESCSymbol);
      ws->write(ANSISymbolTable<OutS>::openBracket);
      ws->write(ANSISymbolTable<OutS>::sSym);

      ws->flush();
    }
    catch (...) {
      throw IOError();
    }
  }

  template<typename InS, typename OutS, typename Property>
  void TerminalIOANSILinux<InS, OutS, Property>::restoreCursorPos() {
    if (!inited) throw BadMode();

    try {
      ws->write(ANSISymbolTable<OutS>::ESCSymbol);
      ws->write(ANSISymbolTable<OutS>::openBracket);
      ws->write(ANSISymbolTable<OutS>::uSym);

      ws->flush();
    }
    catch (...) {
      throw IOError();
    }
  }

  template<typename InS, typename OutS, typename Property>
  void TerminalIOANSILinux<InS, OutS, Property>::setNonCanonicalMode() {
    if (!inited) throw BadMode();

    if (nonCanonicalMode==1) return;

    termios currSettings;

    int temp=tcgetattr(fd,&currSettings);
    if (temp!=0) throw DeviceError();

    currSettings.c_lflag &=~ICANON;
    currSettings.c_cc[VTIME] = 0;
    currSettings.c_cc[VMIN] = 0;

    tcsetattr(fd,TCSANOW,&currSettings); //Pray it works

    nonCanonicalMode = 1;
  }

  template<typename InS, typename OutS, typename Property>
  void TerminalIOANSILinux<InS, OutS, Property>::setCanonicalMode() {
    if (!inited) throw BadMode();

    if (nonCanonicalMode==-1) return;

    termios currSettings;

    int temp=tcgetattr(fd,&currSettings);
    if (temp!=0) throw DeviceError();

    currSettings.c_lflag |=ICANON;

    tcsetattr(fd,TCSANOW,&currSettings); //Pray it works

    nonCanonicalMode = -1;
  }

  template<typename InS, typename OutS, typename Property>
  void TerminalIOANSILinux<InS, OutS, Property>::setEchoInhibition() {
    if (!inited) throw BadMode();

    if (echoInhibited==1) return;

    termios currSettings;

    int temp=tcgetattr(fd,&currSettings);
    if (temp!=0) throw DeviceError();

    currSettings.c_lflag &=~ECHO;

    tcsetattr(fd,TCSANOW,&currSettings); //Pray it works

    echoInhibited = 1;
  }

  template<typename InS, typename OutS, typename Property>
  void TerminalIOANSILinux<InS, OutS, Property>::setEchoForward() {
    if (!inited) throw BadMode();

    if (echoInhibited==-1) return;

    termios currSettings;

    int temp=tcgetattr(fd,&currSettings);
    if (temp!=0) throw DeviceError();

    currSettings.c_lflag |=ECHO;

    tcsetattr(fd,TCSANOW,&currSettings); //Pray it works

    echoInhibited = -1;
  }

  template<typename InS, typename OutS, typename Property>
  void TerminalIOANSILinux<InS, OutS, Property>::resetDeviceMode() {
    if (!inited) throw BadMode();

    tcsetattr(fd,TCSANOW,&storedSettings); //Pray it works

    nonCanonicalMode = 0;
    echoInhibited = 0;
  }

  template<typename InS, typename OutS, typename Property>
  MonitorResolution TerminalIOANSILinux<InS, OutS, Property>::getResolution() {
    if (!inited) throw BadMode();

    winsize ws;
    int temp=ioctl(fd, TIOCGWINSZ, &ws);
    if (temp==-1) throw DeviceError();

    return MonitorResolution(ws.ws_col, ws.ws_row);
  }
}
