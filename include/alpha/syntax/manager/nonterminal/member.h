#pragma once

#include <alpha/icode/expr.h>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class Lvalue;

class Member {
 private:
  icode::Expr expr;

 public:
  static Member from_lvalue_dotTkn_idTkn(const Lvalue& lvalue);

  static Member from_lvalue_lSqrBrackTkn_expr_rSqrtBrackTkn(
      const Lvalue& lvalue);

  static Member from_call_dotTkn_idTkn();

  static Member from_call_lSqrBrackTkn_expr_rSqrtBrackTkn();

 public:
  icode::Expr get_expr() const;
  void set_expr(const icode::Expr& expr);
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
