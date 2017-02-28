#include <cstdio>
#include <string>
#include <chrono>
#include <thread>

#include "symbol/symbolutf8.hpp"
#include "symbol/symbol.hpp"
#include "ansilinux/terminalio.hpp"
#include "monitor.cpp"
#include "astructs.hpp"

using namespace std;
using namespace blessings;

typedef SymbolUTF8 S;
typedef PropertyANSI P;
typedef TerminalIOANSILinux<S, S, P> TL;
typedef Monitor<S, S> M;
typedef MonitorCell<S> Cell;


int main() {
  TL term;

  term.Init();

  term.setNonCanonicalMode();
  term.setEchoInhibition();

  M monitor(&term, 2000);
  monitor.setResolution(50, 10);
  monitor.clearScreen();

  FILE * in = fopen("logo.txt", "r");
  int s;
  char c;
  bool ex=false;

  const P p(ColorANSI(3));

  for (int t=0;t<300;t++) {
    rewind(in);
    s = 0;

    while (s<500) {
      for (int k=0;k<=t;k++) fscanf(in, "%c", &c);

      for (int k=0;k<50;k++) {
        if (c==*"\n") ex = true;
        if (ex) break;

        //if (c!=*".") {
        //  const P p(ColorANSI(rand()%6+1));
        //  monitor[s] = Cell(S(c), &p);
        //} else {
        //  const P p();
        //  monitor[s] = Cell(S(c), &p);
        //}

        monitor[s] = Cell(S(c), &p);

        fscanf(in, "%c", &c);
        s++;
      }

      if (ex) break;

      while (c !=*"\n") fscanf(in, "%c", &c);
    }

    if (ex) break;

    monitor.draw(M::resChange::ignore);
    this_thread::sleep_for(chrono::milliseconds(50));
  }

  fclose(in);

  return 0;
}
