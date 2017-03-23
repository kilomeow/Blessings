#include "monitor_template_impl.hpp"
#include "monitor_template.hpp"
#include "symbol_utf8/symbol_utf8.hpp"
#include "property.hpp"

namespace blessings {
  template <typename InS, typename OutS, typename Prop>
  size_t MonitorTemplate<InS, OutS, Prop>::CELL_MEMORY_START = 512;
  template <typename InS, typename OutS, typename Prop>
  size_t MonitorTemplate<InS, OutS, Prop>::CELL_MEMORY_STEP = 256;
  
  template class MonitorTemplate<SymbolUTF8, SymbolUTF8, PropertyANSI>;
}
