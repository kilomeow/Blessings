#include "terminal_io_ansi_linux_property_ansi_impl.hpp"
#include "terminal_io_ansi_linux_property_ansi.hpp"
#include "../symbol/symbol.hpp"
#include "../symbol/symbol_utf8.hpp"

//Remove after Rama writes ReadStream
#include <sys/select.h>

namespace blessings {
  //Remove after Rama writes ReadStream
  template <>
  std::queue<SymbolUTF8> TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI>::getSymbol(int n) {
    fd_set readfds;
    FD_ZERO(&readfds);
		FD_SET(0, &readfds);

    timeval tv;
    tv.tv_sec = 0;
		tv.tv_usec = 0;

    std::queue<SymbolUTF8> ret;
    int i=0;
    while (select(1, &readfds, NULL, NULL, &tv) && i<n) {
      ++i;

      ret.push(readSymbol<SymbolUTF8>(stdin));
    }

    return ret;
  }

  template <>
  void TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI>::clearInputBuffer() {
    fseek(stdin, 0, SEEK_END);
  }

  template class TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI>;
}
