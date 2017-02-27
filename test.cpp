#include <iostream>
#include <string>
//#include <chrono>
//#include <thread>

#include "Symbol/SymbolUTF8.hpp"
#include "Symbol/Symbol.hpp"
#include "ANSILinux/TerminalIOANSILinux.hpp"
#include "Monitor.cpp"
#include "AdditionalStructs.hpp"

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
  //monitor.clearScreen();
  
  int t=0;
  
  for (int k=0;k++;k<5) {
		cout << k << endl;
		t++;
	}
  
  cout << t << endl;

  //for (int k=0;k++;k<4) {
	//	for (int s=0;s++;s<500) {
	//		c = fscanf(in, "%c");
	//		if (c != *"\n") {
	//			monitor[s] = Cell(S(c), &P::defaultProperty);
	//		}
	//	}
	//	monitor.draw(M::resChange::ignore);
	//	this_thread::sleep_for(chrono::milliseconds(500));
	//}
	
  return 0;
}
