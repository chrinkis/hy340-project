#pragma once

#define SET_COLOR_FOR_ERROR "\033[31m"
#define RESET_COLOR "\033[0m"

#define S_TABLE_BLOCK_ENTER \
  { symbol_table.increase_scope(); }

#define S_TABLE_BLOCK_EXIT \
  { symbol_table.decrease_scope(); }
