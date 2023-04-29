#include <alpha/syntax/handler/symbol/function/definition.h>

#include <alpha/symbol/table_manager.h>

using namespace alpha::syntax::handlers::symbol::function;
namespace manager = alpha::syntax::manager;

void start(manager::terminal::Identifier& identifier) {
  if (!symTable.can_add_function(identifier.get_name())) {
    std::cerr << SET_COLOR_FOR_ERROR << "error inserting function \""
              << identifier.get_name() << "\" in Symbol Table" << std::endl
              << RESET_COLOR;

    symTable.start_function(identifier.get_location());

    return;
  }

  symTable.start_function(identifier.get_name(), identifier.get_location());
}

void start(manager::terminal::Function& function) {
  symTable.start_function(function.get_location());
}

void end() {
  symTable.end_function();
}
