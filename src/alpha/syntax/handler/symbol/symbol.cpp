#include <alpha/syntax/handler/symbol/symbol.h>

#include <assert.h>

namespace alpha::syntax::handlers::symbol {

void continue_checking(holder::Symbol& symbol_holder,
                       const holder::Symbol& previous) {
  assert(!symbol_holder.get_symbol());

  symbol_holder.set_symbol(previous.get_symbol());
}

}  // namespace alpha::syntax::handlers::symbol
