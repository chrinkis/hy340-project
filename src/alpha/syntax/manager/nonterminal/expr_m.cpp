#include <alpha/syntax/manager/nonterminal/expr_m.h>

#include <alpha/icode/quad/table.h>

namespace alpha::syntax::manager::nonterminal {

ExprM ExprM::from_empty() {
  ExprM expr_m;

  expr_m.set_quad_label(quadTable.get_next_label());

  return expr_m;
}

ExprM::QuadLabel ExprM::get_quad_label() const {
  return this->label;
}

void ExprM::set_quad_label(const QuadLabel& quad_label) {
  this->label = quad_label;
}

}  // namespace alpha::syntax::manager::nonterminal
