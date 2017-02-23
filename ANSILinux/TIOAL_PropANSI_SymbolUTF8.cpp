#include "TIOAL_PropANSI_impl.hpp"
#include "../Symbol/Symbol.hpp"
#include "../Symbol/SymbolUTF8.hpp"

#include <unistd.h> //remove
#include <vector> //remove

using namespace std; //remove

namespace blessings {
  template<>
  vector<SymbolUTF8> TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI>::getSymbol() {
    fd_set rdfs;
    FD_ZERO(&rdfs);
    FD_SET(0, &rdfs);

    timeval tv;
    tv.tv_sec=0;
    tv.tv_usec=0;

    vector<SymbolUTF8> ret;

    if(select(1, &rdfs, NULL, NULL, &tv)) {
      ret.push_back(blessings::getSymbol<SymbolUTF8>(stdin));
    }

    return ret;
  }

  template class TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI>;
}
