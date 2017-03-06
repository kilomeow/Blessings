#include "monitor_impl.hpp"
#include "monitor.hpp"
#include "symbol/symbol_utf8.hpp"

namespace blessings {
  template class Monitor<SymbolUTF8, SymbolUTF8>;

  template <class Symbol>
  bool MonitorCell<Symbol>::hardopt=false;
}
