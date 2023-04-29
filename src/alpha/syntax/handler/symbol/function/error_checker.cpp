#include <alpha/syntax/handler/symbol/function/error_checker.h>

#include <alpha/symbol/table_manager.h>

#include <cassert>

using namespace alpha::syntax::handlers::symbol::function;
namespace holder = alpha::syntax::holder;

void check_for_errors(holder::Symbol& symbol_holder,
                      const std::string& description) {
  if (!symbol_holder.get_symbol()) {
    return;
  }

  auto symbol = symbol_holder.get_symbol().value();

  switch (symbol->get_type()) {
    case alpha::symbol::Symbol::Type::GLOBAL:
    case alpha::symbol::Symbol::Type::LOCAL:
    case alpha::symbol::Symbol::Type::FORMAL:
      break;
    case alpha::symbol::Symbol::Type::USER_FUNCTION:
    case alpha::symbol::Symbol::Type::LIBRARY_FUNCTION:
      std::cerr << SET_COLOR_FOR_ERROR << "error: cannot perform "
                << description << " a function" << std::endl
                << RESET_COLOR;
      break;
    default:
      assert(0);
  }
}
