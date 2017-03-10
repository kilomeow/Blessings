#pragma once

#include <queue>
#include <algorithm>

#include "monitor.hpp"
#include "additional_structs.hpp"
#include "terminal_io.hpp"

namespace blessings {
  template <typename InS, typename OutS, typename Prop>
  Monitor<InS,OutS,Prop>::Monitor(int MaxSize) {
    if (MaxSize <= 0) throw Error();   // ::Error("wrong MaxSize")
    maxSize = MaxSize;
    grid = new Monitor<InS,OutS,Prop>::Cell [maxSize];
    res.width=1; res.height=1;
    Monitor<InS,OutS,Prop>::Cell::hardopt = false;
  }

  template <typename InS, typename OutS, typename Prop>
  Monitor<InS,OutS,Prop>::~Monitor() {
    delete [] grid;
  }

  template <typename InS, typename OutS, typename Prop>
  Monitor<InS,OutS,Prop>::Monitor(const Monitor& monitor) {
    termIO = monitor.termIO;
    maxSize = monitor.maxSize;
    res = monitor.res;
    grid = new Monitor<InS,OutS,Prop>::Cell [maxSize];
    for (int i=0;i<maxSize;i++)
      grid[i] = monitor.grid[i];
  }

  template <typename InS, typename OutS, typename Prop>
  Monitor<InS,OutS,Prop>& Monitor<InS,OutS,Prop>::operator=(const Monitor& monitor) {
    termIO = monitor.termIO;
    maxSize = monitor.maxSize;
    res = monitor.res;
    isDrawn = false;
    delete [] grid;
    grid = new Monitor<InS,OutS,Prop>::Cell [maxSize];
    for (int i=0;i<maxSize;i++)
      grid[i] = monitor.grid[i];
    return (*this);
  }

  template <typename InS, typename OutS, typename Prop>
  void Monitor<InS,OutS,Prop>::connect(TerminalIO<InS,OutS,Prop>* Term) {
    termIO = Term;
  }

  template <typename InS, typename OutS, typename Prop>
  void Monitor<InS,OutS,Prop>::disconnect() {
    termIO = nullptr;
  }

  template <typename InS, typename OutS, typename Prop>
  void Monitor<InS,OutS,Prop>::startWork() {
    termIO->setNonCanonicalMode();
    termIO->setEchoInhibition();
    clearScreen();
    resetCursor();
  }

  template <typename InS, typename OutS, typename Prop>
  void Monitor<InS,OutS,Prop>::endWork() {
    termIO->setCanonicalMode();
    termIO->setEchoForward();
    clearScreen();
    resetCursor();
    showCursor();
  }

  template <typename InS, typename OutS, typename Prop>
  GridPos Monitor<InS,OutS,Prop>::positionOf(int index) const {
    GridPos gp;
    gp.x = index%res.width;
    gp.y = index/res.width;
    return gp;
  }

  template <typename InS, typename OutS, typename Prop>
  int Monitor<InS,OutS,Prop>::indexOf(GridPos gp) const {
    return gp.x+gp.y*res.width;
  }

  template <typename InS, typename OutS, typename Prop>
  int Monitor<InS,OutS,Prop>::bound() const {
    return res.width*res.height;
  }

  template <typename InS, typename OutS, typename Prop>
  typename Monitor<InS,OutS,Prop>::Cell& Monitor<InS,OutS,Prop>::operator[] (int p) {
    if ((p<0) || (p>=bound())) throw Monitor::Error();
    //Monitor::Error("p out of range");
    return grid[p];
  }

  template <typename InS, typename OutS, typename Prop>
  typename Monitor<InS,OutS,Prop>::Cell Monitor<InS,OutS,Prop>::operator[] (int p) const {
    if ((p<0) || (p>=bound())) throw Monitor::Error();
    //Monitor::Error("p out of range");
    return grid[p];
  }

  template <typename InS, typename OutS, typename Prop>
  typename Monitor<InS,OutS,Prop>::Cell& Monitor<InS,OutS,Prop>::operator() (int x, int y) {
    if ((x<0) || (x>res.width) || (y<0) || (y>res.height)) throw Error();
    //Monitor::Error("(x,y) out of range");
    return grid[x+y*res.width];
  }

