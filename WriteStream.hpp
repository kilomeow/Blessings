#pragma once

#include "AdditionalStructs.hpp"
#include "Symbol.hpp"

namespace Blessings_ns {
  template <class OutputSymbol>
  class WriteStream {
  public:
    virtual void print(OutputSymbol, PropertyGeneral*)=0;

    virtual void clearScreen()=0;

    virtual void newLine()=0;

    virtual void moveCursor(int x, int y)=0;
    virtual GridPos getCursorPos()=0;

    virtual void hideCursor()=0;
    virtual void showCursor()=0;

    virtual void saveCursorPos()=0;
    virtual void restoreCursorPos()=0;

    virtual MonitorResolution getResolution()=0;

    virtual int boldSupported()=0;
    virtual int italicsSupported()=0;

    virtual ColorType getColorType()=0;
  };
}
