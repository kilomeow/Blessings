#include "monitor.hpp"
#include "additional_structs.hpp"
#include "terminal_io.hpp"
#include "symbol/symbol.hpp"

namespace blessings {
  template <class InS, class OutS>
  Monitor<InS,OutS>::Monitor(int MaxSize) {
    if (MaxSize <= 0) throw Error();   // ::Error("wrong MaxSize")
    maxSize = MaxSize;
    grid = new MonitorCell<OutS> [maxSize];
    res.width=1; res.height=1;
    MonitorCell<OutS>::compare = false;
  }
  
  template <class InS, class OutS>
  Monitor<InS,OutS>::~Monitor() {
    delete [] grid;
  }

  template <class InS, class OutS>
  Monitor<InS,OutS>::Monitor(const Monitor& monitor) {
    termIO = monitor.termIO;
    maxSize = monitor.maxSize;
    res = monitor.res;
    grid = new MonitorCell<OutS> [maxSize];
    for (int i=0;i<maxSize;i++)
      grid[i] = monitor.grid[i];
  }

  template <class InS, class OutS>
  Monitor<InS,OutS>& Monitor<InS,OutS>::operator=(const Monitor& monitor) {
    termIO = monitor.termIO;
    maxSize = monitor.maxSize;
    res = monitor.res;
    delete [] grid;
    grid = new MonitorCell<OutS> [maxSize];
    for (int i=0;i<maxSize;i++)
      grid[i] = monitor.grid[i];
    return (*this);
  }
  
  template <class InS, class OutS>
  void Monitor<InS,OutS>::connect(TerminalIO<InS,OutS>* Term) {
    termIO = Term;
  }
  
  template <class InS, class OutS>
  void Monitor<InS,OutS>::disconnect() {
    termIO = TerminalIO<InS,OutS>();
  }
  
  template <class InS, class OutS>
  void Monitor<InS,OutS>::startWork() {
    // termIO->resetDeviceMode();
    termIO->setNonCanonicalMode();
    termIO->setEchoInhibition();
    termIO->hideCursor();
    clearScreen();
    moveCursorTo(1, 1);
  }
  
  template <class InS, class OutS>
  void Monitor<InS,OutS>::endWork() {
    termIO->setCanonicalMode();
    termIO->setEchoForward();
    termIO->showCursor();
    clearScreen();
    moveCursorTo(1, 1);
  }

  template <class InS, class OutS>
  GridPos Monitor<InS,OutS>::positionOf(int index) const {
    GridPos gp;
    gp.x = index%res.width;
    gp.y = index/res.width;
    return gp;
  }

  template <class InS, class OutS>
  int Monitor<InS,OutS>::indexOf(GridPos gp) const {
    return gp.x+gp.y*res.width;
  }

  template <class InS, class OutS>
  int Monitor<InS,OutS>::currentBound() const {
    return res.width*res.height;
  }

  template <class InS, class OutS>
  MonitorCell<OutS>& Monitor<InS,OutS>::operator[] (int p) {
    if ((p<0) || (p>=currentBound())) throw Monitor::Error();
    //Monitor::Error("p out of range");
    return grid[p];
  }

  template <class InS, class OutS>
  MonitorCell<OutS> Monitor<InS,OutS>::operator[] (int p) const {
    if ((p<0) || (p>=currentBound())) throw Monitor::Error();
    //Monitor::Error("p out of range");
    return grid[p];
  }

  template <class InS, class OutS>
  MonitorCell<OutS>& Monitor<InS,OutS>::operator() (int x, int y) {
    int p = x+y*res.width;
    if ((p<0) || (p>=currentBound())) throw Monitor::Error();
    //Monitor::Error("p out of range");
    return grid[p];
  }

  template <class InS, class OutS>
  MonitorCell<OutS> Monitor<InS,OutS>::operator() (int x, int y) const {
    int p = x+y*res.width;
    if ((p<0) || (p>=currentBound())) throw Monitor::Error();
    //Monitor::Error("p out of range");
    return grid[p];
  }

