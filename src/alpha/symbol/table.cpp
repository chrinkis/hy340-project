#include <alpha/symbol/table.h>

#include <alpha/symbol/function.h>
#include <alpha/symbol/variable.h>

#include <cassert>
#include <iomanip>
#include <iostream>
#include <sstream>

#define pairOf(symbol) (Pair(symbol.get_name(), Entry(symbol.clone())))

using namespace alpha::symbol;

Symbol::SharedPtr Table::insert(const symbol::Symbol& symbol) {
  Symbol::Scope scope = symbol.get_scope();

  if (this->per_scope_map.size() <= scope) {
    this->per_scope_map.resize(scope + 1);
  }

  auto pair = pairOf(symbol);

  this->per_scope_map.at(scope).insert(pair);

  return pair.second.get_symbol();
}

std::optional<TableEntry> Table::lookup(const std::string& name,
                                        const Symbol::Scope& _start,
                                        const Symbol::Scope& end) const {
  assert(_start >= end);

  if (this->per_scope_map.size() <= end) {
    return std::optional<TableEntry>();
  }

  Symbol::Scope start = _start;

  if (this->per_scope_map.size() <= start) {
    start = this->per_scope_map.size() - 1;
  }

  for (Symbol::Scope i = start; i >= end; i--) {
    const Map& map = this->per_scope_map.at(i);

    auto symbols = map.equal_range(Key(name));
    for (auto pair = symbols.first; pair != symbols.second; pair++) {
      if (pair->second.get_is_active()) {
        return std::optional(pair->second);
      }
    }

    if (i == 0) {
      break;  // Scope is unsigned int, so (0 - 1 > 0)
    }
  }

  return std::optional<TableEntry>();
}

void Table::hide(const Symbol::Scope& scope) {
  if (this->per_scope_map.size() <= scope) {
    return;
  }

  for (auto& pair : this->per_scope_map.at(scope)) {
    assert(pair.second.get_symbol()->get_scope() == scope);

    if (pair.second.get_is_active()) {
      pair.second.deactivate();
    }
  }
}

namespace alpha {
namespace symbol {

std::ostream& operator<<(std::ostream& os, const Table& st) {
  auto ident = [](int w = 26) { return std::setw(w); };

  os << std::left;

  os << "\x1B[42m";
  os << "\x1B[30m";
  os << std::endl;

  for (Symbol::Scope scope = 0; scope < st.per_scope_map.size(); scope++) {
    os << "--> Scope " << scope << " <--" << std::endl;

    auto map = st.per_scope_map.at(scope);

    for (auto pair : map) {
      Symbol::SharedPtr symbol = pair.second.get_symbol();

      os << ident();
      os << "\"" + symbol->get_name() + "\"";

      os << ident();
      switch (symbol->get_type()) {
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
      location << "(line " << symbol->get_location().begin.line << ')';
      os << location.str();

      os << ident();
      os << "(scope " + std::to_string(symbol->get_scope()) + ')';

      os << ident();
      os << "{active " + std::to_string(pair.second.get_is_active()) + '}';

      os << std::endl;
    }

    os << std::endl;
  }

  os << "\033[0m\t\t";

  return os;
}

}  // namespace symbol
}  // namespace alpha
