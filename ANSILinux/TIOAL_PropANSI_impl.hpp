#include <cstdio>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include "../Symbol/SomeUTF8Symbols.hpp"
#include "../Symbol/Symbol.hpp"
#include "TIOAL_PropANSI.hpp"
#include "WriteStreamLinux.hpp"
#include "../AdditionalStructs.hpp"

namespace blessings {
  template<class InS, class OutS>
  TerminalIOANSILinux<InS, OutS, PropertyANSI>::TerminalIOANSILinux() {
    inited=false;
    nonCanonicalMode=0;
    echoInhibited=0;
  }

  template<class InS, class OutS>
  TerminalIOANSILinux<InS, OutS, PropertyANSI>::~TerminalIOANSILinux() {
    if(inited) {
      setEchoInhibition();
      resetSGR();
      showCursor();
      resetDeviceMode();
    }
  }

  template<class InS, class OutS>
  void TerminalIOANSILinux<InS, OutS, PropertyANSI>::Init(std::string path) {
    if(inited) throw ReInitAttemptError();

    if(path=="") fd=open(ttyname(1), O_RDWR|O_APPEND);
    else fd=open(path.c_str(), O_RDWR|O_APPEND);

    if(fd==-1) throw InitError();

    file=fdopen(fd, "rw+");
    if(file==nullptr) {
      close(fd);
      throw InitError();
    }

    try {
      ws=new WriteStreamLinux<SymbolUTF8>(file);
    }
    catch(...) {
      fclose(file);
      throw InitError();
    }

    int temp=tcgetattr(fd,&storedSettings);
    if(temp!=0) {
      fclose(file);
      throw InitError();
    }

    termios tempSettings=storedSettings;
    tempSettings.c_lflag &=~ECHO;
    tcsetattr(fd,TCSANOW,&tempSettings); //Pray it works

    try {
      ws->write(SymbolTable<OutS>::ESCSymbol);
      ws->write(SymbolTable<OutS>::openBracket);
      ws->write(SymbolTable<OutS>::zero);
      ws->write(SymbolTable<OutS>::mSym);

      ws->flush();
    }
    catch(...) {
      tcsetattr(fd,TCSANOW,&storedSettings);
      fclose(file);
      throw InitError();
    }

    tcsetattr(fd,TCSANOW,&storedSettings); //Pray it works

    inited=true;
  }

  template<class InS, class OutS>
  void TerminalIOANSILinux<InS, OutS, PropertyANSI>::print(\
    OutS sym, Property* propRaw) {
    if(!inited) throw BadModeError();
    if(echoInhibited!=1) throw BadModeError();

    if(propRaw==nullptr) throw ArgumentError();

    PropertyANSI* prop=static_cast<PropertyANSI* >(propRaw);

    try {
      if(prop->empty) print(sym);
      else {
        if(prop->bold) {
          ws->write(SymbolTable<OutS>::ESCSymbol);
          ws->write(SymbolTable<OutS>::openBracket);
          ws->write(SymbolTable<OutS>::one);
          ws->write(SymbolTable<OutS>::mSym);
        }

        if(prop->italics) {
          ws->write(SymbolTable<OutS>::ESCSymbol);
          ws->write(SymbolTable<OutS>::openBracket);
          ws->write(SymbolTable<OutS>::three);
          ws->write(SymbolTable<OutS>::mSym);
        }

        ws->write(SymbolTable<OutS>::ESCSymbol);
        ws->write(SymbolTable<OutS>::openBracket);
        ws->write(SymbolTable<OutS>::three);
        switch(prop->color.color) {
        case ColorANSI::BLACK:
          ws->write(SymbolTable<OutS>::zero);
          break;
        case ColorANSI::RED:
          ws->write(SymbolTable<OutS>::one);
          break;
        case ColorANSI::GREEN:
          ws->write(SymbolTable<OutS>::two);
          break;
        case ColorANSI::YELLOW:
          ws->write(SymbolTable<OutS>::three);
          break;
        case ColorANSI::BLUE:
          ws->write(SymbolTable<OutS>::four);
          break;
        case ColorANSI::MAGENTA:
          ws->write(SymbolTable<OutS>::five);
          break;
        case ColorANSI::CYAN:
          ws->write(SymbolTable<OutS>::six);
          break;
        case ColorANSI::WHITE:
          ws->write(SymbolTable<OutS>::seven);
          break;
        default:
          throw ArgumentError();
        }
        ws->write(SymbolTable<OutS>::mSym);

        ws->write(SymbolTable<OutS>::ESCSymbol);
        ws->write(SymbolTable<OutS>::openBracket);
        ws->write(SymbolTable<OutS>::four);
        switch(prop->backgroundColor.color) {
        case ColorANSI::BLACK:
          ws->write(SymbolTable<OutS>::zero);
          break;
        case ColorANSI::RED:
          ws->write(SymbolTable<OutS>::one);
          break;
        case ColorANSI::GREEN:
          ws->write(SymbolTable<OutS>::two);
          break;
        case ColorANSI::YELLOW:
          ws->write(SymbolTable<OutS>::three);
          break;
        case ColorANSI::BLUE:
          ws->write(SymbolTable<OutS>::four);
          break;
        case ColorANSI::MAGENTA:
          ws->write(SymbolTable<OutS>::five);
          break;
        case ColorANSI::CYAN:
          ws->write(SymbolTable<OutS>::six);
          break;
        case ColorANSI::WHITE:
          ws->write(SymbolTable<OutS>::seven);
          break;
        default:
          throw ArgumentError();
        }
        ws->write(SymbolTable<OutS>::mSym);

        ws->write(sym);

        resetSGR();

        ws->flush();
      }
    }
    catch(...) {
      throw IOError();
    }
  }

