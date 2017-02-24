#include <iostream>
#include <unistd.h>
#include <string>

#include "Symbol/SymbolUTF8.hpp"
#include "Symbol/Symbol.hpp"
#include "ANSILinux/TerminalIOANSILinux.hpp"
#include "Demos.hpp"

using namespace std;
using namespace blessings;

typedef TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI> TL;

int main() {
  TL term;

  term.Init();

  term.setNonCanonicalMode();
  term.setEchoInhibition();

  cout << term.getResolution().width << ' ' << term.getResolution().height << endl;

  term.resetDeviceMode();

  return 0;
}
