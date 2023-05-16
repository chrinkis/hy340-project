#include <alpha/syntax/manager/nonterminal/ifstmt_if.h>

#include <alpha/icode/quad/table.h>
#include <alpha/syntax/manager/nonterminal/expr.h>

using namespace alpha::syntax::manager::nonterminal;

IfstmtIf IfstmtIf::from_ifTkn_lParTkn_expr_rParTkn(const Expr& expr) {
  IfstmtIf ifstmt_if;

  quadTable.emit_if_eq(
      expr.get_expr(), icode::Expr::for_const_bool(true),
      icode::Expr::for_const_num(quadTable.get_next_label() + 2));

  ifstmt_if.set_label(quadTable.get_next_label());
  quadTable.emit_jump(0);

  return ifstmt_if;
}
