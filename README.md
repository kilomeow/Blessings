# Blessings

Blessings is a C++ terminal control library (like curses), but made in a
object-oriented style. Blessings allows you write fast, nice terminal-
independed programs with text user interface. The name is a pun of name
of the other same library **curses**.

## Getting Started
### Linux
For a start, all you need is a C++ compiler, like gcc or clang. To run
stadnard installation, clone repisotory to your directory with:
```
git clone https://github.com/FourthRome/Blessings.git --depth=1
```
After this, enter your project directory and install blessings:
```
cd Blessings
./configure
make
sudo make install
```
To compile your program with blessings, use *gcc* (or any other gcc-like
compiler) with keys:
```
gcc your_project.cpp -lblessings -lblessings_utf8
```

## Some Examples
Blessings has nice, simple API. The shortest program looks like:
```
#include <blessings/terminal.hpp>
#include <blessings/monitor.hpp>

int main() {
  Terminal term;
  Monitor monitor;
  
  term.init();
  monitor.connect(&term);
  
  monitor.initscr();
  monitor.setResolution(9, 9);
  
  monitor.tile(".");
  monitor(4, 4) = "@";
  
  monitor.refresh();
  monitor.endwin();
  
  return 0;
}
```

## Contributing
If you want to contribute or just have some ideas, please write to [us](mailto:destabilizer@opmbx.org).

## Authors
This library created by MelonDev team:
  * Danya Ishakov - Main work and c++ chef - [KernelOps](https://github.com/KernelOps)
  * Balaram Usov - Monitor and other things - [destabilizer](https://github.com/destabilizer)
  * Roma Krivonogov - ReadStream and ideas - [FourthRome](https://github.com/FourthRome)

## License
This project is licensed under the MIT License - see the LICENSE file
for details.

