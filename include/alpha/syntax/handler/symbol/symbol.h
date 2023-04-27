#pragma once

#define SET_COLOR_FOR_ERROR "\033[31m"
#define RESET_COLOR "\033[0m"

#define S_TABLE_FURTHER_SYMBOL_CHECK_NEEDED(type_of_symbol, next_symbol) \
  { next_symbol = type_of_symbol; }

#define S_TABLE_NO_FURTHER_SYMBOL_CHECK_NEEDED(next_symbol) \
  { next_symbol = SearchResult::NOT_FOUND; }
