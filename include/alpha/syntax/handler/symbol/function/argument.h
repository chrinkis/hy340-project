#pragma once

#include <alpha/syntax/manager/terminal/identifier.h>

namespace alpha {
namespace syntax {
namespace handlers {
namespace symbol {
namespace function {

void add_arg(manager::terminal::Identifier& argument);
void end_arg_list();

}  // namespace function
}  // namespace symbol
}  // namespace handlers
}  // namespace syntax
}  // namespace alpha

#define SET_COLOR_FOR_ERROR "\033[31m"
#define RESET_COLOR "\033[0m"
