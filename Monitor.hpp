#pragma once

#include <utility>

#include "AdditionalStructs.hpp"
#include "ReadStream.hpp"
#include "WriteStream.hpp"

namespace Blessings_ns {
  template <class InputSymbol, class OutputSymbol, class Property>
  class Monitor {
    //Ram fills realization.
  public:
    Monitor(ReadStream<InputSymbol>* RS, WriteStream<OutputSymbol, Property>* WS, MonitorResolution res);
      //If res.x_size==0 and res.y_size==0 - Resolution=WS->getResolution()
      //If res.x_size==0 but res.y_size!=0 or res.x_size!=0 but res.y_size==0 - throw exception

    Monitor(const Monitor&); //If needed or remove
    Monitor& operator=(const Monitor&); //If needed or remove

    ~Monitor(); //If needed or remove

    class Error;

    std::pair<OutputSymbol, Property>& operator()(int x, int y);
    std::pair<OutputSymbol, Property> operator()(int x, int y) const;

    void printPage();
    InputSymbol getSym();

    void printSpecialSymbol(OutputSymbol);

    void moveCursor(int x, int y);
    CursorPos getCursorPos();

    void hideCursor();
    void showCursor();

    void saveCursorPos();
    void restoreCursorPos();

    void clearScreen();

    MonitorResolution getResolution();
  };

}
