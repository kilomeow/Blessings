#pragma once

#include <string>

namespace Blessings {
  template <class InputSymbol>
  class ReadStream {
    virtual InputSymbol getSymbol()=0;
  };
}
