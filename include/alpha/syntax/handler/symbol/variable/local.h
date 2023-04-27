#pragma once

#define SET_COLOR_FOR_ERROR "\033[31m"
#define RESET_COLOR "\033[0m"

#define S_TABLE_SEARCH_AND_ADD_LOCAL_VAR(name, lvalue, location)              \
  {                                                                           \
    lvalue = symbol_table.search_for_visible_local_symbol(name);              \
                                                                              \
    switch (lvalue) {                                                         \
      case SearchResult::MUTABLE:                                             \
        break;                                                                \
                                                                              \
      case SearchResult::UNMUTABLE:                                           \
        break;                                                                \
                                                                              \
      case SearchResult::NOT_FOUND:                                           \
                                                                              \
        if (symbol_table.can_add_local_variable(name)) {                      \
          symbol_table.add_local_variable(name, location);                    \
          lvalue = SearchResult::MUTABLE;                                     \
        } else {                                                              \
          std::cerr << SET_COLOR_FOR_ERROR << "error with local variable \""  \
                    << name << "\" shadowing a library function" << std::endl \
                    << RESET_COLOR;                                           \
        }                                                                     \
        break;                                                                \
                                                                              \
      default:                                                                \
        assert(0);                                                            \
    }                                                                         \
  }
