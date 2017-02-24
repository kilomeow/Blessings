#include "TIOAL_PropANSI_impl.hpp"
#include "../Symbol/Symbol.hpp"
#include "../Symbol/SymbolUTF8.hpp"

namespace blessings {
  template class TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI>;
}
