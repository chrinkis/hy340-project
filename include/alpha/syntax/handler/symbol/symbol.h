#pragma once

#include <alpha/syntax/holder/Symbol.h>

namespace alpha {
namespace syntax {
namespace handlers {
namespace symbol {

void continue_checking(holder::Symbol& symbol_holder, holder::Symbol& previous);
void stop_checking(holder::Symbol& symbol_holder);

}  // namespace symbol
}  // namespace handlers
}  // namespace syntax
}  // namespace alpha

#define SET_COLOR_FOR_ERROR "\033[31m"
#define RESET_COLOR "\033[0m"

#define S_TABLE_FURTHER_SYMBOL_CHECK_NEEDED(type_of_symbol, next_symbol) \
  { next_symbol = type_of_symbol; }

#define S_TABLE_NO_FURTHER_SYMBOL_CHECK_NEEDED(next_symbol) \
  { next_symbol = SearchResult::NOT_FOUND; }