  template <class InS, class OutS>
  MonitorCell<OutS>& Monitor<InS,OutS>::at (int p) {
    return (*this)[p];
  }

  template <class InS, class OutS>
  MonitorCell<OutS> Monitor<InS,OutS>::at (int p) const {
    return (*this)[p];
  }

  template <class InS, class OutS>
  MonitorCell<OutS>& Monitor<InS,OutS>::at (int x, int y) {
    return (*this)(x, y);
  }

  template <class InS, class OutS>
  MonitorCell<OutS> Monitor<InS,OutS>::at (int x, int y) const {
    return (*this)(x, y);
  }

  template <class InS, class OutS>
  Monitor<InS,OutS>::Iterator::Iterator(MonitorCell<OutS>* grd, int pnt, int bnd) {
    if ((pnt<0) || (pnt>bnd)) throw Monitor::Iterator::Error();
    //Monitor::Iterator::Error("pointer out of range");
    grid = grd;
    pointer = pnt;
    stopPos = bnd;
  }

  template <class InS, class OutS>
  MonitorCell<OutS>& Monitor<InS,OutS>::Iterator::operator*() {
    if (pointer==stopPos) throw Monitor::Iterator::EndError();
    //Monitor::Iterator::EndError("pointer is at end");
    return grid[pointer];
  }

  template <class InS, class OutS>
  typename Monitor<InS,OutS>::Iterator& Monitor<InS,OutS>::Iterator::operator++() {
    if (pointer==stopPos) throw Monitor::Iterator::EndError();
    //Monitor::Iterator::EndError("pointer is at end");
    pointer++;
    return (*this);
  }

  template <class InS, class OutS>
  typename Monitor<InS,OutS>::Iterator Monitor<InS,OutS>::Iterator::operator++(int a) {
    if (pointer==stopPos) throw Monitor::Iterator::EndError();
    //Monitor::Iterator::EndError("pointer is at end");
    Monitor::Iterator i = (*this);
    ++(*this);
    return i;
  }

  template <class InS, class OutS>
  int Monitor<InS,OutS>::Iterator::index() {
    return pointer;
  }

  template <class InS, class OutS>
  bool Monitor<InS,OutS>::Iterator::isEnd() {
    return (pointer==stopPos);
  }

  template <class InS, class OutS>
  typename Monitor<InS,OutS>::Iterator Monitor<InS,OutS>::begin() {
    Monitor::Iterator i(grid, 0, currentBound());
    return i;
  }

  template <class InS, class OutS>
  typename Monitor<InS,OutS>::Iterator Monitor<InS,OutS>::end() {
    Monitor::Iterator i(grid, currentBound(), currentBound());
    return i;
  }


  template <class InS, class OutS>
  void Monitor<InS,OutS>::tile(OutS s, const Property* p) {
    MonitorCell<OutS> c(s, p);
    Monitor::Iterator i = begin();
    while (!i.isEnd()) {
      (*i) = c;
      i++;
    }
  }

  template <class InS, class OutS>
  MonitorResolution Monitor<InS,OutS>::getCurrentResolution() {
    return res;
  }

  template <class InS, class OutS>
  MonitorResolution Monitor<InS,OutS>::getTerminalResolution() {
    return termIO->getResolution();
  }

  template <class InS, class OutS>
  void Monitor<InS,OutS>::setResolution(MonitorResolution mr) {
    if ((mr.width<=0) || (mr.height<=0)) throw Error(); // "wrong resolution"
    if (mr.width*mr.height>maxSize) throw Error(); // "resolution out of range"
    res = mr;
  }

  template <class InS, class OutS>
  void Monitor<InS,OutS>::setResolution(int w, int h) {
    MonitorResolution mr(w, h);
    setResolution(mr);
  }

  template <class InS, class OutS>
  void Monitor<InS,OutS>::moveCursor(int x, int y) {
    termIO->moveCursor(x, y);
  }

