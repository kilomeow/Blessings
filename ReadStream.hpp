#pragma once

#include <string>

namespace Blessings_ns {
  template <class InputSymbol>
  class ReadStream {
    virtual InputSymbol getSymbol()=0;
  };
}
