#include <alpha/lang/symbol/table.h>

#include <alpha/lang/symbol/function.h>
#include <alpha/lang/symbol/variable.h>

#include <cassert>
#include <iostream>
#include <sstream>

#define pairOf(symbol) (Pair(symbol.get_name(), Entry(symbol.clone())))

#define FG_COLOR "\x1B[30m"
#define BG_COLOR "\x1B[42m"
#define DEFAULT_COLOR "\033[0m"

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
  os << std::left;

  os << FG_COLOR << BG_COLOR;
  os << std::endl;

  for (Symbol::Scope scope = 0; scope < st.per_scope_map.size(); scope++) {
    os << "--> Scope " << scope << " <--" << std::endl;

    auto map = st.per_scope_map.at(scope);

    for (auto pair : map) {
      Symbol::SharedPtr symbol = pair.second.get_symbol();

      os << *symbol << std::endl;
    }

    os << std::endl;
  }

  os << DEFAULT_COLOR;

  return os;
}

}  // namespace symbol
}  // namespace alpha
