#pragma once

#include <queue>

#include "additional_structs.hpp"

namespace blessings {
  template <typename InS, typename OutS, typename Property>
  class TerminalIO {
  public:
    //Device info
    virtual Resolution getResolution()=0;

    //IO
    virtual void print(OutS, const Property&)=0;
    virtual void print(OutS)=0;

    virtual InS getSymbol() = 0;
    virtual std::queue<InS> getSymbol(int n)=0;
    virtual void clearInputBuffer()=0;
    virtual bool checkInput()=0;

    //Screen state
    virtual void clearScreen()=0;

    virtual void newLine()=0;

    virtual void moveCursor(int x, int y)=0;
    virtual void moveCursorTo(int x, int y)=0;

    virtual void hideCursor()=0;
    virtual void showCursor()=0;

    virtual void saveCursorPos()=0;
    virtual void restoreCursorPos()=0;

    //Terminal state
    virtual void setNonCanonicalMode()=0;
    virtual void setCanonicalMode()=0;
    virtual void setEchoInhibition()=0;
    virtual void setEchoForward()=0;

    virtual void resetDeviceMode()=0;

    virtual int isNonCanonical()=0;
    virtual int isEchoInhibited()=0;

    virtual bool isInited()=0;
  };
}
