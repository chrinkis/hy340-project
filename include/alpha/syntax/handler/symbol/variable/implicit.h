#pragma once

#define SET_COLOR_FOR_ERROR "\033[31m"
#define RESET_COLOR "\033[0m"

#define S_TABLE_SEARCH_AND_ADD_VAR(name, lvalue, location)         \
  {                                                                \
    SearchResultWithAccess result_info =                           \
        symbol_table.search_for_visible_symbol(name);              \
    bool is_accessible = result_info.accessible;                   \
    lvalue = result_info.result;                                   \
                                                                   \
    switch (lvalue) {                                              \
      case SearchResult::MUTABLE:                                  \
                                                                   \
        if (!is_accessible) {                                      \
          std::cerr << SET_COLOR_FOR_ERROR                         \
                    << "error trying  to access a variable "       \
                    << "with name \"" << name << "\" that is not " \
                    << "accesible" << std::endl                    \
                    << RESET_COLOR;                                \
          lvalue = SearchResult::NOT_FOUND;                        \
        }                                                          \
                                                                   \
        break;                                                     \
                                                                   \
      case SearchResult::UNMUTABLE:                                \
                                                                   \
        if (!is_accessible) {                                      \
          std::cerr << SET_COLOR_FOR_ERROR                         \
                    << "error trying  to access a function "       \
                    << "with name \"" << name << "\" that is not " \
                    << "accesible" << std::endl                    \
                    << RESET_COLOR;                                \
          lvalue = SearchResult::NOT_FOUND;                        \
        }                                                          \
                                                                   \
        break;                                                     \
                                                                   \
      case SearchResult::NOT_FOUND:                                \
                                                                   \
        if (symbol_table.can_add_variable(name)) {                 \
          symbol_table.add_variable(name, location);               \
          lvalue = SearchResult::MUTABLE;                          \
        } else {                                                   \
          assert(0);                                               \
        }                                                          \
                                                                   \
        break;                                                     \
                                                                   \
      default:                                                     \
        assert(0);                                                 \
    }
