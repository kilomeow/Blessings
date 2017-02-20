#pragma once

#include "Symbol/Symbol.hpp"
#include "WriteStream.hpp"
#include "ReadStream.hpp"
#include "AdditionalStructs.hpp"

namespace blessings {
  template <class InS, class OutS>
  class TerminalIO {
  public:
    //Device info
    virtual MonitorResolution getResolution()=0;
    virtual GridPos getCursorPos()=0;

    //IO
    virtual void print(OutS, Property*)=0;
    virtual void print(OutS)=0;
    virtual InS getSym()=0;

    //Screen state
    virtual void clearScreen()=0;

    virtual void newLine()=0;

    virtual void moveCursor(int x, int y)=0;
    virtual void moveCursorTo(int x, int y)=0;

    virtual void hideCursor()=0;
    virtual void showCursor()=0;

    virtual void saveCursorPos()=0;
    virtual void restoreCursorPos()=0;

    //Terminal info
    virtual int boldSupported()=0;
    virtual int italicsSupported()=0;

    virtual PropertyType getPropertyType()=0;

    //Terminal state
    virtual void setDeviceReady()=0;
    virtual void resetDeviceMode()=0;
    virtual bool isDeviceReady()=0;

    //Global state
    virtual bool isReady()=0;
  };
}
