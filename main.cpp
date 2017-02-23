#include <iostream>
#include <unistd.h>
#include <string>

#include "Symbol/SymbolUTF8.hpp"
#include "Symbol/Symbol.hpp"
#include "ANSILinux/TerminalIOANSILinux.hpp"

#include <boost/filesystem.hpp>

using namespace std;
using namespace blessings;
using namespace boost::filesystem;

typedef TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI> TL;

struct Coord {
  int x;
  int y;

  Coord(int X=0, int Y=0) : x(X), y(Y) {};
};

bool operator==(const Coord& a, const Coord& b) {
  return a.x==b.x && a.y==b.y;
}

bool operator!=(const Coord& a, const Coord& b) {
  return a.x!=b.x || a.y!=b.y;
}

struct BoxmanLevel {
  vector<Coord> boxes;
  vector<Coord> goals;

  int xSize;
  int ySize;

  Coord startPos;

  class Error {};
  class InitError : public Error {};
  class ReadError : public Error {};
  class WriteError : public Error {};

  BoxmanLevel(string s) {
    try {
      cout << "Loading " << s << endl;

      std::ifstream fs(s);

      fs >> xSize;
      fs >> ySize;

      fs >> startPos.x;
      fs >> startPos.y;

      int objCount;
      fs >> objCount;

      if(objCount<=0) throw InitError();

      for(int i=0; i<objCount; ++i) {
        Coord c;
        fs >> c.x >> c.y;
        boxes.push_back(c);
      }

      for(int i=0; i<objCount; ++i) {
        Coord c;
        fs >> c.x >> c.y;
        goals.push_back(c);
      }
    }
    catch(InitError) {
      throw;
    }
    catch(...) {
      throw ReadError();
    }

    if(boxes.size()!=goals.size() || boxes.size()==0) throw InitError();

    if(startPos.x>=xSize || startPos.y>=ySize) throw InitError();

    if(xSize<=0 || ySize<=0) throw InitError();

    for(auto itB=boxes.begin(); itB!=boxes.end(); ++itB) {
      if(itB->x>=xSize || itB->y>=ySize) throw InitError();
      if(itB->x==startPos.x && itB->x==startPos.y) throw InitError();
    }

    for(auto itG=goals.begin(); itG!=goals.end(); ++itG) {
      if(itG->x>=xSize || itG->y>=ySize) throw InitError();
    }
  }

  BoxmanLevel(vector<Coord> Boxes, vector<Coord> Goals, int XSize, int YSize, Coord StartPos) :\
    boxes(Boxes), goals(Goals), xSize(XSize), ySize(YSize), startPos(StartPos) {
      if(boxes.size()!=goals.size() || boxes.size()==0) throw InitError();

      if(startPos.x>=xSize || startPos.y>=ySize) throw InitError();

      if(xSize<=0 || ySize<=0) throw InitError();

      for(auto itB=boxes.begin(); itB!=boxes.end(); ++itB) {
        if(itB->x>=xSize || itB->y>=ySize) throw InitError();
        if(itB->x==startPos.x && itB->x==startPos.y) throw InitError();
      }

      for(auto itG=goals.begin(); itG!=goals.end(); ++itG) {
        if(itG->x>=xSize || itG->y>=ySize) throw InitError();
      }
  }

  void save(string s) {
    try {
      std::ofstream fs(s);

      fs << xSize << ' ' << ySize << endl << endl;

      fs << startPos.x << ' ' << startPos.y << endl << endl;

      fs << boxes.size() << endl << endl;

      for(int i=0; i<boxes.size(); ++i) {
        fs << boxes[i].x << ' ' << boxes[i].y << endl;
      }

      fs << endl;

      for(int i=0; i<goals.size(); ++i) {
        fs << goals[i].x << ' ' << goals[i].y << endl;
      }
    }
    catch(...) {
      throw WriteError();
    }
  }
};

class EditorRoom {
  BoxmanLevel level;

  Coord pos;
public:
  class Error {};
  class InitError : public Error {};
  class BadLevel : public Error {};

  EditorRoom(int xSize, int ySize) : level(vector<Coord>(1,Coord(1,1)), vector<Coord>(1,Coord(1,2)), xSize, ySize, Coord(0,0)){
    if(level.xSize<=0 || level.ySize<=0) throw InitError();
  }

  void moveLeft() {
    if(pos.x==0) return;
    else --pos.x;
  }

  void moveRight() {
    if(pos.x==level.xSize-1) return;
    else ++pos.x;
  }

  void moveUp() {
    if(pos.y==0) return;
    else --pos.y;
  }

