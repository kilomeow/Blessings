#pragma once

#include "monitor_template.hpp"
#include "symbol_utf8/symbol_utf8.hpp"
#include "property.hpp"

namespace blessings {
  typedef MonitorTemplate<SymbolUTF8, SymbolUTF8, PropertyANSI> Monitor;
}
