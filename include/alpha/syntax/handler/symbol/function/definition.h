#pragma once

#include <alpha/syntax/holder/Symbol.h>
#include <alpha/syntax/manager/terminal/function.h>
#include <alpha/syntax/manager/terminal/identifier.h>

namespace alpha {
namespace syntax {
namespace handlers {
namespace symbol {
namespace function {

void start(holder::Symbol& symbol_holder,
           const manager::terminal::Identifier& identifier);

void start(holder::Symbol& symbol_holder,
           const manager::terminal::Function& function);
void end();

}  // namespace function
}  // namespace symbol
}  // namespace handlers
}  // namespace syntax
}  // namespace alpha

#define SET_COLOR_FOR_ERROR "\033[31m"
#define RESET_COLOR "\033[0m"
