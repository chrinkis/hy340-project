#include <alpha/syntax/holder/expr.h>

namespace alpha::syntax::holder {

Expr::Expr(const icode::Expr::SharedPtr& expr) : expr(expr) {}

icode::Expr::SharedPtr Expr::get_expr() const {
  return this->expr;
}

}  // namespace alpha::syntax::holder
