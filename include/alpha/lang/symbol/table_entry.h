#pragma once

#include <alpha/lang/symbol/symbol.h>
#include <cassert>

namespace alpha {
namespace symbol {

class Table;

class TableEntry {
  bool is_active;
  Symbol::SharedPtr symbol;

 public:
  TableEntry(Symbol* symbol) : symbol(symbol), is_active(true) {
    assert(symbol);
  }

  bool get_is_active() const { return is_active; };
  Symbol::SharedPtr get_symbol() const { return symbol; };

  void deactivate() { is_active = false; };
};

}  // namespace symbol
}  // namespace alpha
