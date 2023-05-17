#include <alpha/syntax/manager/nonterminal/continuestmt.h>

#include <alpha/icode/quad/table.h>
#include <alpha/syntax/error.h>
#include <alpha/syntax/loop_counter.h>

using namespace alpha::syntax::manager::nonterminal;
using Opcode = alpha::icode::quad::Quad::Opcode;

Continuestmt::Continuestmt() : break_list_head(0), continue_list_head(0) {}

Continuestmt Continuestmt::from_continueTkn(const location& loc) {
  Continuestmt continuestmt;

  if (!loopCounter.is_in_loop()) {
    error::invalid_use_of_continue(loc);

  } else {
    continuestmt.break_list_head =
        quadTable.new_list(quadTable.get_next_label());
    quadTable.emit(Opcode::JUMP, emptyExpr, emptyExpr, emptyExpr, 0);
  }

  return continuestmt;
}
