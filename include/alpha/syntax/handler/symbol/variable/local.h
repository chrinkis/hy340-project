#pragma once

#include <alpha/syntax/holder/Symbol.h>
#include <alpha/syntax/manager/terminal/identifier.h>

#include <string>

namespace alpha {
namespace syntax {
namespace handlers {
namespace symbol {
namespace variable {

void ensure_local_exists(holder::Symbol& symbol_holder,
                         const manager::terminal::Identifier& id);

}  // namespace variable
}  // namespace symbol
}  // namespace handlers
}  // namespace syntax
}  // namespace alpha

#define SET_COLOR_FOR_ERROR "\033[31m"
#define RESET_COLOR "\033[0m"