  void moveDown() {
    if(pos.y==level.ySize-1) return;
    else ++pos.y;
  }

  void print(TL* term) {
    term->clearScreen();
    term->hideCursor();

    for(int x=0; x<=level.xSize; ++x) {
      term->moveCursorTo(x+1, level.ySize+1);
      term->print(SymbolUTF8("*"));
    }
    for(int y=0; y<=level.ySize; ++y) {
      term->moveCursorTo(level.xSize+1, y+1);
      term->print(SymbolUTF8("*"));
    }

    for(auto itG=level.goals.begin(); itG!=level.goals.end(); ++itG) {
      term->moveCursorTo(itG->x+1, itG->y+1);
      term->print(SymbolUTF8("!"));
    }

    term->moveCursorTo(level.startPos.x+1, level.startPos.y+1);
    term->print(SymbolUTF8("$"));

    for(auto itB=level.boxes.begin(); itB!=level.boxes.end(); ++itB) {
      term->moveCursorTo(itB->x+1, itB->y+1);
      term->print(SymbolUTF8("#"));
    }

    term->moveCursorTo(pos.x+1, pos.y+1);
    term->print(SymbolUTF8("@"));
  }

  void editBox() {
    bool exists=false;
    auto it=level.boxes.begin();
    for(; it!=level.boxes.end(); ++it) {
      if(*it==pos) {
        exists=true;
        break;
      }
    }

    if(exists) {
      level.boxes.erase(it);
    }
    else {
      level.boxes.push_back(pos);
    }
  }

  void editGoal() {
    bool exists=false;
    auto it=level.goals.begin();
    for(; it!=level.goals.end(); ++it) {
      if(*it==pos) {
        exists=true;
        break;
      }
    }

    if(exists) {
      level.goals.erase(it);
    }
    else {
      level.goals.push_back(pos);
    }
  }

  void setStartPos() {
    level.startPos=pos;
  }

  bool checkLevel() {
    if(level.boxes.size()!=level.goals.size() || level.boxes.size()==0) return false;

    for(auto itB=level.boxes.begin(); itB!=level.boxes.end(); ++itB) {
      if(itB->x==level.startPos.x && itB->x==level.startPos.y) return false;
    }

    return true;
  }

  BoxmanLevel getLevel() {
    if(!checkLevel()) throw BadLevel();

    return level;
  }
};

class Room {
  vector<Coord> boxes;
  vector<Coord> goals;

  int xSize;
  int ySize;

  Coord pos;
public:
  Room(BoxmanLevel level) : boxes(level.boxes), goals(level.goals),\
    xSize(level.xSize), ySize(level.ySize), pos(level.startPos) {};

  void moveLeft() {
    if(pos.x==0) return;

    bool boxFound=false;
    int boxNum;
    for(int i=0; i<boxes.size(); ++i) {
      if(boxes[i].x==pos.x-1 && boxes[i].y==pos.y) {
        boxFound=true;
        boxNum=i;
        break;
      }
    }

    if(!boxFound) {
      --pos.x;
      return;
    }
    else {
      if(pos.x==1) return;

      boxFound=false;
      for(int i=0; i<boxes.size(); ++i) {
        if(boxes[i].x==pos.x-2 && boxes[i].y==pos.y) {
          boxFound=true;
          boxNum=i;
          break;
        }
      }

      if(boxFound==true) return;
      else {
        --boxes[boxNum].x;
        --pos.x;
      }
    }
  }

  void moveRight() {
    if(pos.x==xSize-1) return;

    bool boxFound=false;
    int boxNum;
    for(int i=0; i<boxes.size(); ++i) {
      if(boxes[i].x==pos.x+1 && boxes[i].y==pos.y) {
        boxFound=true;
        boxNum=i;
        break;
      }
    }

    if(!boxFound) {
      ++pos.x;
      return;
    }
    else {
      if(pos.x==xSize-2) return;

      boxFound=false;
      for(int i=0; i<boxes.size(); ++i) {
        if(boxes[i].x==pos.x+2 && boxes[i].y==pos.y) {
          boxFound=true;
          boxNum=i;
          break;
        }
      }

      if(boxFound==true) return;
      else {
        ++boxes[boxNum].x;
        ++pos.x;
      }
    }
  }

