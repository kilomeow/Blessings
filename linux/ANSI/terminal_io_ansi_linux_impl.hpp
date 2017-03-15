#include <cstdio>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/select.h>

#include "terminal_io_ansi_linux.hpp"
#include "ansi_symbol_table.hpp"
#include "../../additional_structs.hpp"

namespace blessings {
  template<typename InS, typename OutS, typename Property>
  TerminalIOANSILinux<InS, OutS, Property>::TerminalIOANSILinux() :
    inited(false) {};

  template<typename InS, typename OutS, typename Property>
  TerminalIOANSILinux<InS, OutS, Property>::~TerminalIOANSILinux() {
    if (inited) {
      setEchoInhibition();
      resetSGR();
      showCursor();
      resetDeviceMode();
    }
  }

  template<typename InS, typename OutS, typename Property>
  void TerminalIOANSILinux<InS, OutS, Property>::init(std::string path) {
    if (inited) throw ReInitAttempt();

    if (path=="") fd=open(ttyname(1), O_RDWR|O_APPEND);
    else fd=open(path.c_str(), O_RDWR|O_APPEND);

    if (fd==-1) throw InitError();

    file=fdopen(fd, "rw+");
    if (file==nullptr) {
      close(fd);
      throw InitError();
    }

    int temp=tcgetattr(fd,&storedSettings);
    if (temp!=0) {
      fclose(file);
      throw InitError();
    }

    termios tempSettings=storedSettings;
    tempSettings.c_lflag &=~ECHO;
    tcsetattr(fd,TCSANOW,&tempSettings); //Pray it works

    try {
      ANSISymbolTable<OutS>::ESCSymbol.writeToFile(file);
      ANSISymbolTable<OutS>::openBracket.writeToFile(file);
      ANSISymbolTable<OutS>::zero.writeToFile(file);
      ANSISymbolTable<OutS>::mSym.writeToFile(file);

      int resCode=fflush(file);
      if (resCode==EOF) {
        throw IOError();
      }
    }
    catch(...) {
      tcsetattr(fd,TCSANOW,&storedSettings);
      fclose(file);
      throw InitError();
    }

    tcsetattr(fd,TCSANOW,&storedSettings); //Pray it works

    inited=true;
    echoInhibited=0;
    nonCanonicalMode=0;

    currentProperty=Property::empty;
  }

  template<typename InS, typename OutS, typename Property>
  void TerminalIOANSILinux<InS, OutS, Property>::disconnect() {
    if(!inited) throw BadMode();

    resetSGR();

    inited=false;
  }

  template<typename InS, typename OutS, typename Property>
  void TerminalIOANSILinux<InS, OutS, Property>::print(\
    OutS sym, const Property& prop) {
    if (!inited) throw BadMode();

    try {
      setSGR(prop);

      sym.writeToFile(file);

      int resCode=fflush(file);
      if (resCode==EOF) {
        throw IOError();
      }
    }
    catch (...) {
      throw IOError();
    }
  }

  template<typename InS, typename OutS, typename Property>
  void TerminalIOANSILinux<InS, OutS, Property>::print(OutS sym) {
    if (!inited) throw BadMode();

    try {
      setSGR(Property::empty);

      sym.writeToFile(file);

      int resCode=fflush(file);
      if (resCode==EOF) {
        throw IOError();
      }
    }
    catch (...) {
      throw IOError();
    }
  }

  template<typename InS, typename OutS, typename Property>
  void TerminalIOANSILinux<InS, OutS, Property>::clearScreen() {
    if (!inited) throw BadMode();

    try {
      ANSISymbolTable<OutS>::ESCSymbol.writeToFile(file);
      ANSISymbolTable<OutS>::openBracket.writeToFile(file);
      ANSISymbolTable<OutS>::two.writeToFile(file);
      ANSISymbolTable<OutS>::JSym.writeToFile(file);

      int resCode=fflush(file);
      if (resCode==EOF) {
        throw IOError();
      }
    }
    catch (...) {
      throw IOError();
    }
  }

  template<typename InS, typename OutS, typename Property>
  void TerminalIOANSILinux<InS, OutS, Property>::newLine() {
    if (!inited) throw BadMode();

    try {
      ANSISymbolTable<OutS>::newLineSymbol.writeToFile(file);

      int resCode=fflush(file);
      if (resCode==EOF) {
        throw IOError();
      }
    }
    catch (...) {
      throw IOError();
    }
  }

