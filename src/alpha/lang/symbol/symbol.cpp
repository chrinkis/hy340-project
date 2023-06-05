#include <alpha/lang/symbol/symbol.h>

#include <assert.h>
#include <iomanip>
#include <sstream>

namespace alpha {
namespace symbol {

std::string Symbol::to_string() const {
  auto ident = [](int w = 20) { return std::setw(w); };

  std::stringstream os;
  const Symbol& symbol = *this;

  os << std::left;

  os << ident(32);
  os << "\"" + symbol.get_name() + "\"";

  os << ident(26);
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

  os << ident();
  switch (symbol.get_space()) {
    case Symbol::ScopeSpace::PROGRAM_VAR:
      os << "[program var]";
      break;
    case Symbol::ScopeSpace::FORMAL_ARG:
      os << "[formal arg]";
      break;
    case Symbol::ScopeSpace::FUNCTION_LOCAL:
      os << "[function local]";
      break;
    default:
      assert(0);
  }

  os << ident();
  os << "(offset " + std::to_string(symbol.get_offset()) + ')';

  return os.str();
}

bool Symbol::has_function_type() const {
  switch (this->get_type()) {
    case Type::GLOBAL:
    case Type::LOCAL:
    case Type::FORMAL:
      return false;
    case Type::USER_FUNCTION:
    case Type::LIBRARY_FUNCTION:
      return true;
    default:
      assert(0);
  }

  assert(0);
}

std::ostream& operator<<(std::ostream& os, const Symbol& symbol) {
  os << symbol.to_string();

  return os;
}

}  // namespace symbol
}  // namespace alpha
