#pragma once

#include <queue>
#include <algorithm>

#include "monitor.hpp"
#include "additional_structs.hpp"
#include "terminal_io.hpp"

namespace blessings {
  template <typename InS, typename OutS, typename Prop>
  MonitorTemplate<InS,OutS,Prop>::MonitorTemplate() {
    maxSize = CELL_MEMORY_START;
    grid = new Cell [maxSize];
    res.width=1; res.height=1;
  }

  template <typename InS, typename OutS, typename Prop>
  MonitorTemplate<InS,OutS,Prop>::~MonitorTemplate() {
    delete [] grid;
  }

  template <typename InS, typename OutS, typename Prop>
  MonitorTemplate<InS,OutS,Prop>::MonitorTemplate(\
  const MonitorTemplate& monitor) {
    termIO = monitor.termIO;
    maxSize = monitor.maxSize;
    res = monitor.res;
    grid = new MonitorTemplate<InS,OutS,Prop>::Cell [maxSize];
    for (int i=0;i<maxSize;i++)
      grid[i] = monitor.grid[i];
  }

  template <typename InS, typename OutS, typename Prop>
  MonitorTemplate<InS,OutS,Prop>& \
  MonitorTemplate<InS,OutS,Prop>::operator=(\
  const MonitorTemplate& monitor) {
    termIO = monitor.termIO;
    maxSize = monitor.maxSize;
    res = monitor.res;
    isPrinted = false;
    delete [] grid;
    grid = new MonitorTemplate<InS,OutS,Prop>::Cell [maxSize];
    for (int i=0;i<maxSize;i++)
      grid[i] = monitor.grid[i];
    return (*this);
  }

  template <typename InS, typename OutS, typename Prop>
  void MonitorTemplate<InS,OutS,Prop>::connect(\
  TerminalIO<InS,OutS,Prop>* Term) {
    termIO = Term;
  }

  template <typename InS, typename OutS, typename Prop>
  void MonitorTemplate<InS,OutS,Prop>::disconnect() {
    termIO = nullptr;
  }

  template <typename InS, typename OutS, typename Prop>
  void MonitorTemplate<InS,OutS,Prop>::startWork() {
    termIO->setNonCanonicalMode();
    termIO->setEchoInhibition();
    clearScreen();
    resetCursor();
  }

  template <typename InS, typename OutS, typename Prop>
  void MonitorTemplate<InS,OutS,Prop>::endWork() {
    termIO->setCanonicalMode();
    termIO->setEchoForward();
    clearScreen();
    resetCursor();
    showCursor();
  }
  
  template <typename InS, typename OutS, typename Prop>
  void MonitorTemplate<InS,OutS,Prop>::expand(int n) {
    Cell* newgrid;
    int steps = (n-maxSize)/CELL_MEMORY_STEP;
    size_t newSize = maxSize + (steps+1)*CELL_MEMORY_STEP;
    newgrid = new Cell [newSize];
    for (int i=0; i++; i<maxSize) newgrid[i] = grid[i];
    delete [] grid;
    grid = newgrid;
  }

  template <typename InS, typename OutS, typename Prop>
  GridPos MonitorTemplate<InS,OutS,Prop>::positionOf(int index) const {
    GridPos gp;
    gp.x = index%res.width;
    gp.y = index/res.width;
    return gp;
  }

  template <typename InS, typename OutS, typename Prop>
  int MonitorTemplate<InS,OutS,Prop>::indexOf(GridPos gp) const {
    return gp.x+gp.y*res.width;
  }

  template <typename InS, typename OutS, typename Prop>
  int MonitorTemplate<InS,OutS,Prop>::bound() const {
    return res.width*res.height;
  }

  template <typename InS, typename OutS, typename Prop>
  typename MonitorTemplate<InS,OutS,Prop>::Cell& \
  MonitorTemplate<InS,OutS,Prop>::operator[] (int p) {
    if ((p<0) || (p>=bound())) throw MonitorTemplate::Error();
    //MonitorTemplate::Error("p out of range");
    return grid[p];
  }