  template<typename InS, typename OutS, typename Property>
  void TerminalIOANSILinux<InS, OutS, Property>::moveCursor(int x, int y) {
    if (!inited) throw BadMode();

    try {
      if (x==0 && y==0) return;

      int xAbs=x<0 ? -x : x;
      int yAbs=y<0 ? -y : y;

      std::string xAbsStr=std::to_string(xAbs);
      std::string yAbsStr=std::to_string(yAbs);

      if (x!=0) {
        ANSISymbolTable<OutS>::ESCSymbol.writeToFile(file);
        ANSISymbolTable<OutS>::openBracket.writeToFile(file);

        for(size_t i=0; i<xAbsStr.size(); ++i) {
          int resCode=fputc(xAbsStr[i], file);
          if (resCode==EOF) {
            throw IOError();
          }
        }

        if (x<0) ANSISymbolTable<OutS>::DSym.writeToFile(file);
        else ANSISymbolTable<OutS>::CSym.writeToFile(file);
      }

      if (y!=0) {
        ANSISymbolTable<OutS>::ESCSymbol.writeToFile(file);
        ANSISymbolTable<OutS>::openBracket.writeToFile(file);

        for(size_t i=0; i<yAbsStr.size(); ++i) {
          int resCode=fputc(yAbsStr[i], file);
          if (resCode==EOF) {
            throw IOError();
          }
        }

        if (y>0) ANSISymbolTable<OutS>::ASym.writeToFile(file);
        else ANSISymbolTable<OutS>::BSym.writeToFile(file);
      }

      int resCode=fflush(file);
      if (resCode==EOF) {
        throw IOError();
      }
    }
    catch (...) {
      throw IOError();
    }
  }

  template<typename InS, typename OutS, typename Property>
  void TerminalIOANSILinux<InS, OutS, Property>::moveCursorTo(int x, int y) {
    if (!inited) throw BadMode();

    if (x<=0 || y<=0) throw ArgumentError();

    try {
      std::string xStr=std::to_string(x);
      std::string yStr=std::to_string(y);

      ANSISymbolTable<OutS>::ESCSymbol.writeToFile(file);
      ANSISymbolTable<OutS>::openBracket.writeToFile(file);

      for(size_t i=0; i<yStr.size(); ++i) {
        int resCode=fputc(yStr[i], file);
        if (resCode==EOF) {
          throw IOError();
        }
      }

      ANSISymbolTable<OutS>::semicolon.writeToFile(file);

      for(size_t i=0; i<xStr.size(); ++i) {
        int resCode=fputc(xStr[i], file);
        if (resCode==EOF) {
          throw IOError();
        }
      }

      ANSISymbolTable<OutS>::HSym.writeToFile(file);

      int resCode=fflush(file);
      if (resCode==EOF) {
        throw IOError();
      }
    }
    catch (...) {
      throw IOError();
    }
  }

  template<typename InS, typename OutS, typename Property>
  void TerminalIOANSILinux<InS, OutS, Property>::resetSGR() {
    if (!inited) throw BadMode();

    try {
      ANSISymbolTable<OutS>::ESCSymbol.writeToFile(file);
      ANSISymbolTable<OutS>::openBracket.writeToFile(file);
      ANSISymbolTable<OutS>::zero.writeToFile(file);
      ANSISymbolTable<OutS>::mSym.writeToFile(file);

      int resCode=fflush(file);
      if (resCode==EOF) {
        throw IOError();
      }
    }
    catch (...) {
      throw IOError();
    }
  }

  template<typename InS, typename OutS, typename Property>
  void TerminalIOANSILinux<InS, OutS, Property>::hideCursor() {
    if (!inited) throw BadMode();

    try {
      ANSISymbolTable<OutS>::ESCSymbol.writeToFile(file);
      ANSISymbolTable<OutS>::openBracket.writeToFile(file);
      ANSISymbolTable<OutS>::question.writeToFile(file);
      ANSISymbolTable<OutS>::two.writeToFile(file);
      ANSISymbolTable<OutS>::five.writeToFile(file);
      ANSISymbolTable<OutS>::lSym.writeToFile(file);

      int resCode=fflush(file);
      if (resCode==EOF) {
        throw IOError();
      }
    }
    catch (...) {
      throw IOError();
    }
  }

  template<typename InS, typename OutS, typename Property>
  void TerminalIOANSILinux<InS, OutS, Property>::showCursor() {
    if (!inited) throw BadMode();

    try {
      ANSISymbolTable<OutS>::ESCSymbol.writeToFile(file);
      ANSISymbolTable<OutS>::openBracket.writeToFile(file);
      ANSISymbolTable<OutS>::question.writeToFile(file);
      ANSISymbolTable<OutS>::two.writeToFile(file);
      ANSISymbolTable<OutS>::five.writeToFile(file);
      ANSISymbolTable<OutS>::hSym.writeToFile(file);

      int resCode=fflush(file);
      if (resCode==EOF) {
        throw IOError();
      }
    }
    catch (...) {
      throw IOError();
    }
  }

  template<typename InS, typename OutS, typename Property>
  void TerminalIOANSILinux<InS, OutS, Property>::saveCursorPos() {
    if (!inited) throw BadMode();

    try {
      ANSISymbolTable<OutS>::ESCSymbol.writeToFile(file);
      ANSISymbolTable<OutS>::openBracket.writeToFile(file);
      ANSISymbolTable<OutS>::sSym.writeToFile(file);

      int resCode=fflush(file);
      if (resCode==EOF) {
        throw IOError();
      }
    }
    catch (...) {
      throw IOError();
    }
  }

