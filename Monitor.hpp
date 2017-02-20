#pragma once

#include <utility>

#include "AdditionalStructs.hpp"
#include "TerminalIO.hpp"
#include "Symbol/Symbol.hpp"

namespace Blessings {
	template <class Symbol>
  struct MonitorCell {
  	Symbol symb;
  	Property* prop;
  };


  class MonitorGeneral {
	public:
		virtual void update()=0;
		virtual void clearScreen()=0;
    virtual void printPage()=0;

    virtual void moveCursor(int x, int y)=0;
    virtual GridPos getCursorPos()=0;

    virtual void hideCursor()=0;
    virtual void showCursor()=0;

    virtual void saveCursorPos()=0;
    virtual void restoreCursorPos()=0;

    virtual MonitorResolution getResolution()=0;

    virtual int boldSupported()=0;
    virtual int italicsSupported()=0;

    virtual PropertyType getPropertyType()=0;
  };


  template <class InputSymbol, class OutputSymbol>
  class Monitor : public MonitorGeneral {
  public:
    Monitor(TerminalIO Term, int MaxSize);

    Monitor(const Monitor&);
    Monitor& operator=(const Monitor&);
    ~Monitor();

    class Error;

		MonitorCell& operator[] (int p);
    MonitorCell operator[] (int p) const;
    MonitorCell& operator()(int x, int y);
    MonitorCell operator()(int x, int y) const;

    class Iterator {
		protected:
			int pointer;
			int stopPos;
		public:
    	Iterator(int pnt, int bnd)
			Iterator& operator++();
			Iterator operator++(int);
			MonitorCell& operator*();

			int currentIndex();
			GridPos currentPos();
    };

    Iterator begin();
    Iterator end();

    void update();
		void clearScreen();
    void printPage();

    InputSymbol getSym();

    void printSymbol(OutputSymbol);

    void moveCursor(int x, int y);
    GridPos getCursorPos();

    void hideCursor();
    void showCursor();

    void saveCursorPos();
    void restoreCursorPos();

    MonitorResolution getResolution();

    int boldSupported();         // Must be rewrited
    int italicsSupported();

    PropertyType getPropertyType();

	protected:
		MonitorCell * Monitor::grid;
		TerminalIO Monitor::termIO;
		int maxSize;
		MonitorResolution res;
		GlidPos cursorPos;
		GridPos cursorSlot;
  };

}
