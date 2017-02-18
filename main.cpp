#include <iostream>
#include <unistd.h>

#include "Blessings.hpp"
#include "SymbolUTF8.hpp"
#include "WSAL/WSAL_DefaultProp_SymbolUTF8.hpp"

using namespace std;
using namespace Blessings_ns;

void f(string s) {
  Property<ColorANSI> prop;
  prop.bold=true;
  prop.italics=true;
  prop.color=ColorANSI::RED;

  WriteStreamANSILinux<SymbolUTF8, Property<ColorANSI> > ws;
  ws.setNonCanonTerminalMode();

  ws.clearScreen();
  ws.moveCursor(5,6);

  int colorPtr=1;
  for(int i=0; i<s.size(); ++i) {
    sleep(1);
    ws.print(SymbolUTF8(string(1, s[i])), &prop);
    colorPtr++;
    if(colorPtr>=7) colorPtr=1;
    prop.color=static_cast<ColorANSI::ColorName>(colorPtr);
  }

  ws.moveCursor(-6-s.size(),-6);

  ws.resetTerminalMode();
}

int main() {
  f(string("Roma pidor"));

  return 0;
}