  template <typename InS, typename OutS, typename Prop>
  typename Monitor<InS,OutS,Prop>::Cell Monitor<InS,OutS,Prop>::operator() (int x, int y) const {
    if ((x<0) || (x>res.width) || (y<0) || (y>res.height)) throw Error();
    //Monitor::Error("(x,y) out of range");
    return grid[x+y*res.width];
  }

  template <typename InS, typename OutS, typename Prop>
  typename Monitor<InS,OutS,Prop>::Cell& Monitor<InS,OutS,Prop>::operator() (GridPos p) {
    return this->at(p.x, p.y);
  }

  template <typename InS, typename OutS, typename Prop>
  typename Monitor<InS,OutS,Prop>::Cell Monitor<InS,OutS,Prop>::operator() (GridPos p) const {
    return this->at(p.x, p.y);
  }

  template <typename InS, typename OutS, typename Prop>
  typename Monitor<InS,OutS,Prop>::Cell& Monitor<InS,OutS,Prop>::at (int p) {
    return (*this)[p];
  }

  template <typename InS, typename OutS, typename Prop>
  typename Monitor<InS,OutS,Prop>::Cell Monitor<InS,OutS,Prop>::at (int p) const {
    return (*this)[p];
  }

  template <typename InS, typename OutS, typename Prop>
  typename Monitor<InS,OutS,Prop>::Cell& Monitor<InS,OutS,Prop>::at (int x, int y) {
    return (*this)(x, y);
  }

  template <typename InS, typename OutS, typename Prop>
  typename Monitor<InS,OutS,Prop>::Cell Monitor<InS,OutS,Prop>::at (int x, int y) const {
    return (*this)(x, y);
  }

  template <typename InS, typename OutS, typename Prop>
  typename Monitor<InS,OutS,Prop>::Cell& Monitor<InS,OutS,Prop>::at (GridPos p) {
    return this->at(p.x, p.y);
  }

  template <typename InS, typename OutS, typename Prop>
  typename Monitor<InS,OutS,Prop>::Cell Monitor<InS,OutS,Prop>::at (GridPos p) const {
    return this->at(p.x, p.y);
  }

  template <typename InS, typename OutS, typename Prop>
  Monitor<InS,OutS,Prop>::Cell::Cell(const Monitor<InS,OutS,Prop>::Cell& cell) {
    symb = cell.symb;
    prop = cell.prop;
  }

  template <typename InS, typename OutS, typename Prop>
  typename Monitor<InS,OutS,Prop>::Cell& Monitor<InS,OutS,Prop>::Cell::operator=(const Monitor<InS,OutS,Prop>::Cell& cell) {
    if (hardopt && (symb==cell.symb) && (prop==cell.prop)) {
      // do nothing
    } else {
      symb = cell.symb;
      prop = cell.prop;
      unstaged = true;
    }
    return (*this);
  }

  template <typename InS, typename OutS, typename Prop>
  bool Monitor<InS,OutS,Prop>::Cell::isUnstaged() {
    return unstaged;
  }

  template <typename InS, typename OutS, typename Prop>
  void Monitor<InS,OutS,Prop>::Cell::setStaged() {
    unstaged = false;
  }

  template <typename InS, typename OutS, typename Prop>
  void Monitor<InS,OutS,Prop>::Cell::setUnstaged() {
    unstaged = true;
  }

  template <typename InS, typename OutS, typename Prop>
  Monitor<InS,OutS,Prop>::Iterator::Iterator(Monitor<InS,OutS,Prop>::Cell* Grid, int ptr, int bound) {
    if ((ptr<0) || (ptr>bound)) throw Monitor::Iterator::Error();
    //Monitor::Iterator::Error("pointer out of range");
    grid = Grid;
    pointer = ptr;
    stopPos = bound;
  }

  template <typename InS, typename OutS, typename Prop>
  Monitor<InS,OutS,Prop>::Iterator::Iterator(const Iterator& it) {
    grid = it.grid;
    pointer = it.pointer;
    stopPos = it.stopPos;
  }

