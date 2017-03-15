#include <cstdio>
#include <string>
#include <chrono>
#include <thread>
#include <queue>

#include "symbol_utf8/symbol_utf8.hpp"
#include "property.hpp"
#include "linux/ANSI/terminal_io_ansi_linux.hpp"
#include "monitor.hpp"
#include "additional_structs.hpp"

using namespace std;
using namespace blessings;

typedef SymbolUTF8 S;
typedef PropertyANSI P;
typedef TerminalIOANSILinux<S, S, P> TL;
typedef Monitor M;

void test_dest00(M monitor) {
  P yell(ColorANSI(3));

  monitor.setResolution(50, 10);

  monitor.tile(S("."));
  monitor.draw(M::resChange::ignore);

  for (int i=0; i<(500-116); i++) {
    monitor(i/8+1, i%8+1) = M::Cell(S('#'), yell);
    monitor.lazyDraw(M::resChange::ignore);
    //monitor.draw(M::resChange::ignore);
    this_thread::sleep_for(chrono::milliseconds(3));
  }
}

void test_dest01(M monitor) {
	monitor.setResolution(50, 10);

  FILE * in = fopen("logo.txt", "r");
  int s;
  char c;
  bool ex=false;

  monitor.hardOptimization(true);

  monitor.tile(S(" "));
  monitor.draw(M::resChange::ignore);

  for (int t=0;t<300;t++) {
    rewind(in);
    s = 0;

    while (s<500) {
      for (int k=0;k<=t;k++) fscanf(in, "%c", &c);

      for (int k=0;k<50;k++) {
        if (c=='\n') ex = true;
        if (ex) break;

        if (c!='.') {
          P randcolor(ColorANSI(rand()%6+1));
          monitor[s] = M::Cell(S(c), randcolor);
        } else {
          monitor[s] = M::Cell(S(" "));
        }

        fscanf(in, "%c", &c);
        s++;
      }

      if (ex) break;

      while (c !=*"\n") fscanf(in, "%c", &c);
    }

    if (ex) break;

    monitor.lazyDraw(M::resChange::ignore);
    this_thread::sleep_for(chrono::milliseconds(50));
  }

  fclose(in);
}

void test_dest02(M monitor) {
	monitor.updateResolution();

	monitor.tile();

	for (int i=0;i<20;i++) {
		int x1 = rand()%monitor.resolution().width;
		int x2 = rand()%monitor.resolution().width;
		int y1 = rand()%monitor.resolution().height;
		int y2 = rand()%monitor.resolution().height;

		P col(ColorANSI(i%6+1));

		monitor.tile(S("@"), col, x1, y1, x2, y2);
		monitor.lazyDraw();
		this_thread::sleep_for(chrono::milliseconds(300));
	}
}

void test_melon00(M monitor) {
  monitor.setResolution(50, 10);

  monitor.hardOptimization(true);

  monitor.tile(S("."));
  monitor(0,0)=SymbolUTF8("a");
  monitor(0,1)=M::Cell(SymbolUTF8("a"), PropertyANSI::highlight);
  monitor(0,2)=SymbolUTF8("a");

  monitor.draw(M::resChange::ignore);

  this_thread::sleep_for(chrono::milliseconds(1000));
}


int main() {
	TL term;
	M monitor(50000);

	term.init();
	monitor.connect(&term);

	monitor.startWork();

	test_dest01(monitor);

	monitor.endWork();

  return 0;
}
