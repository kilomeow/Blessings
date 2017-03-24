#pragma once

#include "linux/ANSI/terminal_io_ansi_linux.hpp"
#include "symbol_utf8/symbol_utf8.hpp"
#include "property.hpp"

namespace blessings {
  typedef TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI> Terminal;
}