  template <typename InS, typename OutS, typename Prop>
  typename Monitor<InS,OutS,Prop>::Iterator& Monitor<InS,OutS,Prop>::Iterator::operator=(const Iterator& it) {
    grid = it.grid;
    pointer = it.pointer;
    stopPos = it.stopPos;
    return (*this);
  }

  template <typename InS, typename OutS, typename Prop>
  typename Monitor<InS,OutS,Prop>::Cell& Monitor<InS,OutS,Prop>::Iterator::operator*() {
    if (pointer==stopPos) throw Monitor::Iterator::EndError();
    //Monitor::Iterator::EndError("pointer is at end");
    return grid[pointer];
  }

  template <typename InS, typename OutS, typename Prop>
  typename Monitor<InS,OutS,Prop>::Cell* Monitor<InS,OutS,Prop>::Iterator::operator->() {
    if (pointer==stopPos) throw Monitor::Iterator::EndError();
    //Monitor::Iterator::EndError("pointer is at end");
    return &grid[pointer];
  }

  template <typename InS, typename OutS, typename Prop>
  typename Monitor<InS,OutS,Prop>::Iterator& Monitor<InS,OutS,Prop>::Iterator::operator++() {
    if (pointer==stopPos) throw Monitor::Iterator::EndError();
    //Monitor::Iterator::EndError("pointer is at end");
    pointer++;
    return (*this);
  }

  template <typename InS, typename OutS, typename Prop>
  typename Monitor<InS,OutS,Prop>::Iterator Monitor<InS,OutS,Prop>::Iterator::operator++(int a) {
    if (pointer==stopPos) throw Monitor::Iterator::EndError();
    //Monitor::Iterator::EndError("pointer is at end");
    Monitor::Iterator i = (*this);
    ++(*this);
    return i;
  }

  template <typename InS, typename OutS, typename Prop>
  typename Monitor<InS,OutS,Prop>::Iterator& Monitor<InS,OutS,Prop>::Iterator::operator--() {
    if (pointer==0) throw Monitor::Iterator::EndError();
    //Monitor::Iterator::EndError("pointer is at end");
    pointer--;
    return (*this);
  }

  template <typename InS, typename OutS, typename Prop>
  typename Monitor<InS,OutS,Prop>::Iterator Monitor<InS,OutS,Prop>::Iterator::operator--(int a) {
    if (pointer==0) throw Monitor::Iterator::EndError();
    //Monitor::Iterator::EndError("pointer is at end");
    Monitor::Iterator i = (*this);
    --(*this);
    return i;
  }

  template <typename InS, typename OutS, typename Prop>
  typename Monitor<InS,OutS,Prop>::Iterator Monitor<InS,OutS,Prop>::Iterator::operator+(int k) {
    int newptr = pointer+k;
    if ((newptr < 0) || (newptr > stopPos)) throw Monitor::Iterator::Error();
    Iterator it(grid, newptr, stopPos);
    return it;
  }

  template <typename InS, typename OutS, typename Prop>
  typename Monitor<InS,OutS,Prop>::Iterator Monitor<InS,OutS,Prop>::Iterator::operator-(int k) {
    return this->operator+(-k);
  }

  template <typename InS, typename OutS, typename Prop>
  void Monitor<InS,OutS,Prop>::Iterator::operator+=(int k) {
    this->operator=(this->operator+(k));
  }

  template <typename InS, typename OutS, typename Prop>
  void Monitor<InS,OutS,Prop>::Iterator::operator-=(int k) {
    this->operator=(this->operator-(k));
  }

  template <typename InS, typename OutS, typename Prop>
  int Monitor<InS,OutS,Prop>::Iterator::index() {
    return pointer;
  }

  template <typename InS, typename OutS, typename Prop>
  bool Monitor<InS,OutS,Prop>::Iterator::isBegin() {
    return (pointer==0);
  }

  template <typename InS, typename OutS, typename Prop>
  bool Monitor<InS,OutS,Prop>::Iterator::isEnd() {
    return (pointer==stopPos);
  }