  template <typename InS, typename OutS, typename Prop>
  typename MonitorTemplate<InS,OutS,Prop>::Cell \
  MonitorTemplate<InS,OutS,Prop>::operator[] (int p) const {
    if ((p<0) || (p>=bound())) throw MonitorTemplate::Error();
    //MonitorTemplate::Error("p out of range");
    return grid[p];
  }

  template <typename InS, typename OutS, typename Prop>
  typename MonitorTemplate<InS,OutS,Prop>::Cell& \
  MonitorTemplate<InS,OutS,Prop>::operator() (int x, int y) {
    if ((x<0) || (x>res.width) || (y<0) || (y>res.height)) throw Error();
    //MonitorTemplate::Error("(x,y) out of range");
    return grid[x+y*res.width];
  }

  template <typename InS, typename OutS, typename Prop>
  typename MonitorTemplate<InS,OutS,Prop>::Cell \
  MonitorTemplate<InS,OutS,Prop>::operator() (int x, int y) const {
    if ((x<0) || (x>res.width) || (y<0) || (y>res.height)) throw Error();
    //MonitorTemplate::Error("(x,y) out of range");
    return grid[x+y*res.width];
  }

  template <typename InS, typename OutS, typename Prop>
  typename MonitorTemplate<InS,OutS,Prop>::Cell& \
  MonitorTemplate<InS,OutS,Prop>::operator() (GridPos p) {
    return this->at(p.x, p.y);
  }

  template <typename InS, typename OutS, typename Prop>
  typename MonitorTemplate<InS,OutS,Prop>::Cell \
  MonitorTemplate<InS,OutS,Prop>::operator() (GridPos p) const {
    return this->at(p.x, p.y);
  }

  template <typename InS, typename OutS, typename Prop>
  typename MonitorTemplate<InS,OutS,Prop>::Cell& \
  MonitorTemplate<InS,OutS,Prop>::at (int p) {
    return (*this)[p];
  }

  template <typename InS, typename OutS, typename Prop>
  typename MonitorTemplate<InS,OutS,Prop>::Cell \
  MonitorTemplate<InS,OutS,Prop>::at (int p) const {
    return (*this)[p];
  }

  template <typename InS, typename OutS, typename Prop>
  typename MonitorTemplate<InS,OutS,Prop>::Cell& \
  MonitorTemplate<InS,OutS,Prop>::at (int x, int y) {
    return (*this)(x, y);
  }

  template <typename InS, typename OutS, typename Prop>
  typename MonitorTemplate<InS,OutS,Prop>::Cell \
  MonitorTemplate<InS,OutS,Prop>::at (int x, int y) const {
    return (*this)(x, y);
  }

  template <typename InS, typename OutS, typename Prop>
  typename MonitorTemplate<InS,OutS,Prop>::Cell& \
  MonitorTemplate<InS,OutS,Prop>::at (GridPos p) {
    return this->at(p.x, p.y);
  }

  template <typename InS, typename OutS, typename Prop>
  typename MonitorTemplate<InS,OutS,Prop>::Cell \
  MonitorTemplate<InS,OutS,Prop>::at (GridPos p) const {
    return this->at(p.x, p.y);
  }

  template <typename InS, typename OutS, typename Prop>
  MonitorTemplate<InS,OutS,Prop>::Cell::Cell( \
  const MonitorTemplate<InS,OutS,Prop>::Cell& cell) {
    symb = cell.symb;
    prop = cell.prop;
    newsymb = symb;
    newprop = prop;
  }

  template <typename InS, typename OutS, typename Prop>
  typename MonitorTemplate<InS,OutS,Prop>::Cell& \
  MonitorTemplate<InS,OutS,Prop>::Cell::operator=( \
  const MonitorTemplate<InS,OutS,Prop>::Cell& cell) {
    newsymb = cell.symb;
    newprop = cell.prop;
    return (*this);
  }

