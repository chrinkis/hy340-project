#pragma once

#include <alpha/icode/expr.h>

namespace alpha::syntax::holder {

class Expr {
  icode::Expr::SharedPtr expr;

 public:
  Expr(const icode::Expr::SharedPtr& expr);

  icode::Expr::SharedPtr get_expr() const;

  // void set_symbol(const icode::Expr& optional_symbol);
};

}  // namespace alpha::syntax::holder
