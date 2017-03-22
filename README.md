# Blessings
Blessings is a C++ terminal management library (like curses) written in an
object-oriented style. Blessings allows you to write fast nice
terminal-independent programs with text user interface. The name is a pun
on the name of the other terminal library **curses**.

## Getting Started
### Linux
You'll need **gcc** *(or any other gcc-like compiler)* and
**python3** to start with. To install the library, clone the repository to your
working directory with:
```
% git clone https://github.com/FourthRome/Blessings.git --depth=1
```

Then enter your project directory and install blessings:
```
% cd Blessings
% ./configure
% make
% sudo make install
```

To build your program with blessings, run:
```
% gcc your_project.cpp -lblessings -lblessings_utf8
```

## Examples
Blessings API is simple and nice. Just look at this short example:
```
#include <blessings/terminal.hpp>
#include <blessings/monitor.hpp>

int main() {
  blessings::Terminal term;
  blessings::Monitor monitor;
  
  term.init();
  monitor.connect(&term);
  monitor.setResolution(9, 9);
  monitor.initscr();
  
  monitor.tile(".");
  monitor(4, 4) = "@";
  
  monitor.refresh();
  monitor.endwin();
  
  return 0;
}
```

## Contributing
If you want to contribute or just have some ideas, please
[write to us](mailto:destabilizer@opmbx.org).

## Authors
This library created by MelonDev team:
  * [Danya Ishakov](https://github.com/KernelOps) — The lead developer
  * [Ram Usov](https://github.com/destabilizer) — API usurper
  * [Roma Krivonogov](https://github.com/FourthRome) — The inspirer

## License
This project is licensed under the MIT License - see LICENSE for details.

