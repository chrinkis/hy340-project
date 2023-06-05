#include <alpha/syntax/manager/nonterminal/whilestmt_cond.h>

#include <alpha/icode/expr.h>
#include <alpha/icode/quad/table.h>
#include <alpha/syntax/manager/nonterminal/expr.h>

using namespace alpha::syntax::manager::nonterminal;
using Opcode = alpha::icode::quad::Quad::Opcode;

WhilestmtCond WhilestmtCond::from_lParTkn_expr_rParTkn(const Expr& expr) {
  WhilestmtCond whilestmt_cond;

  icode::Expr quad_expr = expr.get_expr();
  icode::Expr const_bool = icode::Expr::for_const_bool(true);
  Quad::Label label = quadTable.get_next_label() + 2;
  quadTable.emit(Opcode::IF_EQ, emptyExpr, quad_expr, const_bool, label);

  whilestmt_cond.set_quad_address(quadTable.get_next_label());

  quadTable.emit(Opcode::JUMP, emptyExpr, emptyExpr, emptyExpr, 0);

  return whilestmt_cond;
}

WhilestmtCond::Quad::Label WhilestmtCond::get_quad_address() const {
  return this->quad_address;
}

void WhilestmtCond::set_quad_address(const Quad::Label& quad_address) {
  this->quad_address = quad_address;
}
