#pragma once

#include <alpha/symbol/symbol.h>

#include <functional>

namespace alpha {
namespace symbol {

class Table;

class TableKey {
  std::string symbol_name;
  Symbol::Scope symbol_scope;

 public:
  TableKey(const std::string& symbol_name, Symbol::Scope scope)
      : symbol_name(symbol_name), symbol_scope(scope) {}

  std::string get_symbol_name() const { return symbol_name; }
  Symbol::Scope get_symbol_scope() const { return symbol_scope; }

 public:
  bool operator==(const TableKey& other) const {
    return this->symbol_name == other.symbol_name &&
           this->symbol_scope == other.symbol_scope;
  }
};

}  // namespace symbol
}  // namespace alpha

template <>
struct std::hash<alpha::symbol::TableKey> {
  std::size_t operator()(const alpha::symbol::TableKey& key) const noexcept {
    std::hash<std::string> hasher;

    return hasher(std::to_string(key.get_symbol_scope()) +
                  key.get_symbol_name());
  }
};
