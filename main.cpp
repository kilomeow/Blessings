#include <iostream>

#include "Blessings.hpp"
#include "SymbolUTF8.hpp"
#include "WSL/WSL_ANSI_SymbolUTF8.hpp"

using namespace std;
using namespace Blessings_ns;

int main() {
  auto x=getSym<SymbolUTF8>(stdin);
  cout << x << ' ' << x.getSize() << endl;

  WriteStreamLinux<SymbolUTF8, Property<ColorANSI> > ws;
  ws.clearScreen();

  return 0;
}