  template <typename InS, typename OutS, typename Prop>
  bool MonitorTemplate<InS,OutS,Prop>::Cell::isUnstaged() {
    return !((symb==newsymb) && (prop==newprop));
  }
  
  template <typename InS, typename OutS, typename Prop>
  void MonitorTemplate<InS,OutS,Prop>::Cell::setStaged() {
    symb = newsymb;
    prop = newprop;
  }

  template <typename InS, typename OutS, typename Prop>
  MonitorTemplate<InS,OutS,Prop>::Iterator::Iterator( \
  MonitorTemplate<InS,OutS,Prop>::Cell* Grid, int ptr, int bound) {
    if ((ptr<0) || (ptr>bound)) throw MonitorTemplate::Iterator::Error();
    //MonitorTemplate::Iterator::Error("pointer out of range");
    grid = Grid;
    pointer = ptr;
    stopPos = bound;
  }

  template <typename InS, typename OutS, typename Prop>
  MonitorTemplate<InS,OutS,Prop>::Iterator::Iterator( \
  const Iterator& it) {
    grid = it.grid;
    pointer = it.pointer;
    stopPos = it.stopPos;
  }

  template <typename InS, typename OutS, typename Prop>
  typename MonitorTemplate<InS,OutS,Prop>::Iterator& \
  MonitorTemplate<InS,OutS,Prop>::Iterator::operator=( \
  const Iterator& it) {
    grid = it.grid;
    pointer = it.pointer;
    stopPos = it.stopPos;
    return (*this);
  }

  template <typename InS, typename OutS, typename Prop>
  typename MonitorTemplate<InS,OutS,Prop>::Cell& \
  MonitorTemplate<InS,OutS,Prop>::Iterator::operator*() {
    if (pointer==stopPos) throw MonitorTemplate::Iterator::EndError();
    //MonitorTemplate::Iterator::EndError("pointer is at end");
    return grid[pointer];
  }

  template <typename InS, typename OutS, typename Prop>
  typename MonitorTemplate<InS,OutS,Prop>::Cell* \
  MonitorTemplate<InS,OutS,Prop>::Iterator::operator->() {
    if (pointer==stopPos) throw MonitorTemplate::Iterator::EndError();
    //MonitorTemplate::Iterator::EndError("pointer is at end");
    return &grid[pointer];
  }

  template <typename InS, typename OutS, typename Prop>
  typename MonitorTemplate<InS,OutS,Prop>::Iterator& \
  MonitorTemplate<InS,OutS,Prop>::Iterator::operator++() {
    if (pointer==stopPos) throw MonitorTemplate::Iterator::EndError();
    //MonitorTemplate::Iterator::EndError("pointer is at end");
    pointer++;
    return (*this);
  }

  template <typename InS, typename OutS, typename Prop>
  typename MonitorTemplate<InS,OutS,Prop>::Iterator \
  MonitorTemplate<InS,OutS,Prop>::Iterator::operator++(int a) {
    if (pointer==stopPos) throw MonitorTemplate::Iterator::EndError();
    //MonitorTemplate::Iterator::EndError("pointer is at end");
    MonitorTemplate::Iterator i = (*this);
    ++(*this);
    return i;
  }

  template <typename InS, typename OutS, typename Prop>
  typename MonitorTemplate<InS,OutS,Prop>::Iterator& \
  MonitorTemplate<InS,OutS,Prop>::Iterator::operator--() {
    if (pointer==0) throw MonitorTemplate::Iterator::EndError();
    //MonitorTemplate::Iterator::EndError("pointer is at end");
    pointer--;
    return (*this);
  }

  template <typename InS, typename OutS, typename Prop>
  typename MonitorTemplate<InS,OutS,Prop>::Iterator \
  MonitorTemplate<InS,OutS,Prop>::Iterator::operator--(int a) {
    if (pointer==0) throw MonitorTemplate::Iterator::EndError();
    //MonitorTemplate::Iterator::EndError("pointer is at end");
    MonitorTemplate::Iterator i = (*this);
    --(*this);
    return i;
  }

