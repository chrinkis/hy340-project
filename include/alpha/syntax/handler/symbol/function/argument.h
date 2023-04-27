#pragma once

#define SET_COLOR_FOR_ERROR "\033[31m"
#define RESET_COLOR "\033[0m"

#define S_TABLE_ADD_ARG(name, location)                                 \
  {                                                                     \
    if (symbol_table.can_add_argument(name)) {                          \
      symbol_table.add_argument(name, location);                        \
    } else {                                                            \
      std::cerr << SET_COLOR_FOR_ERROR << "error inserting argument \"" \
                << name << "\" in Symbol Table" << std::endl            \
                << RESET_COLOR;                                         \
    }                                                                   \
  }

#define S_TABLE_END_LIST_ARG() \
  { symbol_table.end_argument_list(); }
