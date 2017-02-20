#pragma once

#include <string>

namespace blessings {
  template <class InputSymbol>
  class ReadStream {
    virtual InputSymbol getSymbol()=0;
  };
}
