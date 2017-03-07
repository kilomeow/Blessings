#include "monitor_impl.hpp"
#include "monitor.hpp"
#include "symbol_utf8/symbol_utf8.hpp"
#include "property.hpp"

namespace blessings {
  template class Monitor<SymbolUTF8, SymbolUTF8, PropertyANSI>;

  template <typename InS, typename OutS, typename Prop>
  bool Monitor<InS, OutS, Prop>::Cell::hardopt=false;
}
