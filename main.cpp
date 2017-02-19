#include <iostream>
#include <unistd.h>
#include <string>

#include "Symbol/SymbolUTF8.hpp"
#include "Symbol/Symbol.hpp"
#include "ANSILinux/TerminalIOANSILinux.hpp"

using namespace std;
using namespace Blessings;

void f(string s) {
  TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI> term;

  term.Init();
  term.setDeviceReady();

  term.clearScreen();

  int colorNum=1;
  PropertyANSI prop;
  prop.bold=true;
  prop.italics=true;
  prop.color=static_cast<ColorANSI::ColorT>(1);

  term.moveCursor(6,7);

  for(int i=0; i<s.size(); ++i) {
    sleep(1);
    term.print(SymbolUTF8(string(1, s[i])), &prop);

    colorNum++;
    if(colorNum==7) colorNum=1;
    prop.color=static_cast<ColorANSI::ColorT>(colorNum);
  }

  term.newLine();

  term.resetDeviceMode();
}

int main() {
  f("Ram pidor");
  return 0;
}