  template <typename InS, typename OutS, typename Prop>
  void Monitor<InS,OutS,Prop>::Iterator::rewind() {
    pointer=0;
  }

  template <typename InS, typename OutS, typename Prop>
  bool Monitor<InS,OutS,Prop>::Iterator::operator==(const Iterator& it) {
    if (!comparable(it)) throw Monitor::Iterator::Error();
    return (pointer == it.pointer);
  }

  template <typename InS, typename OutS, typename Prop>
  bool Monitor<InS,OutS,Prop>::Iterator::operator!=(const Iterator& it) {
    return !((*this) == it);
  }

  template <typename InS, typename OutS, typename Prop>
  bool Monitor<InS,OutS,Prop>::Iterator::operator>=(const Iterator& it) {
    if (!comparable(it)) throw Monitor::Iterator::Error();
    return (pointer >= it.pointer);
  }

  template <typename InS, typename OutS, typename Prop>
  bool Monitor<InS,OutS,Prop>::Iterator::operator<=(const Iterator& it) {
    if (!comparable(it)) throw Monitor::Iterator::Error();
    return (pointer <= it.pointer);
  }

  template <typename InS, typename OutS, typename Prop>
  bool Monitor<InS,OutS,Prop>::Iterator::operator>(const Iterator& it) {
    return (((*this)!=it) && ((*this)>=it));
  }

  template <typename InS, typename OutS, typename Prop>
  bool Monitor<InS,OutS,Prop>::Iterator::operator<(const Iterator& it) {
    return (((*this)!=it) && ((*this)<=it));
  }

  template <typename InS, typename OutS, typename Prop>
  bool Monitor<InS,OutS,Prop>::Iterator::comparable(const Iterator& it) {
    return ((grid==it.grid) && (stopPos==it.stopPos));
  }

  template <typename InS, typename OutS, typename Prop>
  typename Monitor<InS,OutS,Prop>::Iterator Monitor<InS,OutS,Prop>::begin() {
    Monitor::Iterator i(grid, 0, bound());
    return i;
  }

  template <typename InS, typename OutS, typename Prop>
  typename Monitor<InS,OutS,Prop>::Iterator Monitor<InS,OutS,Prop>::end() {
    Monitor::Iterator i(grid, bound(), bound());
    return i;
  }


  template <typename InS, typename OutS, typename Prop>
  void Monitor<InS,OutS,Prop>::tile(OutS s, Prop p) {
    Monitor::Cell c(s, p);
    Monitor::Iterator i = begin();
    while (!i.isEnd()) {
      (*i) = c;
      i++;
    }
  }

  template <typename InS, typename OutS, typename Prop>
  void Monitor<InS,OutS,Prop>::tile(OutS s) {
    tile(s, Prop::empty);
  }

  template <typename InS, typename OutS, typename Prop>
  void Monitor<InS,OutS,Prop>::tile() {
    tile(OutS::space, Prop::empty);
  }

  template <typename InS, typename OutS, typename Prop>
  void Monitor<InS,OutS,Prop>::tile(OutS s, Prop p, int x1, int y1, int x2, int y2) {
    int l = std::min(x1, x2); //left
    int r = std::max(x1, x2); //right
    int u = std::min(y1, y2); //up
    int d = std::max(y1, y2); //down

    if ((l<0) || (r>=res.width) || (u<0) || (d>=res.height))
      throw Monitor::ResolutionDisparity();

    Monitor::Cell c(s, p);

    for (int j=l;j<=r;j++)
    for (int i=u;i<=d;i++)
      this->at(j, i) = c;
  }

  template <typename InS, typename OutS, typename Prop>
  void Monitor<InS,OutS,Prop>::tile(OutS s, int x1, int y1, int x2, int y2) {
    tile(s, Prop::empty, x1, y1, x2, y2);
  }

  template <typename InS, typename OutS, typename Prop>
  void Monitor<InS,OutS,Prop>::tile(int x1, int y1, int x2, int y2) {
    tile(OutS::space, Prop::empty, x1, y1, x2, y2);
  }

