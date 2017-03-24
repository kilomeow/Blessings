#include <cstdio>
#include <chrono>
#include <thread>

//#include <blessings/monitor.hpp>
//#include <blessings/terminal.hpp>
#include "../monitor.hpp"
#include "../terminal.hpp"

int main() {
  blessings::Terminal term;
  blessings::Monitor monitor;
  
  term.init();
  monitor.connect(&term);
  
  monitor.setResolution(50, 10);
  monitor.initscr();

  FILE * in = std::fopen("resource/logo.txt", "r");
  int s;
  char c;
  bool ex=false;

  for (int t=0;t<300;t++) {
    rewind(in);
    s = 0;

    while (s<500) {
      for (int k=0;k<=t;k++) fscanf(in, "%c", &c);

      for (int k=0;k<50;k++) {
        if (c=='\n') ex = true;
        if (ex) break;

        if (c!='.') {
          blessings::SymbolUTF8 symb(c);
          blessings::PropertyANSI randcolor(blessings::ColorANSI(rand()%6+1));
          monitor[s] = blessings::Monitor::Cell(symb, randcolor);
        } else {
          monitor[s] = " ";
        }

        fscanf(in, "%c", &c);
        s++;
      }

      if (ex) break;

      while (c !=*"\n") fscanf(in, "%c", &c);
    }

    if (ex) break;

    monitor.draw();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }

  fclose(in);
  
  monitor.endwin();
  
  return 0;
}
