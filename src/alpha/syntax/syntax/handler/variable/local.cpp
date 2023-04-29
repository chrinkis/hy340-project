#include <alpha/syntax/handler/symbol/variable/local.h>

#include <alpha/symbol/table_manager.h>
#include <cassert>

using namespace alpha::syntax::handlers::symbol::variable;
namespace holder = alpha::syntax::holder;
using Symbol = alpha::symbol::Symbol;

void ensure_local_exists(holder::Symbol& symbol_holder,
                         const std::string& name) {
  assert(!symbol_holder.get_symbol());

  auto result_opt = symTable.search_for_visible_local_symbol(name);

  if (result_opt) {
    auto result = result_opt.value();
    symbol_holder.set_symbol(holder::Symbol::Optional(result.symbol));

    return;
  }

  if (!symTable.can_add_local_variable(name)) {
    std::cerr << SET_COLOR_FOR_ERROR << "error with local variable \"" << name
              << "\" shadowing a library function" << std::endl
              << RESET_COLOR;

    return;
  }

  Symbol::SharedPtr symbol = symTable.add_local_variable(
      name, Symbol::Location());  // FIXME update location

  symbol_holder.set_symbol(holder::Symbol::Optional(symbol));
}
