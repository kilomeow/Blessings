#include <termios.h>
#include <cstdio>

#include "../Symbol/Symbol.hpp"
#include "../Symbol/SomeUTF8Symbols.hpp"
#include "TIOAL_PropANSI_SymbolUTF8.hpp"
#include "WriteStreamLinux.hpp"

namespace blessings {
  using namespace SomeUTF8Symbols;

  TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI>::TerminalIOANSILinux() {
    inited=false;
    noncanonicalMode=false;
    settingsStored=false;
  }

  TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI>::~TerminalIOANSILinux() {

  }

  void TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI>::Init(FILE* f) {
    try {
      file=f;

      ws=new WriteStreamLinux<SymbolUTF8>(f);
    }
    catch(...) {
      throw InitError();
    }

    inited=true;
    noncanonicalMode=false;
    settingsStored=false;
  }

  void TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI>::print(\
    SymbolUTF8 sym, Property* propRaw) {
    if(!isReady()) throw ReadinessError();

    if(propRaw==nullptr) throw ArgumentError();

    PropertyANSI* prop=static_cast<PropertyANSI* >(propRaw);

    try {
      if(prop->bold) {
        ws->write(CSISymbol);
        ws->write(one);
        ws->write(mSym);
      }

      if(prop->italics) {
        ws->write(CSISymbol);
        ws->write(three);
        ws->write(mSym);
      }

      CSISymbol.writeToFile(file);
      three.writeToFile(file);
      switch(prop->color.color) {
      case ColorANSI::BLACK:
        ws->write(zero);
        break;
      case ColorANSI::RED:
        ws->write(one);
        break;
      case ColorANSI::GREEN:
        ws->write(two);
        break;
      case ColorANSI::YELLOW:
        ws->write(three);
        break;
      case ColorANSI::BLUE:
        ws->write(four);
        break;
      case ColorANSI::MAGENTA:
        ws->write(five);
        break;
      case ColorANSI::CYAN:
        ws->write(six);
        break;
      case ColorANSI::WHITE:
        ws->write(seven);
        break;
      default:
        throw ArgumentError();
      }
      ws->write(mSym);

      ws->write(sym);

      resetSGR();

      ws->flush();
    }
    catch(...) {
      throw IOError();
    }
  }

  void TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI>::print(\
    SymbolUTF8 sym) {
    if(!isReady()) throw ReadinessError();

    try {
      ws->write(sym);

      ws->flush();
    }
    catch(...) {
      throw IOError();
    }
  }

  void TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI>::clearScreen() {
    if(!isReady()) throw ReadinessError();

    try {
      ws->write(CSISymbol);
      ws->write(two);
      ws->write(JSym);

      ws->flush();
    }
    catch(...) {
      throw IOError();
    }
  }

  void TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI>::newLine() {
    if(!isReady()) throw ReadinessError();

    try {
      ws->write(newLineSymbol);

      ws->flush();
    }
    catch(...) {
      throw IOError();
    }
  }

  void TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI>::moveCursor(int x, int y) {
    if(!isReady()) throw ReadinessError();

    try {
      if(x==0 && y==0) return;

      int xAbs=x<0 ? -x : x;
      int yAbs=y<0 ? -y : y;

      std::string xAbsStr=std::to_string(xAbs);
      std::string yAbsStr=std::to_string(yAbs);

      if(x!=0) {
        ws->write(CSISymbol);

        for(int i=0; i<xAbsStr.size(); ++i) {
          ws->write(xAbsStr[i]);
        }

        if(x<0) ws->write(DSym);
        else ws->write(CSym);
      }

      if(y!=0) {
        ws->write(CSISymbol);

        for(int i=0; i<yAbsStr.size(); ++i) {
          ws->write(yAbsStr[i]);
        }

        if(y>0) ws->write(ASym);
        else ws->write(BSym);
      }

      ws->flush();
    }
    catch(...) {
      throw IOError();
    }
  }

  void TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI>::moveCursorTo(int x, int y) {
    if(!isReady()) throw ReadinessError();

    if(x<=0 || y<=0) throw ArgumentError();

    try {
      std::string xStr=std::to_string(x);
      std::string yStr=std::to_string(y);

      ws->write(CSISymbol);

      for(int i=0; i<yStr.size(); ++i) {
        ws->write(yStr[i]);
      }

      ws->write(semicolon);

      for(int i=0; i<xStr.size(); ++i) {
        ws->write(xStr[i]);
      }

      ws->write(HSym);

      ws->flush();
    }
    catch(...) {
      throw IOError();
    }
  }

  void TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI>::resetSGR() {
    if(!isReady()) throw ReadinessError();

    try {
      ws->write(CSISymbol);
      ws->write(zero);
      ws->write(mSym);

      ws->flush();
    }
    catch(...) {
      throw IOError();
    }
  }

  void TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI>::setDeviceReady() {
    if(!inited) throw UninitedStateError();

    if(noncanonicalMode==true) return;

    termios newSettings;

    int fd=fileno(file);
    if(fd==-1) throw DeviceError();

    int temp=tcgetattr(fd,&storedSettings);
    if(temp!=0) throw DeviceError();

    newSettings = storedSettings;

    newSettings.c_lflag &=~ICANON;
    newSettings.c_lflag &=~ECHO;
    newSettings.c_cc[VTIME] = 0;
    newSettings.c_cc[VMIN] = 0;

    tcsetattr(fd,TCSANOW,&newSettings); //Pray it works

    noncanonicalMode=true;
    settingsStored=true;

    resetSGR();
  }

  void TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI>::resetDeviceMode() {
    if(!inited) throw UninitedStateError();
    if(!settingsStored) throw NoStoredSettingsError();

    if(noncanonicalMode==false) return;

    int fd=fileno(file);
    if(fd==-1) throw DeviceError();

    tcsetattr(fd,TCSANOW,&storedSettings); //And here pray too

    noncanonicalMode=false;
  }
}
