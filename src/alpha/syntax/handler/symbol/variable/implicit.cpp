#include <alpha/syntax/handler/symbol/variable/implicit.h>

#include <alpha/symbol/table_manager.h>
#include <cassert>

namespace alpha::syntax::handlers::symbol::variable {

void ensure_exists(holder::Symbol& symbol_holder, const std::string& name) {
  assert(!symbol_holder.get_symbol());

  auto result_opt = symTable.search_for_visible_symbol(name);

  if (!result_opt) {
    assert(symTable.can_add_variable(name));

    auto symbol = symTable.add_variable(
        name, alpha::symbol::Symbol::Location());  // FIXME update location

    symbol_holder.set_symbol(symbol);

    return;
  }

  auto result = result_opt.value();

  if (!result.accessible) {
    std::cerr << SET_COLOR_FOR_ERROR
              << "error trying  to access a variable/function "
              << "with name \"" << name << "\" that is not "
              << "accesible" << std::endl
              << RESET_COLOR;

    return;
  }

  symbol_holder.set_symbol(result.symbol);
}

}  // namespace alpha::syntax::handlers::symbol::variable
