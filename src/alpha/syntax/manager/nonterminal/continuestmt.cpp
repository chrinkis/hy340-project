#include <alpha/syntax/manager/nonterminal/continuestmt.h>

#include <alpha/icode/quad/table.h>

using namespace alpha::syntax::manager::nonterminal;

Continuestmt::Continuestmt() : break_list_head(0), continue_list_head(0) {}

Continuestmt Continuestmt::from_continueTkn() {
  Continuestmt continuestmt;

  continuestmt.break_list_head = quadTable.new_list(quadTable.get_next_label());
  quadTable.emit_jump(0);

  return continuestmt;
}
