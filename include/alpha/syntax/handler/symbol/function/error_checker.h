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

#define S_TABLE_CHECK_FUNCTION_ERRORS(type_of_symbol, usage_info)  \
  {                                                                \
    if (type_of_symbol == SearchResult::UNMUTABLE) {               \
      std::cerr << SET_COLOR_FOR_ERROR << "error: cannot perform " \
                << usage_info << " a function" << std::endl        \
                << RESET_COLOR;                                    \
    }                                                              \
  }
