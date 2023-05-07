#include <alpha/syntax/handler/symbol/function/argument.h>

#include <alpha/symbol/table_manager.h>
#include <alpha/syntax/error.h>

namespace alpha::syntax::handlers::symbol::function {

void end_arg_list() {
  symTable.end_argument_list();
}

}  // namespace alpha::syntax::handlers::symbol::function
