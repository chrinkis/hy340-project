#include <alpha/syntax/handler/block.h>

#include <alpha/symbol/table_manager.h>

namespace alpha::syntax::handlers::block {

void enter() {
  symTable.increase_scope();
}

void exit() {
  symTable.decrease_scope();
}

}  // namespace alpha::syntax::handlers::block
