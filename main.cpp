#include <iostream>
#include <unistd.h>
#include <string>

#include "Symbol/SymbolUTF8.hpp"
#include "Symbol/Symbol.hpp"
#include "ANSILinux/TerminalIOANSILinux.hpp"
#include "demos.hpp"

using namespace std;
using namespace blessings;

typedef TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI> TL;

int main() {
  StringUTF8 str;
  cin >> str;

  TL term;

  term.Init();
  term.setDeviceReady();

  term.clearScreen();
  term.moveCursorTo(1,1);

  PropertyANSI prop;
  prop.bold=true;
  prop.italics=true;
  prop.color=ColorANSI::WHITE;
  prop.backgroundColor=static_cast<ColorANSI::ColorT>(1);

  int col=1;
  for(int i=0; i<str.size(); ++i) {
    term.print(str[i], &prop);

    if(static_cast<int>(prop.backgroundColor.color)==7) {
      prop.backgroundColor=static_cast<ColorANSI::ColorT>(1);
      col=1;
    }
    else {
      ++col;
      prop.backgroundColor=static_cast<ColorANSI::ColorT>(col);
    }
  }

  term.resetDeviceMode();

  return 0;
}