  template <class InS, class OutS>
  void Monitor<InS,OutS>::moveCursorTo(int x, int y) {
    termIO->moveCursorTo(x, y);
  }

  template <class InS, class OutS>
  void Monitor<InS,OutS>::moveCursorTo(GridPos pos) {
    termIO->moveCursorTo(pos.x+1, pos.y+1);
  }

  template <class InS, class OutS>
  void Monitor<InS,OutS>::hideCursor() {
    termIO->hideCursor();
  }

  template <class InS, class OutS>
  void Monitor<InS,OutS>::showCursor() {
    termIO->showCursor();
  }

  template <class InS, class OutS>
  void Monitor<InS,OutS>::saveCursorPos() {
    termIO->saveCursorPos();
  }

  template <class InS, class OutS>
  void Monitor<InS,OutS>::restoreCursorPos() {
    termIO->restoreCursorPos();
  }

  template <class InS, class OutS>
  std::queue<InS> Monitor<InS,OutS>::getSymbol(int n) {
    return termIO->getSymbol(n);
  }

  template <class InS, class OutS>
  void Monitor<InS,OutS>::printSymbol(OutS symb, const Property* prop) {
    termIO->print(symb, prop);
  }

  template <class InS, class OutS>
  void Monitor<InS,OutS>::printSymbol(OutS symb) {
    termIO->print(symb);
  }

  template <class InS, class OutS>
  void Monitor<InS,OutS>::updateResolution() {
    setResolution(getTerminalResolution());
  }

  template <class InS, class OutS>
  void Monitor<InS,OutS>::checkResolution(resChange drawMode) {
    switch (drawMode) {
    case alarm: {
      if ((getTerminalResolution().width != res.width) ||
          (getTerminalResolution().height != res.height))
        throw ResolutionDisparity();
        break;
      }
    case ignoreExtension: {
      if ((getTerminalResolution().width < res.width) ||
          (getTerminalResolution().height < res.height))
        throw ResolutionDisparity();
        break;
    }
    case ignore: {
      break;
    }
    }
  }

  template <class InS, class OutS>
  void Monitor<InS,OutS>::checkMode() {
    if (termIO->isNonCanonical() != 1) throw TerminalModeError();
    if (termIO->isEchoInhibited() != 1) throw TerminalModeError();
  }

  template <class InS, class OutS>
  void Monitor<InS,OutS>::clearScreen() {
    termIO->clearScreen();
  }

  template <class InS, class OutS>
  void Monitor<InS,OutS>::printPage() {
    Monitor::Iterator i = begin();
    while (!i.isEnd()) {
      termIO->print((*i).symb, (*i).prop);
      (*i).setStaged();
      i++;
      if (i.index()%res.width==0) termIO->newLine();
    }
  }

  template <class InS, class OutS>
  void Monitor<InS,OutS>::draw(Monitor::resChange drawMode) {
    checkMode();
    checkResolution(drawMode);
    moveCursorTo(1, 1);
    printPage();
  }

  template <class InS, class OutS>
  void Monitor<InS,OutS>::lazyDraw(Monitor::resChange drawMode) {
    checkMode();
    checkResolution(drawMode);
    Monitor::Iterator i = begin();
    while (!i.isEnd()) {
      if ((*i).unstaged) {
        moveCursorTo(positionOf(i.index()));
        termIO->print((*i).symb, (*i).prop);
        (*i).setStaged();
      }
      i++;
    }
  }
  
  template <class InS, class OutS>
  void Monitor<InS,OutS>::hardOptimization(bool p) {
    MonitorCell<OutS>::compare = p;
  }

  template <class InS, class OutS>
  int Monitor<InS,OutS>::boldSupported() {
    return termIO->boldSupported();
  }

  template <class InS, class OutS>
  int Monitor<InS,OutS>::italicsSupported() {
    return termIO->italicsSupported();
  }

  template <class InS, class OutS>
  PropertyType Monitor<InS,OutS>::getPropertyType() {
    return termIO->getPropertyType();
  }
}
