#pragma once

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
