#pragma once

#include <string>

namespace blessings {
  template <class InS>
  class ReadStream {
    virtual InS getSymbol()=0;
  };
}
