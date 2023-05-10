#pragma once

#include <alpha/icode/expr.h>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class Lvalue;

class Assignexpr {
 private:
  icode::Expr expr;

 public:
  static Assignexpr from_lvalue_assignTkn_expr(const Lvalue& lvalue);

 public:
  icode::Expr get_expr() const;
  void set_expr(const icode::Expr& expr);
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
