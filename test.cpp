#include <iostream>
#include <string>

#include "Symbol/SymbolUTF8.hpp"
#include "Symbol/Symbol.hpp"
#include "ANSILinux/TerminalIOANSILinux.hpp"
#include "Monitor.cpp"

using namespace std;
using namespace blessings;

typedef TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI> TL;
typedef Monitor<SymbolUTF8, SymbolUTF8> M;

int main() {
  TL * term;

  term->Init();

  term->setNonCanonicalMode();
  term->setEchoInhibition();

  M monitor(term, 256);

  monitor.setResolution(10, 10);

  return 0;
}
