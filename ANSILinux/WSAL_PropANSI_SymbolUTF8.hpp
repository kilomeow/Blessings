#pragma once

#include <cstdio>

#include "../SymbolUTF8.hpp"
#include "../WriteStream.hpp"
#include "WriteStreamANSILinux.hpp"

namespace Blessings_ns {
  template <>
  class WriteStreamANSILinux<SymbolUTF8, Property<ColorANSI> > :
    public WriteStream<SymbolUTF8> {
    FILE* file;
  public:
    class Error;

    WriteStreamANSILinux();

    virtual void write(OutputSymbol, PropertyGeneral*)=0;
    virtual void write(OutputSymbol)=0;
    virtual void write(char)=0;
    virtual void write(const char*)=0;
    virtual void write(std::string)=0;

    virtual void flush()=0;

    virtual PropertyType getPropertyType()=0;

    PropertyType getPropertyType() {return ColorType::ANSI;};

    //Pure ANSI/Linux methods
    void setNonCanonTerminalMode(); //rewrite!
    void resetTerminalMode(); //rewrite!

    void resetSGR();
  };
}
