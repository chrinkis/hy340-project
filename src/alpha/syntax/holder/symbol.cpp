#include <alpha/syntax/holder/Symbol.h>

using namespace alpha::syntax::holder;

Symbol::Optional Symbol::get_symbol() const {
  return this->symbol_opt;
}

void Symbol::set_symbol(const Optional& optional_symbol) {
  this->symbol_opt = optional_symbol;
}
