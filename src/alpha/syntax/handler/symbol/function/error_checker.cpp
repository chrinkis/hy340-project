#include <alpha/syntax/handler/symbol/function/error_checker.h>

#include <alpha/symbol/table_manager.h>
#include <alpha/syntax/error.h>

#include <cassert>

namespace alpha::syntax::handlers::symbol::function {

void check_for_errors(const holder::Symbol& symbol_holder,
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
      error::print_semantic("cannot perform " + description +
                            " the function `" + symbol->get_name() +
                            "`");  // TODO use location of error instead of
                                   // function defintion
      break;
    default:
      assert(0);
  }
}

}  // namespace alpha::syntax::handlers::symbol::function
