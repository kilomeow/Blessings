#include "write_stream_linux_impl.hpp"
#include "write_stream_linux.hpp"
#include "../symbol_utf8/symbol_utf8.hpp"

namespace blessings {
  template void WriteStreamLinux::write(const SymbolUTF8& sym);
}
