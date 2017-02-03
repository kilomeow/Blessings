#pragma once

namespace Blessings_ns {
  template <class OutputSymbol, class Color>
  class WriteStream {
    virtual write(OutputSymbol, Color)=0;
  };
}
