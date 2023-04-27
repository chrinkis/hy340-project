#pragma once

namespace alpha {
namespace syntax {
namespace handlers {
namespace block {

void enter();
void exit();

}  // namespace block
}  // namespace handlers
}  // namespace syntax
}  // namespace alpha

#define S_TABLE_BLOCK_ENTER \
  { symbol_table.increase_scope(); }

#define S_TABLE_BLOCK_EXIT \
  { symbol_table.decrease_scope(); }