  template<class InS, class OutS>
  void TerminalIOANSILinux<InS, OutS, PropertyANSI>::print(\
    OutS sym) {
    if(!inited) throw BadModeError();
    if(echoInhibited!=1) throw BadModeError();

    try {
      ws->write(sym);

      ws->flush();
    }
    catch(...) {
      throw IOError();
    }
  }

  template<class InS, class OutS>
  void TerminalIOANSILinux<InS, OutS, PropertyANSI>::clearScreen() {
    if(!inited) throw BadModeError();
    if(echoInhibited!=1) throw BadModeError();

    try {
      ws->write(SymbolTable<OutS>::ESCSymbol);
      ws->write(SymbolTable<OutS>::openBracket);
      ws->write(SymbolTable<OutS>::two);
      ws->write(SymbolTable<OutS>::JSym);

      ws->flush();
    }
    catch(...) {
      throw IOError();
    }
  }

  template<class InS, class OutS>
  void TerminalIOANSILinux<InS, OutS, PropertyANSI>::newLine() {
    if(!inited) throw BadModeError();
    if(echoInhibited!=1) throw BadModeError();

    try {
      ws->write(SymbolTable<OutS>::newLineSymbol);

      ws->flush();
    }
    catch(...) {
      throw IOError();
    }
  }

  template<class InS, class OutS>
  void TerminalIOANSILinux<InS, OutS, PropertyANSI>::moveCursor(int x, int y) {
    if(!inited) throw BadModeError();
    if(echoInhibited!=1) throw BadModeError();

    try {
      if(x==0 && y==0) return;

      int xAbs=x<0 ? -x : x;
      int yAbs=y<0 ? -y : y;

      std::string xAbsStr=std::to_string(xAbs);
      std::string yAbsStr=std::to_string(yAbs);

      if(x!=0) {
        ws->write(SymbolTable<OutS>::ESCSymbol);
        ws->write(SymbolTable<OutS>::openBracket);

        for(int i=0; i<xAbsStr.size(); ++i) {
          ws->write(xAbsStr[i]);
        }

        if(x<0) ws->write(SymbolTable<OutS>::DSym);
        else ws->write(SymbolTable<OutS>::CSym);
      }

      if(y!=0) {
        ws->write(SymbolTable<OutS>::ESCSymbol);
        ws->write(SymbolTable<OutS>::openBracket);

        for(int i=0; i<yAbsStr.size(); ++i) {
          ws->write(yAbsStr[i]);
        }

        if(y>0) ws->write(SymbolTable<OutS>::ASym);
        else ws->write(SymbolTable<OutS>::BSym);
      }

      ws->flush();
    }
    catch(...) {
      throw IOError();
    }
  }

  template<class InS, class OutS>
  void TerminalIOANSILinux<InS, OutS, PropertyANSI>::moveCursorTo(int x, int y) {
    if(!inited) throw BadModeError();
    if(echoInhibited!=1) throw BadModeError();

    if(x<=0 || y<=0) throw ArgumentError();

    try {
      std::string xStr=std::to_string(x);
      std::string yStr=std::to_string(y);

      ws->write(SymbolTable<OutS>::ESCSymbol);
      ws->write(SymbolTable<OutS>::openBracket);

      for(int i=0; i<yStr.size(); ++i) {
        ws->write(yStr[i]);
      }

      ws->write(SymbolTable<OutS>::semicolon);

      for(int i=0; i<xStr.size(); ++i) {
        ws->write(xStr[i]);
      }

      ws->write(SymbolTable<OutS>::HSym);

      ws->flush();
    }
    catch(...) {
      throw IOError();
    }
  }

  template<class InS, class OutS>
  void TerminalIOANSILinux<InS, OutS, PropertyANSI>::resetSGR() {
    if(!inited) throw BadModeError();
    if(echoInhibited!=1) throw BadModeError();

    try {
      ws->write(SymbolTable<OutS>::ESCSymbol);
      ws->write(SymbolTable<OutS>::openBracket);
      ws->write(SymbolTable<OutS>::zero);
      ws->write(SymbolTable<OutS>::mSym);

      ws->flush();
    }
    catch(...) {
      throw IOError();
    }
  }

