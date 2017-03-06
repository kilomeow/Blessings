#pragma once

#include <queue>

#include "additional_structs.hpp"
#include "terminal_io.hpp"
#include "property.hpp"

namespace blessings {
  template <class InS, class OutS>    // <InputSymbol, OutputSymbol>
  class Monitor {
  public:
    Monitor() {}
    Monitor(int MaxSize);
    ~Monitor();
    Monitor(const Monitor&);
    Monitor& operator=(const Monitor&);

    termplate <class Symbol>
    class Cell {
    protected:
      Symbol symb;
      Property prop;
      bool unstaged = false;

    public:
      Cell() {}
      Cell(Symbol s, const Property* p) : symb(s), prop(p) {}
      ~Cell() {}
      Cell(const Cell&);
      Cell& operator=(const Cell&);

      static bool hardopt;

      void setStaged();
      void setUnstaged();
    };

    class Iterator {
    protected:
      Monitor::Cell <OutS> * grid;
      int pointer;
      int stopPos;

    public:
      Iterator() {};
      Iterator(Cell<OutS>* Grid, int ptr, int bound);
      Iterator(const Iterator&);
      Iterator& operator=(const Iterator&);
      ~Iterator();

      Cell<OutS>& operator*();

      Iterator& operator++();
      Iterator operator++(int);
      Iterator& operator--();
      Iterator operator--(int);

      bool operator==(const Iterator&);
      bool operator!=(const Iterator&);
      bool operator>=(const Iterator&);
      bool operator<=(const Iterator&);
      bool operator>(const Iterator&);
      bool operator<(const Iterator&);

      Iterator operator+(int);
      Iterator operator-(int);
      void operator+=(int);
      void operator-=(int);

      int index();
      bool isBegin();
      bool isEnd();

      void rewind();

      class Error {};
      class EndError : public Error {};

    private:
      bool comparable(const Iterator&);
    };

    void connect(TerminalIO <InS, OutS>*);
    void disconnect();

    void startWork();
    void endWork();

    GridPos positionOf(int) const;
    int indexOf(GridPos) const;
    int currentBound() const;

    Cell <OutS> & operator[] (int p);
    Cell <OutS> operator[] (int p) const;
    Cell <OutS> & operator()(int x, int y);
    Cell <OutS> operator()(int x, int y) const;

    Cell <OutS> & at(int p);
    Cell <OutS> at (int p) const;
    Cell <OutS> & at(int x, int y);
    Cell <OutS> at (int x, int y) const;

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
    void hardOptimization(bool);

    int boldSupported();    // Must be rewritten
    int italicsSupported();

    PropertyType getPropertyType();

    class Error {};
    class DrawError : public Error {};
    class ResolutionDisparity : public DrawError {};
    class TerminalModeError : public DrawError {};

  protected:
    Cell <OutS> * grid;
    TerminalIO <InS, OutS> * termIO;

    int maxSize;
    MonitorResolution res;

    bool isDrawn=false;

  private:
    void checkMode();
    void checkResolution(resChange);
  };

}
