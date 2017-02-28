#pragma once

#include <string>

namespace blessings {
  template <class OutS>
  class WriteStream {
  public:
    virtual void write(OutS)=0;
    virtual void write(char)=0;
    virtual void write(const char*)=0;
    virtual void write(std::string)=0;

    virtual void flush()=0;
  };
}