  void moveDown() {
    if(pos.y==ySize-1) return;

    bool boxFound=false;
    int boxNum;
    for(int i=0; i<boxes.size(); ++i) {
      if(boxes[i].y==pos.y+1 && boxes[i].x==pos.x) {
        boxFound=true;
        boxNum=i;
        break;
      }
    }

    if(!boxFound) {
      ++pos.y;
      return;
    }
    else {
      if(pos.y==ySize-2) return;

      boxFound=false;
      for(int i=0; i<boxes.size(); ++i) {
        if(boxes[i].y==pos.y+2 && boxes[i].x==pos.x) {
          boxFound=true;
          boxNum=i;
          break;
        }
      }

      if(boxFound==true) return;
      else {
        ++boxes[boxNum].y;
        ++pos.y;
      }
    }
  }

  void moveUp() {
    if(pos.y==0) return;

    bool boxFound=false;
    int boxNum;
    for(int i=0; i<boxes.size(); ++i) {
      if(boxes[i].y==pos.y-1 && boxes[i].x==pos.x) {
        boxFound=true;
        boxNum=i;
        break;
      }
    }

    if(!boxFound) {
      --pos.y;
      return;
    }
    else {
      if(pos.y==1) return;

      boxFound=false;
      for(int i=0; i<boxes.size(); ++i) {
        if(boxes[i].y==pos.y-2 && boxes[i].x==pos.x) {
          boxFound=true;
          boxNum=i;
          break;
        }
      }

      if(boxFound==true) return;
      else {
        --boxes[boxNum].y;
        --pos.y;
      }
    }
  }

  bool checkWin() {
    bool ret=true;

    for(auto itB=boxes.begin(); itB!=boxes.end(); ++itB) {
      bool found=false;
      for(auto itG=goals.begin(); itG!=goals.end(); ++itG) {
        if(*itB==*itG) {
          found=true;
          break;
        }
      }

      if(!found) {
        ret=false;
        break;
      }
    }

    return ret;
  }

  void print(TL* term) {
    term->clearScreen();
    term->hideCursor();

    for(int x=0; x<=xSize; ++x) {
      term->moveCursorTo(x+1, ySize+1);
      term->print(SymbolUTF8("*"));
    }
    for(int y=0; y<=ySize; ++y) {
      term->moveCursorTo(xSize+1, y+1);
      term->print(SymbolUTF8("*"));
    }

    for(auto itG=goals.begin(); itG!=goals.end(); ++itG) {
      term->moveCursorTo(itG->x+1, itG->y+1);
      term->print(SymbolUTF8("!"));
    }

    for(auto itB=boxes.begin(); itB!=boxes.end(); ++itB) {
      term->moveCursorTo(itB->x+1, itB->y+1);
      term->print(SymbolUTF8("#"));
    }

    term->moveCursorTo(pos.x+1, pos.y+1);
    term->print(SymbolUTF8("@"));
  }
};

class BoxmanGame {
  string levelsFolder;
  vector<BoxmanLevel> levels;
public:
  class Error {};
  class TerminalIsNotReadyError : public Error {};
  class BadPathError : public Error {};
  class LevelLoadError : public Error {};

  BoxmanGame(string LevelsFolder) : levelsFolder(LevelsFolder) {
    path levelsFolderPath(levelsFolder.c_str());

    if(!exists(levelsFolderPath)) throw BadPathError();
    if(!is_directory(levelsFolderPath)) throw BadPathError();

    if(levelsFolder[levelsFolder.size()-1]!='/') levelsFolder+='/';
  }

