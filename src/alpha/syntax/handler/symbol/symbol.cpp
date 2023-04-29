#include <alpha/syntax/handler/symbol/symbol.h>

#include <assert.h>

using namespace alpha::syntax::handlers::symbol;
namespace holder = alpha::syntax::holder;

void continue_checking(holder::Symbol& symbol_holder,
                       const holder::Symbol& previous) {
  assert(!symbol_holder.get_symbol());

  symbol_holder.set_symbol(previous.get_symbol());
}

void stop_checking(holder::Symbol& symbol_holder) {
  symbol_holder.set_symbol(holder::Symbol::Optional());
}