  template <typename InS, typename OutS, typename Prop>
  typename MonitorTemplate<InS,OutS,Prop>::Iterator \
  MonitorTemplate<InS,OutS,Prop>::Iterator::operator+(int k) {
    int newptr = pointer+k;
    if ((newptr < 0) || (newptr > stopPos)) throw MonitorTemplate::Iterator::Error();
    Iterator it(grid, newptr, stopPos);
    return it;
  }

  template <typename InS, typename OutS, typename Prop>
  typename MonitorTemplate<InS,OutS,Prop>::Iterator \
  MonitorTemplate<InS,OutS,Prop>::Iterator::operator-(int k) {
    return this->operator+(-k);
  }

  template <typename InS, typename OutS, typename Prop>
  void MonitorTemplate<InS,OutS,Prop>::Iterator::operator+=(int k) {
    this->operator=(this->operator+(k));
  }

  template <typename InS, typename OutS, typename Prop>
  void MonitorTemplate<InS,OutS,Prop>::Iterator::operator-=(int k) {
    this->operator=(this->operator-(k));
  }

  template <typename InS, typename OutS, typename Prop>
  int MonitorTemplate<InS,OutS,Prop>::Iterator::index() {
    return pointer;
  }

  template <typename InS, typename OutS, typename Prop>
  bool MonitorTemplate<InS,OutS,Prop>::Iterator::isBegin() {
    return (pointer==0);
  }

  template <typename InS, typename OutS, typename Prop>
  bool MonitorTemplate<InS,OutS,Prop>::Iterator::isEnd() {
    return (pointer==stopPos);
  }

  template <typename InS, typename OutS, typename Prop>
  void MonitorTemplate<InS,OutS,Prop>::Iterator::rewind() {
    pointer=0;
  }

  template <typename InS, typename OutS, typename Prop>
  bool MonitorTemplate<InS,OutS,Prop>::Iterator::operator==( \
  const Iterator& it) {
    if (!comparable(it)) throw MonitorTemplate::Iterator::Error();
    return (pointer == it.pointer);
  }

  template <typename InS, typename OutS, typename Prop>
  bool MonitorTemplate<InS,OutS,Prop>::Iterator::operator!=( \
  const Iterator& it) {
    return !((*this) == it);
  }

  template <typename InS, typename OutS, typename Prop>
  bool MonitorTemplate<InS,OutS,Prop>::Iterator::operator>=( \
  const Iterator& it) {
    if (!comparable(it)) throw MonitorTemplate::Iterator::Error();
    return (pointer >= it.pointer);
  }

  template <typename InS, typename OutS, typename Prop>
  bool MonitorTemplate<InS,OutS,Prop>::Iterator::operator<=( \
  const Iterator& it) {
    if (!comparable(it)) throw MonitorTemplate::Iterator::Error();
    return (pointer <= it.pointer);
  }

  template <typename InS, typename OutS, typename Prop>
  bool MonitorTemplate<InS,OutS,Prop>::Iterator::operator>( \
  const Iterator& it) {
    return (((*this)!=it) && ((*this)>=it));
  }

  template <typename InS, typename OutS, typename Prop>
  bool MonitorTemplate<InS,OutS,Prop>::Iterator::operator<( \
  const Iterator& it) {
    return (((*this)!=it) && ((*this)<=it));
  }

  template <typename InS, typename OutS, typename Prop>
  bool MonitorTemplate<InS,OutS,Prop>::Iterator::comparable( \
  const Iterator& it) {
    return ((grid==it.grid) && (stopPos==it.stopPos));
  }

  template <typename InS, typename OutS, typename Prop>
  typename MonitorTemplate<InS,OutS,Prop>::Iterator \
  MonitorTemplate<InS,OutS,Prop>::begin() {
    MonitorTemplate::Iterator i(grid, 0, bound());
    return i;
  }

