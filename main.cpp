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
  laser();

  return 0;
}
