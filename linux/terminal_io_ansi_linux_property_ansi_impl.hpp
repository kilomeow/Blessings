#include <cstdio>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include "ansi_symbol_table.hpp"
#include "terminal_io_ansi_linux_property_ansi.hpp"
#include "write_stream_linux.hpp"
#include "../additional_structs.hpp"

namespace blessings {
  template<typename InS, typename OutS, typename InStr, typename OutStr,
    typename Property>
  TerminalIOANSILinux<InS, OutS, InStr, OutStr, Property>::
  TerminalIOANSILinux() {
    inited=false;
    nonCanonicalMode=0;
    echoInhibited=0;
  }

  template<typename InS, typename OutS, typename InStr, typename OutStr,
    typename Property>
  TerminalIOANSILinux<InS, OutS, InStr, OutStr, Property>::
  ~TerminalIOANSILinux() {
    if (inited) {
      setEchoInhibition();
      resetSGR();
      showCursor();
      resetDeviceMode();
    }
  }

  template<typename InS, typename OutS, typename InStr, typename OutStr,
    typename Property>
  TerminalIOANSILinux<InS, OutS, InStr, OutStr, Property>::
  Init(std::string path) {
    if (inited) throw ReInitAttemptError();

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

    inited = true;
  }

  template<typename InS, typename OutS, typename InStr, typename OutStr,
    typename Property>
  TerminalIOANSILinux<InS, OutS, InStr, OutStr, Property>::print(\
    OutS sym, const Property& prop) {
    if (!inited) throw BadModeError();

    try {
      setSGR(Property);

      ws->write(sym);

      ws->flush();
    }
    catch (...) {
      throw IOError();
    }
  }

  template<typename InS, typename OutS, typename InStr, typename OutStr,
    typename Property>
  TerminalIOANSILinux<InS, OutS, InStr, OutStr, Property>::print(OutS sym) {
    if (!inited) throw BadModeError();

    try {
      ws->write(sym);

      ws->flush();
    }
    catch (...) {
      throw IOError();
    }
  }

