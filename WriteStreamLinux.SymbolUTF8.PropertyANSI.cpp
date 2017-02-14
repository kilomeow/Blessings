#include <cstdio>
#include <string>

#include "WriteStreamLinux.hpp"
#include "Symbol.hpp"

namespace Blessings_ns {
  WriteStreamLinux<SymbolUTF8, PropertyANSI>::WriteStreamLinux() {
    file=stdout;

    CSISymbol.writeToFile(file);
    
  }

  void WriteStreamLinux<SymbolUTF8, PropertyANSI>::print(SymbolUTF8 sym, PropertyANSI prop) {

  }
}