  template<typename InS, typename OutS, typename Property>
  void TerminalIOANSILinux<InS, OutS, Property>::restoreCursorPos() {
    if (!inited) throw BadMode();

    try {
      ANSISymbolTable<OutS>::ESCSymbol.writeToFile(file);
      ANSISymbolTable<OutS>::openBracket.writeToFile(file);
      ANSISymbolTable<OutS>::uSym.writeToFile(file);

      int resCode=fflush(file);
      if (resCode==EOF) {
        throw IOError();
      }
    }
    catch (...) {
      throw IOError();
    }
  }

  template<typename InS, typename OutS, typename Property>
  void TerminalIOANSILinux<InS, OutS, Property>::setNonCanonicalMode() {
    if (!inited) throw BadMode();

    if (nonCanonicalMode==1) return;

    termios currSettings;

    int temp=tcgetattr(fd,&currSettings);
    if (temp!=0) throw DeviceError();

    currSettings.c_lflag &=~ICANON;
    currSettings.c_cc[VTIME] = 0;
    currSettings.c_cc[VMIN] = 0;

    tcsetattr(fd,TCSANOW,&currSettings); //Pray it works

    nonCanonicalMode = 1;
  }

  template<typename InS, typename OutS, typename Property>
  void TerminalIOANSILinux<InS, OutS, Property>::setCanonicalMode() {
    if (!inited) throw BadMode();

    if (nonCanonicalMode==-1) return;

    termios currSettings;

    int temp=tcgetattr(fd,&currSettings);
    if (temp!=0) throw DeviceError();

    currSettings.c_lflag |=ICANON;

    tcsetattr(fd,TCSANOW,&currSettings); //Pray it works

    nonCanonicalMode = -1;
  }

  template<typename InS, typename OutS, typename Property>
  void TerminalIOANSILinux<InS, OutS, Property>::setEchoInhibition() {
    if (!inited) throw BadMode();

    if (echoInhibited==1) return;

    termios currSettings;

    int temp=tcgetattr(fd,&currSettings);
    if (temp!=0) throw DeviceError();

    currSettings.c_lflag &=~ECHO;

    tcsetattr(fd,TCSANOW,&currSettings); //Pray it works

    echoInhibited = 1;
  }

  template<typename InS, typename OutS, typename Property>
  void TerminalIOANSILinux<InS, OutS, Property>::setEchoForward() {
    if (!inited) throw BadMode();

    if (echoInhibited==-1) return;

    termios currSettings;

    int temp=tcgetattr(fd,&currSettings);
    if (temp!=0) throw DeviceError();

    currSettings.c_lflag |=ECHO;

    tcsetattr(fd,TCSANOW,&currSettings); //Pray it works

    echoInhibited = -1;
  }

  template<typename InS, typename OutS, typename Property>
  void TerminalIOANSILinux<InS, OutS, Property>::resetDeviceMode() {
    if (!inited) throw BadMode();

    tcsetattr(fd,TCSANOW,&storedSettings); //Pray it works

    nonCanonicalMode = 0;
    echoInhibited = 0;
  }

  template<typename InS, typename OutS, typename Property>
  Resolution TerminalIOANSILinux<InS, OutS, Property>::getResolution() {
    if (!inited) throw BadMode();

    winsize ws;
    int temp=ioctl(fd, TIOCGWINSZ, &ws);
    if (temp==-1) throw DeviceError();

    return Resolution(ws.ws_col, ws.ws_row);
  }

  template<typename InS, typename OutS, typename Property>
  void TerminalIOANSILinux<InS, OutS, Property>::clearInputBuffer() {
    if (!inited) throw BadMode();

    fseek(file, 0, SEEK_END);
  }

  template<typename InS, typename OutS, typename Property>
  InS TerminalIOANSILinux<InS, OutS, Property>::getSymbol() {
    if (!inited) throw BadMode();

    try
    {
      if (checkInput()) {
        return InS::readFromFile(file);
      } else {
        throw NoSymbolYet();
      }
    }
    catch(typename InS::EndOfFile &)
    {
      throw InputEnd();
    }
    catch(typename InS::IOError &)
    {
      throw SymbolCorruption();
    }
    catch(typename InS::BadEncodingStreamGiven &)
    {
      throw WrongEncoding();
    }
  }

  template<typename InS, typename OutS, typename Property>
  std::queue<InS> TerminalIOANSILinux<InS, OutS, Property>::getSymbol(int n) {
    if (!inited) throw BadMode();

    std::queue<InS> new_q;

    try
    {
      for (int i = 0; i < n; i++) {
        if (checkInput()) {
          new_q.push(InS::readFromFile(file));
        } else {
          break;
        }
      }
    }
    catch(typename InS::EndOfFile &)
    {
      throw InputEnd(new_q);
    }
    catch(typename InS::BadEncodingStreamGiven &)
    {
      throw WrongEncoding(new_q);
    }

    return new_q;
  }


  template<typename InS, typename OutS, typename Property>
  bool TerminalIOANSILinux<InS, OutS, Property>::checkInput() {
    if (!inited) throw BadMode();

    static timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 0;

    static fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(fd, &readfds);

    if (select(1, &readfds, NULL, NULL, &tv)) return true;

    return false;
  }
}
