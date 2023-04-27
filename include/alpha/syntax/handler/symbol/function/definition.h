#pragma once

#include <alpha/syntax/manager/terminal/function.h>
#include <alpha/syntax/manager/terminal/identifier.h>

namespace alpha {
namespace syntax {
namespace handlers {
namespace symbol {
namespace function {

void start(manager::terminal::Identifier& identifier);
void start(manager::terminal::Function& function);
void end();

}  // namespace function
}  // namespace symbol
}  // namespace handlers
}  // namespace syntax
}  // namespace alpha

#define SET_COLOR_FOR_ERROR "\033[31m"
#define RESET_COLOR "\033[0m"

#define S_TABLE_FUNC_START(name, location)                              \
  {                                                                     \
    if (symbol_table.can_add_function(name)) {                          \
      symbol_table.start_function(name, location);                      \
    } else {                                                            \
      std::cerr << SET_COLOR_FOR_ERROR << "error inserting function \"" \
                << name << "\" in Symbol Table" << std::endl            \
                << RESET_COLOR;                                         \
      S_TABLE_FUNC_START_ANONYMOYS(location)                            \
    }                                                                   \
  }

#define S_TABLE_FUNC_START_ANONYMOYS(location) \
  { symbol_table.start_function(location); }

#define S_TABLE_FUNC_END \
  { symbol_table.end_function(); }
