#include "terminal_io_ansi_linux_impl.hpp"
#include "../../property.hpp"
#include "../../symbol_utf8/symbol_utf8.hpp"

#include <sys/select.h>

namespace blessings {
  template<>
  void TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI>::
  setSGR(const PropertyANSI& prop) {
    if (prop!=currentProperty) {
      try {
        resetSGR();

        if (prop.bold) {
          ws->write(ANSISymbolTable<SymbolUTF8>::ESCSymbol);
          ws->write(ANSISymbolTable<SymbolUTF8>::openBracket);
          ws->write(ANSISymbolTable<SymbolUTF8>::one);
          ws->write(ANSISymbolTable<SymbolUTF8>::mSym);
        }

        if (prop.italics) {
          ws->write(ANSISymbolTable<SymbolUTF8>::ESCSymbol);
          ws->write(ANSISymbolTable<SymbolUTF8>::openBracket);
          ws->write(ANSISymbolTable<SymbolUTF8>::three);
          ws->write(ANSISymbolTable<SymbolUTF8>::mSym);
        }

        if (prop.color!=ColorANSI::NONE) {
          ws->write(ANSISymbolTable<SymbolUTF8>::ESCSymbol);
          ws->write(ANSISymbolTable<SymbolUTF8>::openBracket);
          ws->write(ANSISymbolTable<SymbolUTF8>::three);
          switch(prop.color.color) {
          case ColorANSI::BLACK:
            ws->write(ANSISymbolTable<SymbolUTF8>::zero);
            break;
          case ColorANSI::RED:
            ws->write(ANSISymbolTable<SymbolUTF8>::one);
            break;
          case ColorANSI::GREEN:
            ws->write(ANSISymbolTable<SymbolUTF8>::two);
            break;
          case ColorANSI::YELLOW:
            ws->write(ANSISymbolTable<SymbolUTF8>::three);
            break;
          case ColorANSI::BLUE:
            ws->write(ANSISymbolTable<SymbolUTF8>::four);
            break;
          case ColorANSI::MAGENTA:
            ws->write(ANSISymbolTable<SymbolUTF8>::five);
            break;
          case ColorANSI::CYAN:
            ws->write(ANSISymbolTable<SymbolUTF8>::six);
            break;
          case ColorANSI::WHITE:
            ws->write(ANSISymbolTable<SymbolUTF8>::seven);
            break;
          default:
            throw ArgumentError();
          }
          ws->write(ANSISymbolTable<SymbolUTF8>::mSym);
        }

        if (prop.backgroundColor.color!=ColorANSI::NONE) {
          ws->write(ANSISymbolTable<SymbolUTF8>::ESCSymbol);
          ws->write(ANSISymbolTable<SymbolUTF8>::openBracket);
          ws->write(ANSISymbolTable<SymbolUTF8>::four);
          switch(prop.backgroundColor.color) {
          case ColorANSI::BLACK:
            ws->write(ANSISymbolTable<SymbolUTF8>::zero);
            break;
          case ColorANSI::RED:
            ws->write(ANSISymbolTable<SymbolUTF8>::one);
            break;
          case ColorANSI::GREEN:
            ws->write(ANSISymbolTable<SymbolUTF8>::two);
            break;
          case ColorANSI::YELLOW:
            ws->write(ANSISymbolTable<SymbolUTF8>::three);
            break;
          case ColorANSI::BLUE:
            ws->write(ANSISymbolTable<SymbolUTF8>::four);
            break;
          case ColorANSI::MAGENTA:
            ws->write(ANSISymbolTable<SymbolUTF8>::five);
            break;
          case ColorANSI::CYAN:
            ws->write(ANSISymbolTable<SymbolUTF8>::six);
            break;
          case ColorANSI::WHITE:
            ws->write(ANSISymbolTable<SymbolUTF8>::seven);
            break;
          default:
            throw ArgumentError();
          }
          ws->write(ANSISymbolTable<SymbolUTF8>::mSym);
        }
      }
      catch(...) {
        throw IOError();
      }

      currentProperty=prop;
    }
  }

  template class TerminalIOANSILinux<SymbolUTF8, SymbolUTF8, PropertyANSI>;
}
