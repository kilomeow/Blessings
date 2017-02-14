#pragma once

#include <string>
#include <cstdint>

#include "AdditionalStructs.hpp"

namespace Blessings_ns {
  template <class OutputSymbol, class Property>
  class WriteStream {
  public:
    virtual void print(OutputSymbol, Property)=0;

    virtual void clearScreen()=0;

    virtual void newLine()=0;

    virtual void moveCursor(int x, int y)=0;
    virtual CursorPos getCursorPos()=0;

    virtual void hideCursor()=0;
    virtual void showCursor()=0;

    virtual void saveCursorPos()=0;
    virtual void restoreCursorPos()=0;

    virtual void clearScreen()=0;

    virtual MonitorResolution getResolution()=0;
  };

  template <class OutputSymbol, class Property>
  class WriteStreamLinux : public WriteStream<OutputSymbol, Property> {};
}
