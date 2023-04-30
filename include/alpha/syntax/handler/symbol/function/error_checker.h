#pragma once

#include <alpha/syntax/holder/Symbol.h>

#include <string>

namespace alpha {
namespace syntax {
namespace handlers {
namespace symbol {
namespace function {

void check_for_errors(holder::Symbol& symbol_holder,
                      const std::string& description);

}  // namespace function
}  // namespace symbol
}  // namespace handlers
}  // namespace syntax
}  // namespace alpha

#define SET_COLOR_FOR_ERROR "\033[31m"
#define RESET_COLOR "\033[0m"
