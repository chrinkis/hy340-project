#include <alpha/lang/syntax/manager/nonterminal/forstmt_pre.h>

#include <alpha/lang/icode/quad/table.h>
#include <alpha/lang/syntax/manager/nonterminal/expr.h>
#include <alpha/lang/syntax/manager/nonterminal/forstmt_m.h>

using namespace alpha::syntax::manager::nonterminal;
using Opcode = alpha::icode::quad::Quad::Opcode;

ForstmtPre ForstmtPre::from_forTkn_lParTkn_elist_smclnTkn_M_expr_smclnTkn(
    const ForstmtM& M,
    const Expr& expr) {
  ForstmtPre forstmt_pre;

  forstmt_pre.set_test(M.get_quad_address());
  forstmt_pre.set_enter(quadTable.get_next_label());

  quadTable.emit(Opcode::IF_EQ, emptyExpr, expr.get_expr(),
                 icode::Expr::for_const_bool(true), 0);

  return forstmt_pre;
}

ForstmtPre::Quad::Label ForstmtPre::get_test() const {
  return this->test;
}

void ForstmtPre::set_test(const Quad::Label& test) {
  this->test = test;
}

ForstmtPre::Quad::Label ForstmtPre::get_enter() const {
  return this->enter;
}

void ForstmtPre::set_enter(const Quad::Label& enter) {
  this->enter = enter;
}
