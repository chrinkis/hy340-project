#include <alpha/syntax/manager/nonterminal/breakstmt.h>

#include <alpha/icode/quad/table.h>

using namespace alpha::syntax::manager::nonterminal;

Breakstmt::Breakstmt() : break_list_head(0), continue_list_head(0) {}

Breakstmt Breakstmt::from_breakTkn() {
  Breakstmt breakstmt;

  breakstmt.break_list_head = quadTable.new_list(quadTable.get_next_label());
  quadTable.emit_jump(0);

  return breakstmt;
}
