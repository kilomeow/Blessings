#pragma once

#include <queue>

#include "additional_structs.hpp"
#include "terminal_io.hpp"
#include "symbol/symbol.hpp"

namespace blessings {
  template <class Symbol>
  struct MonitorCell {
    Symbol symb;
    const Property* prop;
    bool unstaged = false;

    MonitorCell() {}
    MonitorCell(Symbol s, const Property* p) : symb(s), prop(p) {}
    MonitorCell& operator=(const MonitorCell& cell) {
      symb = cell.symb;
      prop = cell.prop;
      unstaged = true;
    }
  };


  template <class InS, class OutS>    // <InputSymbol, OutputSymbol>
  class Monitor {
  protected:
    MonitorCell <OutS> * grid;
    TerminalIO <InS, OutS> * termIO;

    int maxSize;
    MonitorResolution res;

  public:
    Monitor() {}
    Monitor(TerminalIO <InS, OutS>* Term, int MaxSize);
    Monitor(const Monitor&);
    Monitor& operator=(const Monitor&);
    ~Monitor();

    GridPos positionOf(int) const;
    int indexOf(GridPos) const;
    int currentBound() const;

    MonitorCell <OutS> & operator[] (int p);
    MonitorCell <OutS> operator[] (int p) const;
    MonitorCell <OutS> & operator()(int x, int y);
    MonitorCell <OutS> operator()(int x, int y) const;

    MonitorCell <OutS> & at(int p);
    MonitorCell <OutS> at (int p) const;
    MonitorCell <OutS> & at(int x, int y);
    MonitorCell <OutS> at (int x, int y) const;

    class Iterator {
    protected:
      MonitorCell <OutS> * grid;
      int pointer;
      int stopPos;

    public:
      Iterator() {};
      Iterator(MonitorCell<OutS>* grd, int pnt, int bnd);
      MonitorCell<OutS>& operator*();
      Iterator& operator++();
      Iterator operator++(int);

      int index();
      bool isEnd();

      class Error {};
      class EndError : public Error {};
    };

    Iterator begin();
    Iterator end();

    void tile(OutS, const Property*);

    MonitorResolution getCurrentResolution();
    MonitorResolution getTerminalResolution();
    void setResolution(MonitorResolution);
    void setResolution(int w, int h);
    void updateResolution();

    void moveCursor(int x, int y);
    void moveCursorTo(int x, int y);
    void moveCursorTo(GridPos);

    void hideCursor();
    void showCursor();
    void saveCursorPos();
    void restoreCursorPos();

    std::queue<InS> getSymbol(int n=1);
    void printSymbol(OutS, const Property*);
    void printSymbol(OutS);

    enum resChange {
      alarm,
      ignore,
      ignoreExtension
    };

    void clearScreen();
    void printPage();
    void draw(resChange drawMode=alarm);
    void lazyDraw(resChange drawMode=alarm);

    int boldSupported();    // Must be rewritten
    int italicsSupported();

    PropertyType getPropertyType();

    class Error {};
    class DrawError : public Error {};
    class ResolutionDisparity : public DrawError {};
    class TerminalModeError : public DrawError {};

  private:
    void checkMode();
    void checkResolution(resChange);
  };
}
