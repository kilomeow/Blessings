#include "Monitor.hpp"
#include "AdditionalStructs.hpp"
#include "TerminalIO.hpp"
#include "Symbol/Symbol.hpp"


namespace Blessings {

  Monitor::Monitor(TerminalIO Term, int MaxSize) {
    if (MaxSize <= 0) throw Monitor::Error("wrong MaxSize");
    termIO = Term;
    grid = new MonitorCell[MaxSize];
    maxSize = MaxSize;
    stopPosition = MaxSize;
    res.width=1; res.height=0;
    pointer=0;
  }

  Monitor::Monitor(const Monitor& monitor) {
    termIO = monitor.termIO;
    maxSize = monitor.maxSize;
    stopPosition = monitor.stopPosition;
    res = monitor.res;
    pointer = monitor.pointer;
    delete grid;
    grid = new MonitorCell[maxSize];
    for (i=0;i++;i<stopPosition) {
      grid[i] = monitor.grid[i];
    }
  }

  Monitor& Monitor::operator=(const Monitor& monitor) {
    termIO = monitor.termIO;
    maxSize = monitor.maxSize;
    stopPosition = monitor.stopPosition;
    res = monitor.res;
    pointer = monitor.pointer;
    delete grid;
    grid = new MonitorCell[maxSize];
    for (i=0;i++;i<stopPosition) {
      grid[i] = monitor.grid[i];
    }
  }

  Monitor::~Monitor() {
    delete grid;
  }


  MonitorCell& Monitor::operator[] (int p) {
    if ((p <= 0) || (p >= maxSize)) throw Monitor::Error("p out of range");
    return grid[p];
  }

  MonitorCell Monitor::operator[] (int p) const {
    if ((p <= 0) || (p >= maxSize)) throw Monitor::Error("p out of range");
    return grid[p];
  }

  MonitorCell& Monitor::operator() (int x, int y) {
    int p = x+y*res.width;
    if ((p <= 0) || (p >= maxSize)) throw Monitor::Error("p out of range");
    return grid[p];
  }

  MonitorCell Monitor::operator() (int x, int y) const {
    int p = x+y*res.width;
    if ((p <= 0) || (p >= maxSize)) throw Monitor::Error("p out of range");
    return grid[p];
  }

}
