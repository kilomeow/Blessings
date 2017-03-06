#include <cstdio>
#include <string>
#include <chrono>
#include <thread>
#include <queue>

#include "symbol_utf8/symbol_utf8.hpp"
#include "property.hpp"
#include "linux/terminal_io_ansi_linux.hpp"
#include "monitor.hpp"
#include "additional_structs.hpp"

using namespace std;
using namespace blessings;

typedef SymbolUTF8 S;
typedef PropertyANSI P;
typedef TerminalIOANSILinux<S, S, queue<S>, queue<S>, P> TL;
typedef Monitor<S, S, P> M;
typedef M::Cell<S, P> Cell;

int main() {
  TL term;

  P yell(ColorANSI(3));

  term.Init();

  M monitor(1000);
  monitor.connect(&term);

  monitor.setResolution(50, 10);
  monitor.startWork();

  monitor.hardOptimization(true);

  monitor.tile(S("."), P::defaultProperty);
  monitor.draw(M::resChange::ignore);

  for (int i=0; i<(500-116); i++) {
    monitor(i/8+1, i%8+1) = Cell(S('#'), yell);
    monitor.lazyDraw(M::resChange::ignore);
    // monitor.draw(M::resChange::ignore);
    this_thread::sleep_for(chrono::milliseconds(3));
  }

  monitor.endWork();

  //FILE * in = fopen("logo.txt", "r");
  //int s;
  //char c;
  //bool ex=false;

  //const P p(ColorANSI(3));

  //monitor.tile(S("."), &p);
  //monitor.draw(M::resChange::ignore);

  //for (int t=0;t<300;t++) {
    //rewind(in);
    //s = 0;

    //while (s<500) {
      //for (int k=0;k<=t;k++) fscanf(in, "%c", &c);

      //for (int k=0;k<50;k++) {
        //if (c==*"\n") ex = true;
        //if (ex) break;

        ////if (c!=*".") {
        ////  const P p(ColorANSI(rand()%6+1));
        ////  monitor[s] = Cell(S(c), &p);
        ////} else {
        ////  const P p();
        ////  monitor[s] = Cell(S(c), &p);
        ////}

        //monitor[s] = Cell(S(c), &p);

        //fscanf(in, "%c", &c);
        //s++;
      //}

      //if (ex) break;

      //while (c !=*"\n") fscanf(in, "%c", &c);
    //}

    //if (ex) break;

    //monitor.lazyDraw(M::resChange::ignore);
    //this_thread::sleep_for(chrono::milliseconds(50));
  //}

  //fclose(in);

  return 0;
  
}
