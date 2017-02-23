#include <iostream>
#include <unistd.h>

#include "Symbol/SymbolUTF8.hpp"
#include "Symbol/Symbol.hpp"
#include "ANSILinux/TerminalIOANSILinux.hpp"

using namespace std;
using namespace blessings;

enum directionY {UP, DOWN};
enum directionX {LEFT, RIGHT};

void moveX(int* x, directionX* dX, int width) {
  if(*x==1 && *dX==LEFT) {
    *x=1;
    *dX=RIGHT;
  }
  else if(*x==width && *dX==RIGHT) {
    *x=width;
    *dX=LEFT;
  }
  else if(*dX==RIGHT) {
    ++(*x);
  }
  else {
    --(*x);
  }
}

void moveY(int* y, directionY* dY, int height) {
  if(*y==1 && *dY==UP) {
    *y=1;
    *dY=DOWN;
  }
  else if(*y==height && *dY==DOWN) {
    *y=height;
    *dY=UP;
  }
  else if(*dY==DOWN) {
    ++(*y);
  }
  else {
    --(*y);
  }
}

void laser() {
  std::cout << "Введите ширину экрана: ";
  flush(cout);
  int width;
  cin >> width;

  std::cout << "Введите высоту экрана: ";
  flush(cout);
  int height;
  cin >> height;

  TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI> term;

  term.Init();
  term.setDeviceReady();
  cout << term.isReady() << endl;

  term.clearScreen();

  term.moveCursorTo(1,1);
  term.print(SymbolUTF8("\\"));

  directionX nowDirX=RIGHT;
  directionY nowDirY=DOWN;
  int x=1;
  int y=1;

  while((x!=width || y!=height || nowDirX!=RIGHT || nowDirY!=DOWN) && (x!=1 || y!=height || nowDirX!=LEFT || nowDirY!=DOWN) && (x!=width || y!=1 || nowDirX!=RIGHT || nowDirY!=UP)) {
    usleep(5000);

    moveX(&x, &nowDirX, width);
    moveY(&y, &nowDirY, height);
    if(!((x!=width || y!=height || nowDirX!=RIGHT || nowDirY!=DOWN) && (x!=1 || y!=height || nowDirX!=LEFT || nowDirY!=DOWN) && (x!=width || y!=1 || nowDirX!=RIGHT || nowDirY!=UP))) break;
    moveX(&x, &nowDirX, width);
    moveY(&y, &nowDirY, height);

    term.moveCursorTo(x,y);
    if((nowDirX==RIGHT && nowDirY==DOWN) || (nowDirX==LEFT && nowDirY==UP)) {
      term.print(SymbolUTF8("\\"));
    }
    else {
      term.print(SymbolUTF8("/"));
    }
  }

  term.moveCursorTo(1,height+1);

  term.resetDeviceMode();
}
