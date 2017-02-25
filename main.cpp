#include <iostream>
#include <unistd.h>
#include <string>

#include "Symbol/SymbolUTF8.hpp"
#include "Symbol/Symbol.hpp"
#include "ANSILinux/TerminalIOANSILinux.hpp"
#include "Demos.hpp"
#include "Monitor.hpp"

using namespace std;
using namespace blessings;

typedef TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI> TL;
typedef Monitor<SymbolUTF8, SymbolUTF8> MonUTF8;

int main() {
  TL term;

  term.Init();

  term.setNonCanonicalMode();
  term.setEchoInhibition();

  term.resetDeviceMode();

  return 0;
}
