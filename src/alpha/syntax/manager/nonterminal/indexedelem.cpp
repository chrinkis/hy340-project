#include <alpha/syntax/manager/nonterminal/indexedelem.h>

#include <alpha/icode/quad/table.h>
#include <alpha/syntax/manager/nonterminal/expr.h>

using namespace alpha::syntax::manager::nonterminal;

Indexedelem Indexedelem::from_lCrlBrcktTkn_expr_dblClnTkn_expr_rCrlBrcktTkn(
    const Expr& expr1,
    const Expr& expr2) {
  Indexedelem indexedelem;

  auto expr_a =
      quadTable.emit_if_bool_expr(expr1.get_expr(), expr1.get_true_list_head(),
                                  expr1.get_false_list_head());

  auto expr_b =
      quadTable.emit_if_bool_expr(expr2.get_expr(), expr2.get_true_list_head(),
                                  expr2.get_false_list_head());

  Indexedelem::ExprPair icode_epair = {expr_a, expr_b};

  indexedelem.set_icode_epair(icode_epair);

  return indexedelem;
}

Indexedelem::ExprPair Indexedelem::get_icode_epair() const {
  return this->icode_epair;
}

void Indexedelem::set_icode_epair(ExprPair& icode_epair) {
  this->icode_epair = icode_epair;
}