  template <typename InS, typename OutS, typename Prop>
  typename MonitorTemplate<InS,OutS,Prop>::Iterator \
  MonitorTemplate<InS,OutS,Prop>::end() {
    MonitorTemplate::Iterator i(grid, bound(), bound());
    return i;
  }


  template <typename InS, typename OutS, typename Prop>
  void MonitorTemplate<InS,OutS,Prop>::tile(OutS s, Prop p) {
    MonitorTemplate::Cell c(s, p);
    MonitorTemplate::Iterator i = begin();
    while (!i.isEnd()) {
      (*i) = c;
      i++;
    }
  }

  template <typename InS, typename OutS, typename Prop>
  void MonitorTemplate<InS,OutS,Prop>::tile(OutS s) {
    tile(s, Prop::empty);
  }

  template <typename InS, typename OutS, typename Prop>
  void MonitorTemplate<InS,OutS,Prop>::tile() {
    tile(OutS::space, Prop::empty);
  }

  template <typename InS, typename OutS, typename Prop>
  void MonitorTemplate<InS,OutS,Prop>::tile(OutS s, Prop p, \
  int x1, int y1, int x2, int y2) {
    int l = std::min(x1, x2); //left
    int r = std::max(x1, x2); //right
    int u = std::min(y1, y2); //up
    int d = std::max(y1, y2); //down

    if ((l<0) || (r>=res.width) || (u<0) || (d>=res.height))
      throw MonitorTemplate::ResolutionDisparity();

    MonitorTemplate::Cell c(s, p);

    for (int j=l;j<=r;j++)
    for (int i=u;i<=d;i++)
      this->at(j, i) = c;
  }

  template <typename InS, typename OutS, typename Prop>
  void MonitorTemplate<InS,OutS,Prop>::tile(OutS s, int x1, int y1, \
                                                    int x2, int y2) {
    tile(s, Prop::empty, x1, y1, x2, y2);
  }

  template <typename InS, typename OutS, typename Prop>
  void MonitorTemplate<InS,OutS,Prop>::tile(int x1, int y1, \
                                            int x2, int y2) {
    tile(OutS::space, Prop::empty, x1, y1, x2, y2);
  }

  template <typename InS, typename OutS, typename Prop>
  void MonitorTemplate<InS,OutS,Prop>::tile(OutS s, Prop p, GridPos p1, \
                                                            GridPos p2) {
    tile(s, p, p1.x, p1.y, p2.x, p2.y);
  }

  template <typename InS, typename OutS, typename Prop>
  void MonitorTemplate<InS,OutS,Prop>::tile(OutS s, GridPos p1, \
                                                    GridPos p2) {
    tile(s, Prop::empty, p1.x, p1.y, p2.x, p2.y);
  }

  template <typename InS, typename OutS, typename Prop>
  void MonitorTemplate<InS,OutS,Prop>::tile(GridPos p1, GridPos p2) {
    tile(OutS::space, Prop::empty, p1.x, p1.y, p2.x, p2.y);
  }

  template <typename InS, typename OutS, typename Prop>
  void MonitorTemplate<InS,OutS,Prop>::tile(OutS s, Prop p, GridPos p1, \
  Resolution r) {
    tile(s, p, p1.x, p1.y, p1.x+r.width, p1.y+r.height);
  }

  template <typename InS, typename OutS, typename Prop>
  void MonitorTemplate<InS,OutS,Prop>::tile(OutS s, GridPos p1, \
  Resolution r) {
    tile(s, Prop::empty, p1.x, p1.y, p1.x+r.width, p1.y+r.height);
  }

  template <typename InS, typename OutS, typename Prop>
  void MonitorTemplate<InS,OutS,Prop>::tile(GridPos p1, Resolution r) {
    tile(OutS::space, Prop::empty, p1.x, p1.y, p1.x+r.width, p1.y+r.height);
  }

