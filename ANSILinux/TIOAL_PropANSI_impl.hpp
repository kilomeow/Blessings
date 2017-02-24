#include <cstdio>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#include "../Symbol/SomeUTF8Symbols.hpp"
#include "../Symbol/Symbol.hpp"
#include "TIOAL_PropANSI.hpp"
#include "WriteStreamLinux.hpp"

namespace blessings {
  template<class InS, class OutS>
  TerminalIOANSILinux<InS, OutS, PropertyANSI>::TerminalIOANSILinux() {
    inited=false;
    noncanonicalMode=0;
    echoInhibition=0;
  }

  template<class InS, class OutS>
  TerminalIOANSILinux<InS, OutS, PropertyANSI>::~TerminalIOANSILinux() {
    if(isReady()) {
      resetSGR();
      showCursor();
    }

    if(noncanonicalMode) {
      int fd=fileno(file);
      if(fd==-1) return;

      tcsetattr(fd,TCSANOW,&storedSettings);
    }
  }

  template<class InS, class OutS>
  void TerminalIOANSILinux<InS, OutS, PropertyANSI>::Init(std::string path) {
    if(path=="") fd=open(ttyname(1), O_RDWR|O_APPEND);
    else fd=open(path.c_str(), O_RDWR|O_APPEND);

    std::cout << 1 << std::endl;
    if(fd==-1) throw InitError();

    file=fdopen(fd, "rw+");
    if(file==nullptr) throw InitError();
    std::cout << 1 << std::endl;

    try {
      ws=new WriteStreamLinux<SymbolUTF8>(file);
    }
    catch(...) {
      throw InitError();
    }

    inited=true;
    noncanonicalMode=false;
  }

  template<class InS, class OutS>
  void TerminalIOANSILinux<InS, OutS, PropertyANSI>::print(\
    OutS sym, Property* propRaw) {
    if(!isReady()) throw ReadinessError();

    if(propRaw==nullptr) throw ArgumentError();

    PropertyANSI* prop=static_cast<PropertyANSI* >(propRaw);

    try {
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
    catch(...) {
      throw IOError();
    }
  }

  template<class InS, class OutS>
  void TerminalIOANSILinux<InS, OutS, PropertyANSI>::print(\
    OutS sym) {
    if(!isReady()) throw ReadinessError();

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
    if(!isReady()) throw ReadinessError();

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
    if(!isReady()) throw ReadinessError();

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
    if(!isReady()) throw ReadinessError();

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
    if(!isReady()) throw ReadinessError();

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
    if(!isReady()) throw ReadinessError();

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
    if(!isReady()) throw ReadinessError();

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
    if(!isReady()) throw ReadinessError();

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
    if(!isReady()) throw ReadinessError();

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
    if(!isReady()) throw ReadinessError();

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
  void TerminalIOANSILinux<InS, OutS, PropertyANSI>::setDeviceReady() {
    if(!inited) throw UninitedStateError();

    if(noncanonicalMode==true) return;

    termios newSettings;

    int temp=tcgetattr(fd,&storedSettings);
    if(temp!=0) throw DeviceError();

    newSettings = storedSettings;

    newSettings.c_lflag &=~ICANON;
    newSettings.c_lflag &=~ECHO;
    newSettings.c_cc[VTIME] = 0;
    newSettings.c_cc[VMIN] = 0;

    tcsetattr(fd,TCSANOW,&newSettings); //Pray it works

    noncanonicalMode=true;

    resetSGR();
  }

  template<class InS, class OutS>
  void TerminalIOANSILinux<InS, OutS, PropertyANSI>::resetDeviceMode() {
    if(!inited) throw UninitedStateError();

    if(noncanonicalMode==false) return;

    tcsetattr(fd,TCSANOW,&storedSettings); //And here pray too

    noncanonicalMode=false;
  }
}
