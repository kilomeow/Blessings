#include "monitor_template_impl.hpp"
#include "monitor_template.hpp"
#include "symbol_utf8/symbol_utf8.hpp"
#include "property.hpp"

namespace blessings {
  template <typename InS, typename OutS, typename Prop>
  bool MonitorTemplate<InS, OutS, Prop>::Cell::hardopt=false;
  
  template class MonitorTemplate<SymbolUTF8, SymbolUTF8, PropertyANSI>;
}