  template <typename InS, typename OutS, typename Prop>
  Resolution MonitorTemplate<InS,OutS,Prop>::resolution() {
    return res;
  }

  template <typename InS, typename OutS, typename Prop>
  Resolution MonitorTemplate<InS,OutS,Prop>::terminalResolution() {
    return termIO->getResolution();
  }

  template <typename InS, typename OutS, typename Prop>
  void MonitorTemplate<InS,OutS,Prop>::setResolution(Resolution mr) {
    if ((mr.width<=0) || (mr.height<=0)) throw Error(); // "wrong resolution"
    if (mr.width*mr.height>maxSize) {
      expand(mr.width*mr.height);
    }
    res = mr;
    resetCursor();
    isPrinted = false;
  }

  template <typename InS, typename OutS, typename Prop>
  void MonitorTemplate<InS,OutS,Prop>::setResolution(int w, int h) {
    Resolution mr(w, h);
    setResolution(mr);
  }

  template <typename InS, typename OutS, typename Prop>
  void MonitorTemplate<InS,OutS,Prop>::moveCursor(int x, int y) {
    moveCursorTo(cursorPos.x + x, cursorPos.y + y);
  }

  template <typename InS, typename OutS, typename Prop>
  void MonitorTemplate<InS,OutS,Prop>::moveCursor(int p) {
    moveCursorTo(indexOf(cursorPos)+p);
  }

  template <typename InS, typename OutS, typename Prop>
  void MonitorTemplate<InS,OutS,Prop>::moveCursorTo(int x, int y) {
    if ((x<0) || (x>res.width) || (y<0) || (y>res.height)) throw Error();
    GridPos cursorPos(x, y);
    if (cursormode == CursorBehaviour::Primitive) updateCursor();
  }

  template <typename InS, typename OutS, typename Prop>
  void MonitorTemplate<InS,OutS,Prop>::moveCursorTo(int p) {
    moveCursorTo(positionOf(p));
  }

  template <typename InS, typename OutS, typename Prop>
  void MonitorTemplate<InS,OutS,Prop>::moveCursorTo(GridPos pos) {
    moveCursorTo(pos.x, pos.y);
  }
  
  template <typename InS, typename OutS, typename Prop>
  void MonitorTemplate<InS,OutS,Prop>::updateCursor() {
    termIO->moveCursorTo(cursorPos.x+1, cursorPos.y+1);
  }

  template <typename InS, typename OutS, typename Prop>
  void MonitorTemplate<InS,OutS,Prop>::resetCursor() {
    hideCursor();
    forceMove(0);
  }

  template <typename InS, typename OutS, typename Prop>
  void MonitorTemplate<InS,OutS,Prop>::hideCursor() {
    termIO->hideCursor();
    cursorVisible = false;
  }

  template <typename InS, typename OutS, typename Prop>
  void MonitorTemplate<InS,OutS,Prop>::showCursor() {
    termIO->showCursor();
    cursorVisible = true;
  }

  template <typename InS, typename OutS, typename Prop>
  GridPos MonitorTemplate<InS,OutS,Prop>::cursorPosition() {
    return cursorPos;
  }

  template <typename InS, typename OutS, typename Prop>
  bool MonitorTemplate<InS,OutS,Prop>::isCursorVisible() {
    return cursorVisible;
  }

  template <typename InS, typename OutS, typename Prop>
  void MonitorTemplate<InS,OutS,Prop>::clearInputBuffer() {
    termIO->clearInputBuffer();
  }

  template <typename InS, typename OutS, typename Prop>
  void MonitorTemplate<InS,OutS,Prop>::saveCursor() {
    termIO->saveCursorPos();
    cursorVisibleSlot = cursorVisible;
  }

  template <typename InS, typename OutS, typename Prop>
  void MonitorTemplate<InS,OutS,Prop>::restoreCursor() {
    termIO->restoreCursorPos();
    if (cursorVisibleSlot) {
      showCursor();
    } else {
      hideCursor();
    }
  }
  