  void launchEditor(TL* term) {
    if(!term->isReady()) throw TerminalIsNotReadyError();

    int xSize=1;
    int ySize=1;

    term->clearScreen();
    term->moveCursorTo(1,1);

    cout << "Choose x size:" << endl;

    term->moveCursorTo(1,2);
    term->print(SymbolUTF8("1"));

    for(;;) {
      auto s=term->getSymbol();

      if(s.size()==1) {
        if(s[0].getString()=="a") {
          if(xSize==1) continue;
          else {
            string s=to_string(xSize);
            for(int i=1; i<=s.size(); ++i) {
              term->moveCursorTo(i,2);
              term->print(SymbolUTF8(" "));
            }

            --xSize;
            s=to_string(xSize);
            for(int i=1; i<=s.size(); ++i) {
              term->moveCursorTo(i,2);
              term->print(SymbolUTF8(string(1, s[i-1])));
            }
          }
        }
        else if(s[0].getString()=="d") {
          ++xSize;
          string s=to_string(xSize);
          for(int i=1; i<=s.size(); ++i) {
            term->moveCursorTo(i,2);
            term->print(SymbolUTF8(string(1, s[i-1])));
          }
        }
        else if(s[0].getString()=="\n") break;
      }

      usleep(10000);
    }

    term->clearScreen();
    term->moveCursorTo(1,1);

    cout << "Choose y size:" << endl;


    term->moveCursorTo(1,2);
    term->print(SymbolUTF8("1"));

    for(;;) {
      auto s=term->getSymbol();

      if(s.size()==1) {
        if(s[0].getString()=="a") {
          if(ySize==1) continue;
          else {
            string s=to_string(ySize);
            for(int i=1; i<=s.size(); ++i) {
              term->moveCursorTo(i,2);
              term->print(SymbolUTF8(" "));
            }

            --ySize;
            s=to_string(ySize);
            for(int i=1; i<=s.size(); ++i) {
              term->moveCursorTo(i,2);
              term->print(SymbolUTF8(string(1, s[i-1])));
            }
          }
        }
        else if(s[0].getString()=="d") {
          ++ySize;
          string s=to_string(ySize);
          for(int i=1; i<=s.size(); ++i) {
            term->moveCursorTo(i,2);
            term->print(SymbolUTF8(string(1, s[i-1])));
          }
        }
        else if(s[0].getString()=="\n") break;
      }

      usleep(10000);
    }

    EditorRoom room(xSize, ySize);
    room.print(term);

    term->moveCursorTo(1, ySize+3);
    cout << "b to set box" << endl;
    cout << "g to set goal" << endl;
    cout << "h to set start pos" << endl;
    cout << "p to save; save file is \"1\". Move it to levels folder to play" << endl;
    cout << "q to quit main menu" << endl;

    for(;;) {
      auto s=term->getSymbol();

      if(s.size()==1) {
        if(s[0].getString()=="w") {
          room.moveUp();
          room.print(term);
          term->moveCursorTo(1, ySize+3);
          cout << "b to set box" << endl;
          cout << "g to set goal" << endl;
          cout << "h to set start pos" << endl;
          cout << "p to save; save file is \"1\". Move it to levels folder to play" << endl;
          cout << "q to quit main menu" << endl;
        }
        else if(s[0].getString()=="a") {
          room.moveLeft();
          room.print(term);
          term->moveCursorTo(1, ySize+3);
          cout << "b to set box" << endl;
          cout << "g to set goal" << endl;
          cout << "h to set start pos" << endl;
          cout << "p to save; save file is \"1\". Move it to levels folder to play" << endl;
          cout << "q to quit main menu" << endl;
        }
        else if(s[0].getString()=="s") {
          room.moveDown();
          room.print(term);
          term->moveCursorTo(1, ySize+3);
          cout << "b to set box" << endl;
          cout << "g to set goal" << endl;
          cout << "h to set start pos" << endl;
          cout << "p to save; save file is \"1\". Move it to levels folder to play" << endl;
          cout << "q to quit main menu" << endl;
        }
        else if(s[0].getString()=="d") {
          room.moveRight();
          room.print(term);
          term->moveCursorTo(1, ySize+3);
          cout << "b to set box" << endl;
          cout << "g to set goal" << endl;
          cout << "h to set start pos" << endl;
          cout << "p to save; save file is \"1\". Move it to levels folder to play" << endl;
          cout << "q to quit main menu" << endl;
        }
        else if(s[0].getString()=="b") {
          room.editBox();
          room.print(term);
          term->moveCursorTo(1, ySize+3);
          cout << "b to set box" << endl;
          cout << "g to set goal" << endl;
          cout << "h to set start pos" << endl;
          cout << "p to save; save file is \"1\". Move it to levels folder to play" << endl;
          cout << "q to quit main menu" << endl;
        }
        else if(s[0].getString()=="g") {
          room.editGoal();
          room.print(term);
          term->moveCursorTo(1, ySize+3);
          cout << "b to set box" << endl;
          cout << "g to set goal" << endl;
          cout << "h to set start pos" << endl;
          cout << "p to save; save file is \"1\". Move it to levels folder to play" << endl;
          cout << "q to quit main menu" << endl;
        }
        else if(s[0].getString()=="g") {
          room.editGoal();
          room.print(term);
          term->moveCursorTo(1, ySize+3);
          cout << "b to set box" << endl;
          cout << "g to set goal" << endl;
          cout << "h to set start pos" << endl;
          cout << "p to save; save file is \"1\". Move it to levels folder to play" << endl;
          cout << "q to quit main menu" << endl;
        }
        else if(s[0].getString()=="h") {
          room.setStartPos();
          room.print(term);
          term->moveCursorTo(1, ySize+3);
          cout << "b to set box" << endl;
          cout << "g to set goal" << endl;
          cout << "h to set start pos" << endl;
          cout << "p to save; save file is \"1\". Move it to levels folder to play" << endl;
          cout << "q to quit main menu" << endl;
        }
        else if(s[0].getString()=="p") {
          if(room.checkLevel()) {
            BoxmanLevel level=room.getLevel();
            level.save("1");
            term->moveCursorTo(1, ySize+10);
            cout << "Saved" << endl;
          }
          else {
            term->moveCursorTo(1, ySize+10);
            cout << "Bad level, change it to save" << endl;
          }
        }
        else if(s[0].getString()=="q") {
          break;
        }
      }

      usleep(10000);
    }
  }

