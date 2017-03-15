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
          ANSISymbolTable<SymbolUTF8>::ESCSymbol.writeToFile(file);
          ANSISymbolTable<SymbolUTF8>::openBracket.writeToFile(file);
          ANSISymbolTable<SymbolUTF8>::one.writeToFile(file);
          ANSISymbolTable<SymbolUTF8>::mSym.writeToFile(file);
        }

        if (prop.italics) {
          ANSISymbolTable<SymbolUTF8>::ESCSymbol.writeToFile(file);
          ANSISymbolTable<SymbolUTF8>::openBracket.writeToFile(file);
          ANSISymbolTable<SymbolUTF8>::three.writeToFile(file);
          ANSISymbolTable<SymbolUTF8>::mSym.writeToFile(file);
        }

        if (prop.color!=ColorANSI::NONE) {
          ANSISymbolTable<SymbolUTF8>::ESCSymbol.writeToFile(file);
          ANSISymbolTable<SymbolUTF8>::openBracket.writeToFile(file);
          ANSISymbolTable<SymbolUTF8>::three.writeToFile(file);
          switch(prop.color.color) {
          case ColorANSI::BLACK:
            ANSISymbolTable<SymbolUTF8>::zero.writeToFile(file);
            break;
          case ColorANSI::RED:
            ANSISymbolTable<SymbolUTF8>::one.writeToFile(file);
            break;
          case ColorANSI::GREEN:
            ANSISymbolTable<SymbolUTF8>::two.writeToFile(file);
            break;
          case ColorANSI::YELLOW:
            ANSISymbolTable<SymbolUTF8>::three.writeToFile(file);
            break;
          case ColorANSI::BLUE:
            ANSISymbolTable<SymbolUTF8>::four.writeToFile(file);
            break;
          case ColorANSI::MAGENTA:
            ANSISymbolTable<SymbolUTF8>::five.writeToFile(file);
            break;
          case ColorANSI::CYAN:
            ANSISymbolTable<SymbolUTF8>::six.writeToFile(file);
            break;
          case ColorANSI::WHITE:
            ANSISymbolTable<SymbolUTF8>::seven.writeToFile(file);
            break;
          default:
            throw ArgumentError();
          }
          ANSISymbolTable<SymbolUTF8>::mSym.writeToFile(file);
        }

        if (prop.backgroundColor.color!=ColorANSI::NONE) {
          ANSISymbolTable<SymbolUTF8>::ESCSymbol.writeToFile(file);
          ANSISymbolTable<SymbolUTF8>::openBracket.writeToFile(file);
          ANSISymbolTable<SymbolUTF8>::four.writeToFile(file);
          switch(prop.backgroundColor.color) {
          case ColorANSI::BLACK:
            ANSISymbolTable<SymbolUTF8>::zero.writeToFile(file);
            break;
          case ColorANSI::RED:
            ANSISymbolTable<SymbolUTF8>::one.writeToFile(file);
            break;
          case ColorANSI::GREEN:
            ANSISymbolTable<SymbolUTF8>::two.writeToFile(file);
            break;
          case ColorANSI::YELLOW:
            ANSISymbolTable<SymbolUTF8>::three.writeToFile(file);
            break;
          case ColorANSI::BLUE:
            ANSISymbolTable<SymbolUTF8>::four.writeToFile(file);
            break;
          case ColorANSI::MAGENTA:
            ANSISymbolTable<SymbolUTF8>::five.writeToFile(file);
            break;
          case ColorANSI::CYAN:
            ANSISymbolTable<SymbolUTF8>::six.writeToFile(file);
            break;
          case ColorANSI::WHITE:
            ANSISymbolTable<SymbolUTF8>::seven.writeToFile(file);
            break;
          default:
            throw ArgumentError();
          }
          ANSISymbolTable<SymbolUTF8>::mSym.writeToFile(file);
        }

        int resCode=fflush(file);
        if (resCode==EOF) {
          throw IOError();
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
