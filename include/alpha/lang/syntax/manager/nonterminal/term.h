#pragma once

#include <alpha/lang/icode/expr.h>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class Expr;
class Lvalue;
class Primary;

class Term {
 private:
  icode::Expr expr;

 public:
  static Term from_lParTkn_expr_rParTkn(const Expr& expr);

  static Term from_minusTkn_expr(const Expr& expr);

  static Term from_notTkn_expr(const Expr& expr);

  static Term from_plusPlusTkn_lvalue(const Lvalue& lvalue);

  static Term from_lvalue_plusPlusTkn(const Lvalue& lvalue);

  static Term from_minusMinusTkn_lvalue(const Lvalue& lvalue);

  static Term from_lvalue_minusMinusTkn(const Lvalue& lvalue);

  static Term from_primary(const Primary& primary);

 public:
  icode::Expr get_expr() const;
  void set_expr(const icode::Expr& expr);
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
