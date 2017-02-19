#pragma once

#include <utility>

#include "AdditionalStructs.hpp"
#include "ReadStream.hpp"
#include "WriteStream.hpp"
#include "Symbol.hpp"

namespace Blessings_ns {

  class MonitorGeneral {
	public:
    virtual void printPage()=0;

    //Cursor props
    virtual void moveCursor(GridPos pos)=0;
    virtual GridPos getCursorPos()=0;

    virtual void hideCursor()=0;
    virtual void showCursor()=0;

    virtual void saveCursorPos()=0;
    virtual void restoreCursorPos()=0;

    //Screen props
    virtual void clearScreen();

    virtual MonitorResolution getResolution()=0;

    //Availability
    virtual int boldSupported()=0;
    virtual int italicsSupported()=0;

    virtual PropertyType getPropertyType()=0;
  };


  template <class InputSymbol, class OutputSymbol>
  class Monitor : public MonitorGeneral {
  public:
    Monitor(ReadStream<InputSymbol>* RS, WriteStream<OutputSymbol>* WS, MonitorResolution res);
      //If res.x_size==0 and res.y_size==0 - Resolution=WS->getResolution()
      //If res.x_size==0 but res.y_size!=0 or res.x_size!=0 but res.y_size==0 - throw exception

    Monitor(const Monitor&); //If needed or remove
    Monitor& operator=(const Monitor&); //If needed or remove

    ~Monitor(); //If needed or remove

    class Error;

    std::pair<OutputSymbol, PropertyGeneral*>& operator()(int x, int y);
    std::pair<OutputSymbol, PropertyGeneral*> operator()(int x, int y) const;

    void printPage();

    InputSymbol getSym();

    void printSpecialSymbol(OutputSymbol);

    void moveCursor(int x, int y);
    GridPos getCursorPos();

    void hideCursor();
    void showCursor();

    void saveCursorPos();
    void restoreCursorPos();

    void clearScreen();

    MonitorResolution getResolution();

    //Availability
    int boldSupported();
    int italicsSupported();

    PropertyType getPropertyType();
  };

  struct MonitorCell {};

}
