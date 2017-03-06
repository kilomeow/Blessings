#pragma once

#include <queue>

#include "additional_structs.hpp"
#include "terminal_io.hpp"

namespace blessings {
  template <class InS, class OutS, class Prop>
  class Monitor {
  public:
    Monitor() {}
    Monitor(int MaxSize);
    ~Monitor();
    Monitor(const Monitor&);
    Monitor& operator=(const Monitor&);

    template <class Symbol, class Property>
    class Cell {
    protected:
      Symbol symb;
      Property prop;
      bool unstaged = false;

    public:
      Cell() {}
      Cell(Symbol s, Property p) : symb(s), prop(p) {}
      Cell(Symbol s) : symb(s), prop(Property::defaultProperty) {}
      ~Cell() {}
      Cell(const Cell&);
      Cell& operator=(const Cell&);
      Cell& operator=(Symbol s);

      static bool hardopt;

      void setStaged();
      void setUnstaged();
    };

    class Iterator {
    protected:
      Monitor::Cell<OutS, Prop>* grid;
      int pointer;
      int stopPos;

    public:
      Iterator() {};
      Iterator(Cell<OutS, Prop>* Grid, int ptr, int bound);
      Iterator(const Iterator&);
      Iterator& operator=(const Iterator&);
      ~Iterator();

      Cell<OutS, Prop>& operator*();

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

    void connect(TerminalIO<InS, OutS, std::queue<InS>, std::queue<OutS>, Prop>*);
    void disconnect();

    void startWork();
    void endWork();

    GridPos positionOf(int) const;
    int indexOf(GridPos) const;
    int currentBound() const;

    Cell<OutS, Prop> & operator[] (int p);
    Cell<OutS, Prop> operator[] (int p) const;
    Cell<OutS, Prop> & operator()(int x, int y);
    Cell<OutS, Prop> operator()(int x, int y) const;

    Cell<OutS, Prop> & at(int p);
    Cell<OutS, Prop> at (int p) const;
    Cell<OutS, Prop> & at(int x, int y);
    Cell<OutS, Prop> at (int x, int y) const;

    Iterator begin();
    Iterator end();

    void tile(OutS, Prop);
    void tile(OutS);

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
    void printSymbol(OutS, Prop);
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
    
    // PropertyType getPropertyType();

    int boldSupported();    // Must be rewritten
    int italicsSupported();

    class Error {};
    class DrawError : public Error {};
    class ResolutionDisparity : public DrawError {};
    class TerminalModeError : public DrawError {};

  protected:
    Cell<OutS, Prop>* grid;
    TerminalIO<InS, OutS, std::queue<InS>, std::queue<OutS>, Prop>* termIO;
    
    int maxSize;
    MonitorResolution res;

    bool isDrawn=false;

  private:
    void checkMode();
    void checkResolution(resChange);
  };

}
