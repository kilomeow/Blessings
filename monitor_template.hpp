#pragma once

#include <queue>

#include "additional_structs.hpp"
#include "terminal_io.hpp"

namespace blessings {
  template <typename InS, typename OutS, typename Prop>
  class MonitorTemplate {
  public:
    MonitorTemplate() {}
    MonitorTemplate(int MaxSize);
    ~MonitorTemplate();
    MonitorTemplate(const MonitorTemplate&);
    MonitorTemplate& operator=(const MonitorTemplate&);
    
    // Monitor::Cell
    
    class Cell {
    private:
      OutS symb;
      Prop prop;
      
      OutS newsymb;
      Prop newprop;
      
      bool unstaged = false;

    public:
      Cell() : symb(OutS::space), prop(Prop::empty) {}
      Cell(OutS s) : symb(s), prop(Prop::empty) {}
      Cell(Prop p) : symb(OutS::space), prop(p) {}
      Cell(OutS s, Prop p) : symb(s), prop(p) {}
      ~Cell() {}
      Cell(const Cell&);
      Cell& operator=(const Cell&);

      OutS symbol() const {return newsymb;}
      Prop property() const {return newprop;}

      static bool hardopt;

      bool isUnstaged();

      void setStaged();
    };
    
    // Monitor::Iterator

    class Iterator {
    private:
      MonitorTemplate::Cell* grid;
      int pointer;
      int stopPos;

      bool comparable(const Iterator&);

    public:
      Iterator() {}
      Iterator(Cell* Grid, int ptr, int bound);
      Iterator(const Iterator&);
      Iterator& operator=(const Iterator&);
      ~Iterator() {}

      Cell& operator*();
      Cell* operator->();

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
    };
    
    // Standard API

    void connect(TerminalIO<InS, OutS, Prop>*);
    void disconnect();

    void startWork();
    void endWork();

    GridPos positionOf(int) const;
    int indexOf(GridPos) const;
    int bound() const;

    Cell & operator[] (int p);
    Cell operator[] (int p) const;
    Cell & operator()(int x, int y);
    Cell operator()(int x, int y) const;
    Cell & operator()(GridPos);
    Cell operator()(GridPos) const;

    Cell & at(int p);
    Cell at (int p) const;
    Cell & at(int x, int y);
    Cell at (int x, int y) const;
    Cell & at(GridPos);
    Cell at(GridPos) const;

    Iterator begin();
    Iterator end();

    void tile(OutS, Prop);
    void tile(OutS);
    void tile();
    void tile(OutS, Prop, int x1, int y1, int x2, int y2);
    void tile(OutS, int x1, int y1, int x2, int y2);
    void tile(int x1, int y1, int x2, int y2);
    void tile(OutS, Prop, GridPos p1, GridPos p2);
    void tile(OutS, GridPos p1, GridPos p2);
    void tile(GridPos p1, GridPos p2);
    void tile(OutS, Prop, GridPos p1, Resolution r);
    void tile(OutS, GridPos p1, Resolution r);
    void tile(GridPos p1, Resolution r);

    Resolution resolution();
    Resolution terminalResolution();
    void setResolution(Resolution);
    void setResolution(int w, int h);
    void updateResolution();

    void moveCursor(int x, int y);
    void moveCursor(int p);
    void moveCursorTo(int x, int y);
    void moveCursorTo(int p);
    void moveCursorTo(GridPos);
    
    void updateCursor();
    void resetCursor();
    void hideCursor();
    void showCursor();

    GridPos cursorPosition();
    bool isCursorVisible();

    void clearInputBuffer();
    InS getSymbol();
    std::queue<InS> getSymbol(int n);

    void printSymbol(OutS, Prop);
    void printSymbol(OutS);
    
    enum class ResolutionChange {
      Alarm,
      Ignore,
      IgnoreExtension
    };
    
    enum class DrawBehaviour {
      Primitive,
      Lazy
    };
    
    enum class TileBehaviour {
      Primitive
      //Lazy
    };
    
    enum class CursorBehaviour {
      Primitive,
      Lazy
    };
    
    void setResolutionMode(ResolutionChange resm) {resmode = resm;}
    void setDrawMode(DrawBehaviour drawm) {drawmode = drawm;}
    void setTileMode(TileBehaviour tilem) {tilemode = tilem;}
    void setMoveMode(CursorBehaviour curm) {cursormode = curm;}

    void clearScreen();
    void printPage();
    void draw();
    
    // Curses-like API
    
    void initscr() {startWork();}
    void endwin() {endWork();}
    
    void echo() {termIO->setEchoForward();}
    void noecho() {termIO->setEchoInhibition();}
    
    void clrscr() {clearScreen();}
    
    void doupdate() {draw();}
    void refresh() {clearScreen(); draw();}
    
    InS getch() {return getSymbol();}
    std::queue<InS> getstr(int n) {return getSymbol(n);}
    
    void move(int x, int y) {moveCursorTo(x, y);}
    void move(GridPos p) {moveCursorTo(p);}
    
    void printc(OutS symb, Prop prop) {printSymbol(symb, prop);}
    void printc(OutS symb) {printSymbol(symb);}
    
    // Exceptions
    
    class Error {};
    class DrawError : public Error {};
    class ResolutionDisparity : public DrawError {};
    class TerminalModeError : public DrawError {};

  private:
    Cell* grid;
    TerminalIO<InS, OutS, Prop>* termIO;

    int maxSize;
    Resolution res;

    GridPos cursorPos;

    bool isPrinted=false;
    ResolutionChange resmode = ResolutionChange::Ignore;
    DrawBehaviour drawmode = DrawBehaviour::Lazy;
    TileBehaviour tilemode = TileBehaviour::Primitive;
    CursorBehaviour cursormode = CursorBehaviour::Lazy;
    
    bool cursorVisible=false;
    bool cursorVisibleSlot;
    
    void overDraw();
    void lazyDraw();

    void saveCursor();
    void restoreCursor();
    
    void forceMove(int p);

    void checkMode();
    void checkResolution();
    //void checkPos(GridPos);
    //void checkPos(int x, int y);
    //void checkPos(int p);
  };

}
