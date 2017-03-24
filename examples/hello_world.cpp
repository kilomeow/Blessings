#include <string>
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
  
  monitor.setResolution(14, 5);
  monitor.initscr();
  
  std::string hello("Hello world!");
  int i = 0;
  
  for (std::string::iterator it=hello.begin(); it!=hello.end(); ++it) {
    ++i;
    monitor(i, 2) = *it;
    monitor.draw();
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
  }
  
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  
  monitor.endwin();
  
  return 0;
}
