#include <alpha/syntax/handler/symbol/variable/local.h>

#include <alpha/symbol/table_manager.h>
#include <alpha/syntax/error.h>

#include <cassert>

using Symbol = alpha::symbol::Symbol;

namespace alpha::syntax::handlers::symbol::variable {

void ensure_local_exists(holder::Symbol& symbol_holder,
                         const manager::terminal::Identifier& id) {
  assert(!symbol_holder.get_symbol());

  auto result_opt = symTable.search_for_visible_local_symbol(id.get_name());

  if (result_opt) {
    auto result = result_opt.value();
    symbol_holder.set_symbol(holder::Symbol::Optional(result.symbol));

    return;
  }

  if (!symTable.can_add_local_variable(id.get_name())) {
    error::print_semantic(
        "can not define local variable with the libray function `" +
            id.get_name() + "`",
        id.get_location());

    return;
  }

  Symbol::SharedPtr symbol =
      symTable.add_local_variable(id.get_name(), id.get_location());

  symbol_holder.set_symbol(holder::Symbol::Optional(symbol));
}

}  // namespace alpha::syntax::handlers::symbol::variable
