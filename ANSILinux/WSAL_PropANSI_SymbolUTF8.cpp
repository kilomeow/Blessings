#include <string>
#include <cstdio>
#include "Termios.hpp"

#include "WSAL_PropANSI_SymbolUTF8.hpp"
#include "../Symbol.hpp"
#include "../SomeUTF8Symbols.hpp"
#include "../Error.hpp"

namespace Blessings_ns {
  using namespace Some_UTF8_symbols;
  using namespace Termios_ns;

  WriteStreamANSILinux<SymbolUTF8, Property<ColorANSI> >::WriteStreamANSILinux() {
    file=stdout;

    resetSGR();
  }

  void WriteStreamANSILinux<SymbolUTF8, Property<ColorANSI> >::newLine() {
    newLineSymbol.writeToFile(file);

    fflush(file);
  }

  void WriteStreamANSILinux<SymbolUTF8, Property<ColorANSI> >::moveCursor(int x, int y) {
    if(x==0 && y==0) return;

    int xAbs=x<0 ? -x : x;
    int yAbs=y<0 ? -y : y;

    std::string xAbsStr=std::to_string(xAbs);
    std::string yAbsStr=std::to_string(yAbs);

    if(x!=0) {
      CSISymbol.writeToFile(file);

      for(int i=0; i<xAbsStr.size(); ++i) {
        int res=fputc(xAbsStr[i], file);
        if(res==EOF) throw Error("file i/o error while moving cursor");
      }

      if(x<0) DSym.writeToFile(file);
      else CSym.writeToFile(file);
    }

    if(y!=0) {
      CSISymbol.writeToFile(file);

      for(int i=0; i<yAbsStr.size(); ++i) {
        int res=fputc(yAbsStr[i], file);
        if(res==EOF) throw Error("file i/o error while moving cursor");
      }

      if(y>0) ASym.writeToFile(file);
      else BSym.writeToFile(file);
    }

    fflush(file);
  }

  void WriteStreamANSILinux<SymbolUTF8, Property<ColorANSI> >::resetSGR() {
    CSISymbol.writeToFile(file);
    zero.writeToFile(file);
    mSym.writeToFile(file);

    fflush(file);
  };

  void WriteStreamANSILinux<SymbolUTF8, Property<ColorANSI> >::print(SymbolUTF8 sym,\
    PropertyGeneral* propRaw) {
    Property<ColorANSI>* prop=static_cast<Property<ColorANSI>* >(propRaw);

    resetSGR();

    if(prop->bold) {
      CSISymbol.writeToFile(file);
      one.writeToFile(file);
      mSym.writeToFile(file);
    }

    if(prop->italics) {
      CSISymbol.writeToFile(file);
      three.writeToFile(file);
      mSym.writeToFile(file);
    }

    CSISymbol.writeToFile(file);
    three.writeToFile(file);
    switch(prop->color.color) {
    case ColorANSI::BLACK:
      zero.writeToFile(file);
      break;
    case ColorANSI::RED:
      one.writeToFile(file);
      break;
    case ColorANSI::GREEN:
      two.writeToFile(file);
      break;
    case ColorANSI::YELLOW:
      three.writeToFile(file);
      break;
    case ColorANSI::BLUE:
      four.writeToFile(file);
      break;
    case ColorANSI::MAGENTA:
      five.writeToFile(file);
      break;
    case ColorANSI::CYAN:
      six.writeToFile(file);
      break;
    case ColorANSI::WHITE:
      seven.writeToFile(file);
      break;
    default:
      throw Error("bad color given");
    }
    mSym.writeToFile(file);

    sym.writeToFile(file);

    resetSGR();

    fflush(file);
  };

  void WriteStreamANSILinux<SymbolUTF8, Property<ColorANSI> >::setNonCanonTerminalMode() {
    termios newSettings;

    tcgetattr(0,&storedSettings);

    newSettings = storedSettings;

    newSettings.c_lflag &=~ICANON;
    newSettings.c_lflag &=~ECHO;
    newSettings.c_cc[VTIME] = 0;
    newSettings.c_cc[VMIN] = 0;

    tcsetattr(0,TCSANOW,&newSettings);
  }

  void WriteStreamANSILinux<SymbolUTF8, Property<ColorANSI> >::resetTerminalMode() {
    tcsetattr(0,TCSANOW,&storedSettings);
  }
}
