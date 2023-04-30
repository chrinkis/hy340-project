#include <alpha/syntax/handler/symbol/function/argument.h>

#include <alpha/symbol/table_manager.h>

namespace alpha::syntax::handlers::symbol::function {

void add_arg(const manager::terminal::Identifier& argument) {
  if (!symTable.can_add_argument(argument.get_name())) {
    std::cerr << SET_COLOR_FOR_ERROR << "error inserting argument \""
              << argument.get_name() << "\" in Symbol Table" << std::endl
              << RESET_COLOR;

    return;
  }

  symTable.add_argument(argument.get_name(), argument.get_location());
}

void end_arg_list() {
  symTable.end_argument_list();
}

}  // namespace alpha::syntax::handlers::symbol::function
