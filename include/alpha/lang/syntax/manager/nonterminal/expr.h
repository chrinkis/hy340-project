#pragma once

#include <alpha/icode/expr.h>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class Expr;
class Term;
class Assignexpr;

class Expr {
 private:
  icode::Expr expr;

 public:
  static Expr from_assignexpr(const Assignexpr& assignexpr);

  static Expr from_expr_plusTkn_expr(const Expr& left, const Expr& right);

  static Expr from_expr_minusTkn_expr(const Expr& left, const Expr& right);

  static Expr from_expr_starTkn_expr(const Expr& left, const Expr& right);

  static Expr from_expr_divTkn_expr(const Expr& left, const Expr& right);

  static Expr from_expr_modTkn_expr(const Expr& left, const Expr& right);

  static Expr from_expr_greaterTkn_expr(const Expr& left, const Expr& right);

  static Expr from_expr_greaterEqTkn_expr(const Expr& left, const Expr& right);

  static Expr from_expr_lessTkn_expr(const Expr& left, const Expr& right);

  static Expr from_expr_lessEqTkn_expr(const Expr& left, const Expr& right);

  static Expr from_expr_equalsTkn_expr(const Expr& left, const Expr& right);

  static Expr from_expr_notEqualsTkn_expr(const Expr& left, const Expr& right);

  static Expr from_expr_andTkn_expr(const Expr& left, const Expr& right);

  static Expr from_expr_orTkn_expr(const Expr& left, const Expr& right);

  static Expr from_term(const Term& term);

 public:
  icode::Expr get_expr() const;
  void set_expr(const icode::Expr& expr);
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
