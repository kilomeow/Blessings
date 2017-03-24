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
  
  monitor.updateResolution();
  monitor.initscr();
  
  for (int i=0;i<20;i++) {
    int x1 = rand()%monitor.resolution().width;
    int x2 = rand()%monitor.resolution().width;
    int y1 = rand()%monitor.resolution().height;
    int y2 = rand()%monitor.resolution().height;

    blessings::PropertyANSI col(blessings::ColorANSI(i%6+1));
    
    monitor.tile("@", col, x1, y1, x2, y2);
    monitor.draw();
    
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
  }
  
  monitor.endwin();
  
  return 0;
}
