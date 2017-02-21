#pragma once

#include <utility>

#include "AdditionalStructs.hpp"
#include "TerminalIO.hpp"
#include "Symbol/Symbol.hpp"

namespace blessings {
  template <class Symbol>
  struct MonitorCell {
    Symbol symb;
    Property* prop;
  };


  class MonitorGeneral {
  public:
    virtual void update()=0;
    virtual void clearScreen()=0;
    virtual void printPage()=0;

    virtual void moveCursor(int x, int y)=0;
    virtual GridPos getCursorPos()=0;

    virtual void hideCursor()=0;
    virtual void showCursor()=0;

    virtual void saveCursorPos()=0;
    virtual void restoreCursorPos()=0;

    virtual MonitorResolution getResolution()=0;

    virtual int boldSupported()=0;
    virtual int italicsSupported()=0;

    virtual PropertyType getPropertyType()=0;
  };


  template <class InS, class OutS>    // <InputSymbol, OutputSymbol>
  class Monitor : public MonitorGeneral {
  public:
    Monitor(TerminalIO <InS, OutS> Term, int MaxSize);
    Monitor(const Monitor&);
    Monitor& operator=(const Monitor&);
    ~Monitor();

    class Error;

    GridPos positionOf(int) const;
    int indexOf(GridPos) const;

    MonitorCell <OutS> & operator[] (int p);
    MonitorCell <OutS> operator[] (int p) const;
    MonitorCell <OutS> & operator()(int x, int y);
    MonitorCell <OutS> operator()(int x, int y) const;

    class Iterator {
    protected:
      int pointer;
      int stopPos;
    public:
      Iterator(int pnt, int bnd);
      MonitorCell<OutS>& operator*();
      Iterator& operator++();
      Iterator operator++(int);

      class Error;
      class EndError;

      int currentIndex();
      GridPos currentPos();
    };

    Iterator begin();
    Iterator end();

    void update();
    void clearScreen();
    void printPage();

    InS getSym();

    void printSymbol(OutS);

    void moveCursor(int x, int y);
    GridPos getCursorPos();

    void hideCursor();
    void showCursor();

    void saveCursorPos();
    void restoreCursorPos();

    MonitorResolution getResolution();

    int boldSupported();    // Must be rewrited
    int italicsSupported();

    PropertyType getPropertyType();

  protected:
    void setResolution(MonitorResolution mr);

    MonitorCell <OutS> * grid;
    TerminalIO <InS, OutS> termIO;

    int maxSize;
    MonitorResolution res;

    GridPos cursorPos;
    GridPos cursorSlot;
  };
}
