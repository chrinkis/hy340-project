#pragma once

#include <alpha/icode/expr.h>
#include <alpha/icode/quad/quad.h>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class Expr;
class ExprM;
class Term;
class Assignexpr;

class Expr {
 private:
  using QuadLabel = icode::quad::Quad::Label;

 private:
  icode::Expr expr;

  QuadLabel true_list_head = 0;
  QuadLabel false_list_head = 0;

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

  static Expr from_expr_andTkn_exprM_expr(const Expr& left,
                                          const ExprM& expr_m,
                                          const Expr& right);

  static Expr from_expr_orTkn_exprM_expr(const Expr& left,
                                         const ExprM& expr_m,
                                         const Expr& right);

  static Expr from_term(const Term& term);

 public:
  icode::Expr get_expr() const;
  void set_expr(const icode::Expr& expr);

  QuadLabel get_true_list_head() const;
  void set_true_list_head(const QuadLabel& head);

  QuadLabel get_false_list_head() const;
  void set_false_list_head(const QuadLabel& head);
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
