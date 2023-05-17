#include <alpha/syntax/manager/nonterminal/breakstmt.h>

#include <alpha/icode/quad/table.h>
#include <alpha/syntax/error.h>
#include <alpha/syntax/loop_counter.h>

using namespace alpha::syntax::manager::nonterminal;

Breakstmt::Breakstmt() : break_list_head(0), continue_list_head(0) {}

Breakstmt Breakstmt::from_breakTkn(const location& loc) {
  Breakstmt breakstmt;

  if (!loopCounter.is_in_loop()) {
    error::invalid_use_of_break(loc);

  } else {
    breakstmt.break_list_head = quadTable.new_list(quadTable.get_next_label());
    quadTable.emit_jump(0);
  }

  return breakstmt;
}