  template <typename InS, typename OutS, typename Prop>
  void Monitor<InS,OutS,Prop>::tile(OutS s, Prop p, GridPos p1, GridPos p2) {
    tile(s, p, p1.x, p1.y, p2.x, p2.y);
  }

  template <typename InS, typename OutS, typename Prop>
  void Monitor<InS,OutS,Prop>::tile(OutS s, GridPos p1, GridPos p2) {
    tile(s, Prop::empty, p1.x, p1.y, p2.x, p2.y);
  }

  template <typename InS, typename OutS, typename Prop>
  void Monitor<InS,OutS,Prop>::tile(GridPos p1, GridPos p2) {
    tile(OutS::space, Prop::empty, p1.x, p1.y, p2.x, p2.y);
  }

  template <typename InS, typename OutS, typename Prop>
  void Monitor<InS,OutS,Prop>::tile(OutS s, Prop p, GridPos p1, Resolution r) {
    tile(s, p, p1.x, p1.y, p1.x+r.width, p1.y+r.height);
  }

  template <typename InS, typename OutS, typename Prop>
  void Monitor<InS,OutS,Prop>::tile(OutS s, GridPos p1, Resolution r) {
    tile(s, Prop::empty, p1.x, p1.y, p1.x+r.width, p1.y+r.height);
  }

  template <typename InS, typename OutS, typename Prop>
  void Monitor<InS,OutS,Prop>::tile(GridPos p1, Resolution r) {
    tile(OutS::space, Prop::empty, p1.x, p1.y, p1.x+r.width, p1.y+r.height);
  }

  template <typename InS, typename OutS, typename Prop>
  Resolution Monitor<InS,OutS,Prop>::resolution() {
    return res;
  }

  template <typename InS, typename OutS, typename Prop>
  Resolution Monitor<InS,OutS,Prop>::terminalResolution() {
    return termIO->getResolution();
  }

  template <typename InS, typename OutS, typename Prop>
  void Monitor<InS,OutS,Prop>::setResolution(Resolution mr) {
    if ((mr.width<=0) || (mr.height<=0)) throw Error(); // "wrong resolution"
    if (mr.width*mr.height>maxSize) throw Error(); // "resolution out of range"
    res = mr;
    resetCursor();
    isDrawn = false;
  }

  template <typename InS, typename OutS, typename Prop>
  void Monitor<InS,OutS,Prop>::setResolution(int w, int h) {
    Resolution mr(w, h);
    setResolution(mr);
  }

  template <typename InS, typename OutS, typename Prop>
  void Monitor<InS,OutS,Prop>::moveCursor(int x, int y) {
    moveCursorTo(cursorPos.x + x, cursorPos.y + y);
  }

  template <typename InS, typename OutS, typename Prop>
  void Monitor<InS,OutS,Prop>::moveCursor(int p) {
    moveCursorTo(indexOf(cursorPos)+p);
  }

  template <typename InS, typename OutS, typename Prop>
  void Monitor<InS,OutS,Prop>::moveCursorTo(int x, int y) {
    if ((x<0) || (x>res.width) || (y<0) || (y>res.height)) throw Error();
    termIO->moveCursorTo(x+1, y+1);
    GridPos cursorPos(x, y);
  }

  template <typename InS, typename OutS, typename Prop>
  void Monitor<InS,OutS,Prop>::moveCursorTo(int p) {
    moveCursorTo(positionOf(p));
  }

  template <typename InS, typename OutS, typename Prop>
  void Monitor<InS,OutS,Prop>::moveCursorTo(GridPos pos) {
    moveCursorTo(pos.x, pos.y);
  }

  template <typename InS, typename OutS, typename Prop>
  void Monitor<InS,OutS,Prop>::resetCursor() {
    hideCursor();
    moveCursorTo(0, 0);
  }

  template <typename InS, typename OutS, typename Prop>
  void Monitor<InS,OutS,Prop>::hideCursor() {
    termIO->hideCursor();
    cursorVisible = false;
  }

  template <typename InS, typename OutS, typename Prop>
  void Monitor<InS,OutS,Prop>::showCursor() {
    termIO->showCursor();
    cursorVisible = true;
  }

