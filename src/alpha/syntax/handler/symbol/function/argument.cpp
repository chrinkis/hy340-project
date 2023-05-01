#include <alpha/syntax/handler/symbol/function/argument.h>

#include <alpha/symbol/table_manager.h>
#include <alpha/syntax/error.h>

namespace alpha::syntax::handlers::symbol::function {

void add_arg(const manager::terminal::Identifier& argument) {
  if (!symTable.can_add_argument(argument.get_name())) {
    error::print_semantic("invalid argument name `" + argument.get_name() + "`",
                          argument.get_location());

    return;
  }

  symTable.add_argument(argument.get_name(), argument.get_location());
}

void end_arg_list() {
  symTable.end_argument_list();
}

}  // namespace alpha::syntax::handlers::symbol::function