  void loadLevels() {
    levels.clear();

    path p(levelsFolder.c_str());

    if(!exists(p)) throw BadPathError();
    if(!is_directory(p)) throw BadPathError();

    int levelNum=1;
    try {
      while(exists(path((levelsFolder+to_string(levelNum)).c_str()))) {
        if(!is_regular_file(path((levelsFolder+to_string(levelNum)).c_str()))) break;

        levels.push_back(BoxmanLevel(levelsFolder+to_string(levelNum)));
        ++levelNum;
      }
    }
    catch(...) {
      throw LevelLoadError();
    }
  }

  void launchLevel(TL* term, BoxmanLevel level) {
    if(!term->isReady()) throw TerminalIsNotReadyError();

    Room room(level);
    room.print(term);

    for(;;) {
      auto s=term->getSymbol();

      if(s.size()==1) {
        if(s[0].getString()=="w") {
          room.moveUp();
          room.print(term);
        }
        else if(s[0].getString()=="a") {
          room.moveLeft();
          room.print(term);
        }
        else if(s[0].getString()=="s") {
          room.moveDown();
          room.print(term);
        }
        else if(s[0].getString()=="d") {
          room.moveRight();
          room.print(term);
        }
      }

      if(room.checkWin()) {
        break;
      }

      usleep(10000);
    }

    term->moveCursorTo(1, level.ySize+3);
    term->showCursor();

    string complete="Complete!\n";
    for(int i=0; i<complete.size(); ++i) {
      term->print(SymbolUTF8(string(1, complete[i])));
    }
  }

  void launchMainMenu(TL* term) {
    if(!term->isReady()) throw TerminalIsNotReadyError();

    term->hideCursor();

    for(;;) {
      term->clearScreen();
      term->moveCursorTo(1,1);

      cout << "l to load levels list, e to launch editor, q to quit" << endl;
      if(levels.size()==0) cout << "There is no levels loaded now" << endl;
      else cout << "AD to choose level, ENTER to start" << endl;

      if(!levels.size()) {
        for(;;) {
          auto s=term->getSymbol();

          if(s.size()!=0) {
            if(s[0].getString()=="l") {
              loadLevels();
              break;
            }
            else if(s[0].getString()=="q") {
              return;
            }
            else if(s[0].getString()=="e") {
              launchEditor(term);
              break;
            }
          }

          usleep(2000);
        }
      }
      else {
        term->moveCursorTo(1,3);
        term->print(SymbolUTF8("1"));
        int choosenLevel=1;

        for(;;) {
          auto s=term->getSymbol();

          if(s.size()!=0) {
            if(s[0].getString()=="a") {
              string s=to_string(choosenLevel);
              for(int i=1; i<=s.size(); ++i) {
                term->moveCursorTo(i,3);
                term->print(SymbolUTF8(" "));
              }

              if(choosenLevel==1) choosenLevel=levels.size();
              else --choosenLevel;
              s=to_string(choosenLevel);

              for(int i=0; i<s.size(); ++i) {
                term->moveCursorTo(i+1, 3);
                term->print(SymbolUTF8(string(1,s[i])));
              }
            }
            else if(s[0].getString()=="d") {
              string s=to_string(choosenLevel);
              for(int i=1; i<=s.size(); ++i) {
                term->moveCursorTo(i,3);
                term->print(SymbolUTF8(" "));
              }

              if(choosenLevel==levels.size()) choosenLevel=1;
              else ++choosenLevel;
              s=to_string(choosenLevel);

              for(int i=0; i<s.size(); ++i) {
                term->moveCursorTo(i+1, 3);
                term->print(SymbolUTF8(string(1,s[i])));
              }
            }
            else if(s[0].getString()=="\n") {
              launchLevel(term, levels[choosenLevel-1]);
              break;
            }
            else if(s[0].getString()=="q") {
              return;
            }
            else if(s[0].getString()=="e") {
              launchEditor(term);
              break;
            }
          }

          usleep(2000);
        }
      }
    }
  }
};



int main() {
  TL term;

  term.Init();
  term.setDeviceReady();

  BoxmanGame game("levels");
  game.launchMainMenu(&term);

  term.showCursor();
  term.resetDeviceMode();

  return 0;
}
