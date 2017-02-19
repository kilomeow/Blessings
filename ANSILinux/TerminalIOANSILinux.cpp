#include "Termios.hpp"
#include <cstdio>
#include "../Symbol/Symbol.hpp"
#include "../Symbol/SomeUTF8Symbols.hpp"

namespace Blessings_ns {
  using namespace Some_UTF8_symbols;
  using namespace Termios_ns;

  TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI>::TerminalIOANSILinux() {
    inited=false;
    noncanonicalMode=false;
  }

  void TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI>::Init(FILE* f) {
    file=f;

    ws=&WriteStreamANSILinux<SymbolUTF8, PropertyANSI>(f);
  }

  void TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI>::print(\
    SymbolUTF8 sym, PropertyGeneral* prop) {
    if(!isReady()) throw Error("attempt to print() in not ready terminal");

    ws->write(sym, prop);

    ws->flush();
  }

  void TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI>::clearScreen() {
    if(!isReady()) throw Error("attempt to clearScreen() in not ready terminal");

    ws->write(CSISymbol);
    ws->write(two);
    ws->write(JSym);

    ws->flush();
  }

  void TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI>::newLine() {
    if(!isReady()) throw Error("attempt to newLine() in not ready terminal");

    ws->write(newLineSymbol, prop);

    ws->flush();
  }

  void TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI>::moveCursor(int x, int y) {
    if(!isReady()) throw Error("attempt to moveCursor() in not ready terminal");

    if(x==0 && y==0) return;

    int xAbs=x<0 ? -x : x;
    int yAbs=y<0 ? -y : y;

    std::string xAbsStr=std::to_string(xAbs);
    std::string yAbsStr=std::to_string(yAbs);

    if(x!=0) {
      ws->wirte(CSISymbol);

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

  void TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI>::resetSGR() {
    if(!isReady()) throw Error("attempt to resetSGR() in not ready terminal");

    ws->write(CSISymbol);
    ws->write(zero);
    ws->write(mSym);

    ws->flush();
  }

  void TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI>::setDeviceReady() {
    termios newSettings;

    tcgetattr(0,&storedSettings);

    newSettings = storedSettings;

    newSettings.c_lflag &=~ICANON;
    newSettings.c_lflag &=~ECHO;
    newSettings.c_cc[VTIME] = 0;
    newSettings.c_cc[VMIN] = 0;

    tcsetattr(0,TCSANOW,&newSettings);
  }

  void resetDeviceMode() {
    tcsetattr(0,TCSANOW,&storedSettings);
  }
}