  template<typename InS, typename OutS, typename InStr, typename OutStr,
    typename Property>
  TerminalIOANSILinux<InS, OutS, InStr, OutStr, Property>::clearScreen() {
    if (!inited) throw BadModeError();

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

  template<typename InS, typename OutS, typename InStr, typename OutStr,
    typename Property>
  TerminalIOANSILinux<InS, OutS, InStr, OutStr, Property>::newLine() {
    if (!inited) throw BadModeError();

    try {
      ws->write(ANSISymbolTable<OutS>::newLineSymbol);

      ws->flush();
    }
    catch (...) {
      throw IOError();
    }
  }

  template<typename InS, typename OutS, typename InStr, typename OutStr,
    typename Property>
  TerminalIOANSILinux<InS, OutS, InStr, OutStr, Property>::moveCursor(int x, int y) {
    if (!inited) throw BadModeError();

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

  template<typename InS, typename OutS, typename InStr, typename OutStr,
    typename Property>
  TerminalIOANSILinux<InS, OutS, InStr, OutStr, Property>::moveCursorTo(int x, int y) {
    if (!inited) throw BadModeError();

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

  template<typename InS, typename OutS, typename InStr, typename OutStr,
    typename Property>
  TerminalIOANSILinux<InS, OutS, InStr, OutStr, Property>::setSGR(const Property& prop) {
 	  if (prop->bold) {
        ws->write(ANSISymbolTable<OutS>::ESCSymbol);
        ws->write(ANSISymbolTable<OutS>::openBracket);
        ws->write(ANSISymbolTable<OutS>::one);
        ws->write(ANSISymbolTable<OutS>::mSym);
      }

      if (prop->italics) {
        ws->write(ANSISymbolTable<OutS>::ESCSymbol);
        ws->write(ANSISymbolTable<OutS>::openBracket);
        ws->write(ANSISymbolTable<OutS>::three);
        ws->write(ANSISymbolTable<OutS>::mSym);
      }

      if (prop->color.color!=ColorANSI::NONE) {
        ws->write(ANSISymbolTable<OutS>::ESCSymbol);
        ws->write(ANSISymbolTable<OutS>::openBracket);
        ws->write(ANSISymbolTable<OutS>::three);
        switch(prop->color.color) {
        case ColorANSI::BLACK:
          ws->write(ANSISymbolTable<OutS>::zero);
          break;
        case ColorANSI::RED:
          ws->write(ANSISymbolTable<OutS>::one);
          break;
        case ColorANSI::GREEN:
          ws->write(ANSISymbolTable<OutS>::two);
          break;
        case ColorANSI::YELLOW:
          ws->write(ANSISymbolTable<OutS>::three);
          break;
        case ColorANSI::BLUE:
          ws->write(ANSISymbolTable<OutS>::four);
          break;
        case ColorANSI::MAGENTA:
          ws->write(ANSISymbolTable<OutS>::five);
          break;
        case ColorANSI::CYAN:
          ws->write(ANSISymbolTable<OutS>::six);
          break;
        case ColorANSI::WHITE:
          ws->write(ANSISymbolTable<OutS>::seven);
          break;
        default:
          throw ArgumentError();
        }
        ws->write(ANSISymbolTable<OutS>::mSym);
      }

      if (prop->backgroundColor.color!=ColorANSI::NONE) {
        ws->write(ANSISymbolTable<OutS>::ESCSymbol);
        ws->write(ANSISymbolTable<OutS>::openBracket);
        ws->write(ANSISymbolTable<OutS>::four);
        switch(prop->backgroundColor.color) {
        case ColorANSI::BLACK:
          ws->write(ANSISymbolTable<OutS>::zero);
          break;
        case ColorANSI::RED:
          ws->write(ANSISymbolTable<OutS>::one);
          break;
        case ColorANSI::GREEN:
          ws->write(ANSISymbolTable<OutS>::two);
          break;
        case ColorANSI::YELLOW:
          ws->write(ANSISymbolTable<OutS>::three);
          break;
        case ColorANSI::BLUE:
          ws->write(ANSISymbolTable<OutS>::four);
          break;
        case ColorANSI::MAGENTA:
          ws->write(ANSISymbolTable<OutS>::five);
          break;
        case ColorANSI::CYAN:
          ws->write(ANSISymbolTable<OutS>::six);
          break;
        case ColorANSI::WHITE:
          ws->write(ANSISymbolTable<OutS>::seven);
          break;
        default:
          throw ArgumentError();
        }
        ws->write(ANSISymbolTable<OutS>::mSym);
      }
  }

  template<typename InS, typename OutS, typename InStr, typename OutStr,
    typename Property>
  TerminalIOANSILinux<InS, OutS, InStr, OutStr, Property>::resetSGR() {
    if (!inited) throw BadModeError();

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

  template<typename InS, typename OutS, typename InStr, typename OutStr,
    typename Property>
  TerminalIOANSILinux<InS, OutS, InStr, OutStr, Property>::hideCursor() {
    if (!inited) throw BadModeError();

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

  template<typename InS, typename OutS, typename InStr, typename OutStr,
    typename Property>
  TerminalIOANSILinux<InS, OutS, InStr, OutStr, Property>::showCursor() {
    if (!inited) throw BadModeError();

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

  template<typename InS, typename OutS, typename InStr, typename OutStr,
    typename Property>
  TerminalIOANSILinux<InS, OutS, InStr, OutStr, Property>::saveCursorPos() {
    if (!inited) throw BadModeError();

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

  template<typename InS, typename OutS, typename InStr, typename OutStr,
    typename Property>
  TerminalIOANSILinux<InS, OutS, InStr, OutStr, Property>::restoreCursorPos() {
    if (!inited) throw BadModeError();

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

  template<typename InS, typename OutS, typename InStr, typename OutStr,
    typename Property>
  TerminalIOANSILinux<InS, OutS, InStr, OutStr, Property>::setNonCanonicalMode() {
    if (!inited) throw BadModeError();

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

  template<typename InS, typename OutS, typename InStr, typename OutStr,
    typename Property>
  TerminalIOANSILinux<InS, OutS, InStr, OutStr, Property>::setCanonicalMode() {
    if (!inited) throw BadModeError();

    if (nonCanonicalMode==-1) return;

    termios currSettings;

    int temp=tcgetattr(fd,&currSettings);
    if (temp!=0) throw DeviceError();

    currSettings.c_lflag |=ICANON;

    tcsetattr(fd,TCSANOW,&currSettings); //Pray it works

    nonCanonicalMode = -1;
  }

  template<typename InS, typename OutS, typename InStr, typename OutStr,
    typename Property>
  TerminalIOANSILinux<InS, OutS, InStr, OutStr, Property>::setEchoInhibition() {
    if (!inited) throw BadModeError();

    if (echoInhibited==1) return;

    termios currSettings;

    int temp=tcgetattr(fd,&currSettings);
    if (temp!=0) throw DeviceError();

    currSettings.c_lflag &=~ECHO;

    tcsetattr(fd,TCSANOW,&currSettings); //Pray it works

    echoInhibited = 1;
  }

  template<typename InS, typename OutS, typename InStr, typename OutStr,
    typename Property>
  TerminalIOANSILinux<InS, OutS, InStr, OutStr, Property>::setEchoForward() {
    if (!inited) throw BadModeError();

    if (echoInhibited==-1) return;

    termios currSettings;

    int temp=tcgetattr(fd,&currSettings);
    if (temp!=0) throw DeviceError();

    currSettings.c_lflag |=ECHO;

    tcsetattr(fd,TCSANOW,&currSettings); //Pray it works

    echoInhibited = -1;
  }

  template<typename InS, typename OutS, typename InStr, typename OutStr,
    typename Property>
  TerminalIOANSILinux<InS, OutS, InStr, OutStr, Property>::resetDeviceMode() {
    if (!inited) throw BadModeError();

    tcsetattr(fd,TCSANOW,&storedSettings); //Pray it works

    nonCanonicalMode = 0;
    echoInhibited = 0;
  }

  template<typename InS, typename OutS, typename InStr, typename OutStr,
    typename Property>
  TerminalIOANSILinux<InS, OutS, InStr, OutStr, Property>::getResolution() {
    if (!inited) throw BadModeError();

    struct winsize ws;
    int temp=ioctl(fd, TIOCGWINSZ, &ws);
    if (temp==-1) throw DeviceError();

    return MonitorResolution(ws.ws_col, ws.ws_row);
  }
}
