#pragma once

#define SET_COLOR_FOR_ERROR "\033[31m"
#define RESET_COLOR "\033[0m"

#define S_TABLE_SEARCH_GLOBAL_VAR(name, lvalue)                   \
  {                                                               \
    lvalue = symbol_table.search_for_visible_global_symbol(name); \
                                                                  \
    switch (lvalue) {                                             \
      case SearchResult::MUTABLE:                                 \
        break;                                                    \
                                                                  \
      case SearchResult::UNMUTABLE:                               \
        break;                                                    \
                                                                  \
      case SearchResult::NOT_FOUND:                               \
                                                                  \
        std::cerr << SET_COLOR_FOR_ERROR                          \
                  << "error finding global variable or function " \
                  << "with name \"" << name << "\"" << std::endl  \
                  << RESET_COLOR;                                 \
                                                                  \
        break;                                                    \
                                                                  \
      default:                                                    \
        assert(0);                                                \
    }                                                             \
  }
