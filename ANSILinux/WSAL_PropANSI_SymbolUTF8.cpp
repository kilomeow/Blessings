#include <string>
#include <cstdio>

#include "WSAL_PropANSI_SymbolUTF8.hpp"
#include "../Symbol.hpp"
#include "../Error.hpp"

namespace Blessings_ns {
  using namespace Some_UTF8_symbols;
  using namespace Termios_ns;

  WriteStreamANSILinux<SymbolUTF8, Property<ColorANSI> >::WriteStreamANSILinux() {
    file=stdout;
  }

  void WriteStreamANSILinux<SymbolUTF8, Property<ColorANSI> >::write(SymbolUTF8 sym,\
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
}
