#include <alpha/syntax/manager/nonterminal/ifstmt_else.h>

#include <alpha/icode/quad/table.h>

using namespace alpha::syntax::manager::nonterminal;

IfstmtElse IfstmtElse::from_elseTkn() {
  IfstmtElse ifstmt_else;

  ifstmt_else.set_quad_address(quadTable.get_next_label());
  quadTable.emit_jump(0);

  return ifstmt_else;
}
