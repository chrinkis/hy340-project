#include <alpha/syntax/handler/symbol/variable/global.h>

#include <alpha/symbol/table_manager.h>

namespace alpha::syntax::handlers::symbol::variable {

void ensure_global_exists(holder::Symbol& symbol_holder,
                          const std::string& name) {
  assert(!symbol_holder.get_symbol());

  auto result_opt = symTable.search_for_visible_global_symbol(name);

  if (!result_opt) {
    std::cerr << SET_COLOR_FOR_ERROR
              << "error finding global variable or function "
              << "with name \"" << name << "\"" << std::endl
              << RESET_COLOR;

    return;
  }

  auto result = result_opt.value();
  symbol_holder.set_symbol(holder::Symbol::Optional(result.symbol));
}

}  // namespace alpha::syntax::handlers::symbol::variable