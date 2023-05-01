#include <alpha/syntax/handler/symbol/variable/implicit.h>

#include <alpha/symbol/table_manager.h>
#include <alpha/syntax/error.h>

#include <cassert>

namespace alpha::syntax::handlers::symbol::variable {

void ensure_exists(holder::Symbol& symbol_holder,
                   const manager::terminal::Identifier& id) {
  assert(!symbol_holder.get_symbol());

  auto result_opt = symTable.search_for_visible_symbol(id.get_name());

  if (!result_opt) {
    assert(symTable.can_add_variable(id.get_name()));

    auto symbol = symTable.add_variable(id.get_name(), id.get_location());

    symbol_holder.set_symbol(symbol);

    return;
  }

  auto result = result_opt.value();

  if (!result.accessible) {
    error::print_semantic(
        "can not access variable/function `" + id.get_name() + "`",
        id.get_location());

    return;
  }

  symbol_holder.set_symbol(result.symbol);
}

}  // namespace alpha::syntax::handlers::symbol::variable
