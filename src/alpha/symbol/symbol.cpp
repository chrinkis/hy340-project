#include <alpha/symbol/symbol.h>

#include <assert.h>
#include <iomanip>

namespace alpha {
namespace symbol {

std::ostream& operator<<(std::ostream& os, const Symbol& symbol) {
  auto ident = [](int w = 26) { return std::setw(w); };

  os << ident();
  os << "\"" + symbol.get_name() + "\"";

  os << ident();
  switch (symbol.get_type()) {
    case Symbol::Type::GLOBAL:
      os << "[global variable]";
      break;
    case Symbol::Type::LOCAL:
      os << "[local variable]";
      break;
    case Symbol::Type::FORMAL:
      os << "[formal argument]";
      break;
    case Symbol::Type::USER_FUNCTION:
      os << "[user function]";
      break;
    case Symbol::Type::LIBRARY_FUNCTION:
      os << "[library function]";
      break;
    default:
      assert(0);
  }

  os << ident();
  std::stringstream location;
  location << "(line " << symbol.get_location().begin.line << ')';
  os << location.str();

  os << ident();
  os << "(scope " + std::to_string(symbol.get_scope()) + ')';

  return os;
}

}  // namespace symbol
}  // namespace alpha