  template <typename InS, typename OutS, typename Prop>
  void MonitorTemplate<InS,OutS,Prop>::forceMove(int p) {
    termIO->moveCursorTo(positionOf(p).x+1, positionOf(p).y+1);
  }
  
  template <typename InS, typename OutS, typename Prop>
  InS MonitorTemplate<InS,OutS,Prop>::getSymbol() {
    return termIO->getSymbol();
  }
  
  template <typename InS, typename OutS, typename Prop>
  std::queue<InS> MonitorTemplate<InS,OutS,Prop>::getSymbol(int n) {
    return termIO->getSymbol(n);
  }

  template <typename InS, typename OutS, typename Prop>
  void MonitorTemplate<InS,OutS,Prop>::printSymbol(OutS symb, Prop prop) {
    termIO->print(symb, prop);
  }

  template <typename InS, typename OutS, typename Prop>
  void MonitorTemplate<InS,OutS,Prop>::printSymbol(OutS symb) {
    termIO->print(symb);
  }

  template <typename InS, typename OutS, typename Prop>
  void MonitorTemplate<InS,OutS,Prop>::updateResolution() {
    setResolution(terminalResolution());
  }

  template <typename InS, typename OutS, typename Prop>
  void MonitorTemplate<InS,OutS,Prop>::checkResolution() {
    switch (resmode) {
    case ResolutionChange::Alarm:
      if ((terminalResolution().width != res.width) ||
          (terminalResolution().height != res.height))
        throw ResolutionDisparity();
      break;
    case ResolutionChange::IgnoreExtension:
      if ((terminalResolution().width < res.width) ||
          (terminalResolution().height < res.height))
        throw ResolutionDisparity();
      break;
    case ResolutionChange::Ignore:
      break;
    }
  }

  template <typename InS, typename OutS, typename Prop>
  void MonitorTemplate<InS,OutS,Prop>::checkMode() {
    if (termIO->isNonCanonical() != 1) throw TerminalModeError();
    if (termIO->isEchoInhibited() != 1) throw TerminalModeError();
  }

  template <typename InS, typename OutS, typename Prop>
  void MonitorTemplate<InS,OutS,Prop>::clearScreen() {
    termIO->clearScreen();
    isPrinted = false;
  }

  template <typename InS, typename OutS, typename Prop>
  void MonitorTemplate<InS,OutS,Prop>::printPage() {
    MonitorTemplate::Iterator i = begin();
    while (!i.isEnd()) {
      termIO->print(i->symbol(), i->property());
      i->setStaged();
      i++;
      if (i.index()%res.width==0) termIO->newLine();
    }
  }
  
  template <typename InS, typename OutS, typename Prop>
  void MonitorTemplate<InS,OutS,Prop>::overDraw() {
    MonitorTemplate::Iterator i = begin();
    while (!i.isEnd()) {
      termIO->print(i->symbol(), i->property());
      i->setStaged();
      i++;
      if (i.index()%res.width==0) forceMove(i.index());
    }
  }

  template <typename InS, typename OutS, typename Prop>
  void MonitorTemplate<InS,OutS,Prop>::lazyDraw() {
    MonitorTemplate::Iterator i = begin();
    while (!i.isEnd()) {
      if (i->isUnstaged()) {
        forceMove(i.index());
        termIO->print(i->symbol(), i->property());
        i->setStaged();
      }
      i++;
    }
  }
  
  template <typename InS, typename OutS, typename Prop>
  void MonitorTemplate<InS,OutS,Prop>::draw() {
    checkMode();
    checkResolution();
    
    resetCursor();

    if (!isPrinted) {
      printPage();
      isPrinted = true;
    } else {
      switch (drawmode) {
      case DrawBehaviour::Primitive:
        overDraw();
        break;
      case DrawBehaviour::Lazy:
        lazyDraw();
        break;
      }
    }

    updateCursor();
  }
}