  template <typename InS, typename OutS, typename Prop>
  GridPos Monitor<InS,OutS,Prop>::cursorPosition() {
    return cursorPos;
  }

  template <typename InS, typename OutS, typename Prop>
  bool Monitor<InS,OutS,Prop>::isCursorVisible() {
    return cursorVisible;
  }

  template <typename InS, typename OutS, typename Prop>
  void Monitor<InS,OutS,Prop>::clearInputBuffer() {
    termIO->clearInputBuffer();
  }

  template <typename InS, typename OutS, typename Prop>
  void Monitor<InS,OutS,Prop>::saveCursor() {
    termIO->saveCursorPos();
    cursorVisibleSlot = cursorVisible;
  }

  template <typename InS, typename OutS, typename Prop>
  void Monitor<InS,OutS,Prop>::restoreCursor() {
    termIO->restoreCursorPos();
    if (cursorVisibleSlot) {
      showCursor();
    } else {
      hideCursor();
    }
  }

  template <typename InS, typename OutS, typename Prop>
  std::queue<InS> Monitor<InS,OutS,Prop>::getSymbol(int n) {
    return termIO->getSymbol(n);
  }

  template <typename InS, typename OutS, typename Prop>
  void Monitor<InS,OutS,Prop>::printSymbol(OutS symb, Prop prop) {
    termIO->print(symb, prop);
  }

  template <typename InS, typename OutS, typename Prop>
  void Monitor<InS,OutS,Prop>::printSymbol(OutS symb) {
    termIO->print(symb);
  }

  template <typename InS, typename OutS, typename Prop>
  void Monitor<InS,OutS,Prop>::updateResolution() {
    setResolution(terminalResolution());
  }

  template <typename InS, typename OutS, typename Prop>
  void Monitor<InS,OutS,Prop>::checkResolution(resChange drawMode) {
    switch (drawMode) {
    case alarm: {
      if ((terminalResolution().width != res.width) ||
          (terminalResolution().height != res.height))
        throw ResolutionDisparity();
        break;
      }
    case ignoreExtension: {
      if ((terminalResolution().width < res.width) ||
          (terminalResolution().height < res.height))
        throw ResolutionDisparity();
        break;
    }
    case ignore: {
      break;
    }
    }
  }

  template <typename InS, typename OutS, typename Prop>
  void Monitor<InS,OutS,Prop>::checkMode() {
    if (termIO->isNonCanonical() != 1) throw TerminalModeError();
    if (termIO->isEchoInhibited() != 1) throw TerminalModeError();
  }

  template <typename InS, typename OutS, typename Prop>
  void Monitor<InS,OutS,Prop>::clearScreen() {
    termIO->clearScreen();
  }

  template <typename InS, typename OutS, typename Prop>
  void Monitor<InS,OutS,Prop>::printPage() {
    Monitor::Iterator i = begin();
    while (!i.isEnd()) {
      termIO->print(i->symbol(), i->property());
      i->setStaged();
      i++;
      if (i.index()%res.width==0) termIO->newLine();
    }
  }

  template <typename InS, typename OutS, typename Prop>
  void Monitor<InS,OutS,Prop>::draw(Monitor::resChange drawMode) {
    checkMode();
    checkResolution(drawMode);

    saveCursor();
    resetCursor();

    printPage();
    isDrawn = true;

    restoreCursor();
  }

  template <typename InS, typename OutS, typename Prop>
  void Monitor<InS,OutS,Prop>::lazyDraw(Monitor::resChange drawMode) {
    if (!isDrawn) {
      draw();
      return;
    }

    checkMode();
    checkResolution(drawMode);

    saveCursor();
    resetCursor();

    Monitor::Iterator i = begin();
    while (!i.isEnd()) {
      if (i->isUnstaged()) {
        moveCursorTo(i.index());
        termIO->print(i->symbol(), i->property());
        i->setStaged();
      }
      i++;
    }

    restoreCursor();
  }

  template <typename InS, typename OutS, typename Prop>
  void Monitor<InS,OutS,Prop>::hardOptimization(bool p) {
    Monitor<InS,OutS,Prop>::Cell::hardopt = p;
  }
}