  template<class InS, class OutS>
  void TerminalIOANSILinux<InS, OutS, PropertyANSI>::hideCursor() {
    if(!inited) throw BadModeError();
    if(echoInhibited!=1) throw BadModeError();

    try {
      ws->write(SymbolTable<OutS>::ESCSymbol);
      ws->write(SymbolTable<OutS>::openBracket);
      ws->write(SymbolTable<OutS>::question);
      ws->write(SymbolTable<OutS>::two);
      ws->write(SymbolTable<OutS>::five);
      ws->write(SymbolTable<OutS>::lSym);

      ws->flush();
    }
    catch(...) {
      throw IOError();
    }
  }

  template<class InS, class OutS>
  void TerminalIOANSILinux<InS, OutS, PropertyANSI>::showCursor() {
    if(!inited) throw BadModeError();
    if(echoInhibited!=1) throw BadModeError();

    try {
      ws->write(SymbolTable<OutS>::ESCSymbol);
      ws->write(SymbolTable<OutS>::openBracket);
      ws->write(SymbolTable<OutS>::question);
      ws->write(SymbolTable<OutS>::two);
      ws->write(SymbolTable<OutS>::five);
      ws->write(SymbolTable<OutS>::hSym);

      ws->flush();
    }
    catch(...) {
      throw IOError();
    }
  }

  template<class InS, class OutS>
  void TerminalIOANSILinux<InS, OutS, PropertyANSI>::saveCursorPos() {
    if(!inited) throw BadModeError();
    if(echoInhibited!=1) throw BadModeError();

    try {
      ws->write(SymbolTable<OutS>::ESCSymbol);
      ws->write(SymbolTable<OutS>::openBracket);
      ws->write(SymbolTable<OutS>::sSym);

      ws->flush();
    }
    catch(...) {
      throw IOError();
    }
  }

  template<class InS, class OutS>
  void TerminalIOANSILinux<InS, OutS, PropertyANSI>::restoreCursorPos() {
    if(!inited) throw BadModeError();
    if(echoInhibited!=1) throw BadModeError();

    try {
      ws->write(SymbolTable<OutS>::ESCSymbol);
      ws->write(SymbolTable<OutS>::openBracket);
      ws->write(SymbolTable<OutS>::uSym);

      ws->flush();
    }
    catch(...) {
      throw IOError();
    }
  }

  template<class InS, class OutS>
  void TerminalIOANSILinux<InS, OutS, PropertyANSI>::setNonCanonicalMode() {
    if(!inited) throw BadModeError();

    if(nonCanonicalMode==1) return;

    termios currSettings;

    int temp=tcgetattr(fd,&currSettings);
    if(temp!=0) throw DeviceError();

    currSettings.c_lflag &=~ICANON;
    currSettings.c_cc[VTIME] = 0;
    currSettings.c_cc[VMIN] = 0;

    tcsetattr(fd,TCSANOW,&currSettings); //Pray it works

    nonCanonicalMode=1;
  }

  template<class InS, class OutS>
  void TerminalIOANSILinux<InS, OutS, PropertyANSI>::setCanonicalMode() {
    if(!inited) throw BadModeError();

    if(nonCanonicalMode==-1) return;

    termios currSettings;

    int temp=tcgetattr(fd,&currSettings);
    if(temp!=0) throw DeviceError();

    currSettings.c_lflag |=ICANON;

    tcsetattr(fd,TCSANOW,&currSettings); //Pray it works

    nonCanonicalMode=-1;
  }

  template<class InS, class OutS>
  void TerminalIOANSILinux<InS, OutS, PropertyANSI>::setEchoInhibition() {
    if(!inited) throw BadModeError();

    if(echoInhibited==1) return;

    termios currSettings;

    int temp=tcgetattr(fd,&currSettings);
    if(temp!=0) throw DeviceError();

    currSettings.c_lflag &=~ECHO;

    tcsetattr(fd,TCSANOW,&currSettings); //Pray it works

    echoInhibited=1;
  }

  template<class InS, class OutS>
  void TerminalIOANSILinux<InS, OutS, PropertyANSI>::setEchoForward() {
    if(!inited) throw BadModeError();

    if(echoInhibited==-1) return;

    termios currSettings;

    int temp=tcgetattr(fd,&currSettings);
    if(temp!=0) throw DeviceError();

    currSettings.c_lflag |=ECHO;

    tcsetattr(fd,TCSANOW,&currSettings); //Pray it works

    echoInhibited=-1;
  }

  template<class InS, class OutS>
  void TerminalIOANSILinux<InS, OutS, PropertyANSI>::resetDeviceMode() {
    if(!inited) throw BadModeError();

    tcsetattr(fd,TCSANOW,&storedSettings); //Pray it works

    nonCanonicalMode=0;
    echoInhibited=0;
  }

  template<class InS, class OutS>
  MonitorResolution TerminalIOANSILinux<InS, OutS, PropertyANSI>::getResolution() {
    if(!inited) throw BadModeError();

    struct winsize ws;
    int temp=ioctl(fd, TIOCGWINSZ, &ws);
    if(temp==-1) throw DeviceError();

    return MonitorResolution(ws.ws_col, ws.ws_row);
  }
}
