#include "TIOAL_PropANSI_impl.hpp"
#include "../Symbol/Symbol.hpp"
#include "../Symbol/SymbolUTF8.hpp"

#include <unistd.h> //remove
#include <queue> //remove

using namespace std; //remove

namespace blessings {
  template<>
  queue<SymbolUTF8> TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI>::getSymbol(int ns) {
    fd_set rdfs;
    FD_ZERO(&rdfs);
    FD_SET(0, &rdfs);

    timeval tv;
    tv.tv_sec=0;
    tv.tv_usec=0;

    queue<SymbolUTF8> ret;

    if(select(1, &rdfs, NULL, NULL, &tv)) {
      ret.push(blessings::getSymbol<SymbolUTF8>(stdin));
    }

    return ret;
  }

  template class TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI>;
}
