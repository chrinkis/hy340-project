#include <alpha/syntax/handler/symbol/function/definition.h>

#include <alpha/symbol/table_manager.h>

using namespace alpha::syntax::handlers::symbol::function;
namespace manager = alpha::syntax::manager;
namespace holder = alpha::syntax::holder;

void start(holder::Symbol& symbol_holder,
           manager::terminal::Identifier& identifier) {
  if (!symTable.can_add_function(identifier.get_name())) {
    std::cerr << SET_COLOR_FOR_ERROR << "error inserting function \""
              << identifier.get_name() << "\" in Symbol Table" << std::endl
              << RESET_COLOR;

    auto symbol = symTable.start_function(identifier.get_location());
    symbol_holder.set_symbol(symbol);

    return;
  }

  auto symbol =
      symTable.start_function(identifier.get_name(), identifier.get_location());
  symbol_holder.set_symbol(symbol);
}

void start(holder::Symbol& symbol_holder,
           manager::terminal::Function& function) {
  auto symbol = symTable.start_function(function.get_location());
  symbol_holder.set_symbol(symbol);
}

void end() {
  symTable.end_function();
}
