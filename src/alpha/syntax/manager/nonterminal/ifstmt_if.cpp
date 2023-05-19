#include <alpha/syntax/manager/nonterminal/ifstmt_if.h>

#include <alpha/icode/quad/table.h>
#include <alpha/syntax/manager/nonterminal/expr.h>

using namespace alpha::syntax::manager::nonterminal;

using Quad = alpha::icode::quad::Quad;
using Opcode = alpha::icode::quad::Quad::Opcode;

IfstmtIf IfstmtIf::from_ifTkn_lParTkn_expr_rParTkn(const Expr& _expr) {
  IfstmtIf ifstmt_if;

  auto expr =
      quadTable.emit_if_bool_expr(_expr.get_expr(), _expr.get_true_list_head(),
                                  _expr.get_false_list_head());

  quadTable.emit(Opcode::IF_EQ, emptyExpr, expr,
                 icode::Expr::for_const_bool(true),
                 quadTable.get_next_label() + 2);

  ifstmt_if.set_label(quadTable.get_next_label());
  quadTable.emit(Opcode::JUMP, emptyExpr, emptyExpr, emptyExpr, 0);

  return ifstmt_if;
}

Quad::Label IfstmtIf::get_label() const {
  return this->label;
}

void IfstmtIf::set_label(const Quad::Label& label) {
  this->label = label;
}
