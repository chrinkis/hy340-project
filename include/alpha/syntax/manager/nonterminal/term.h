#pragma once

#include <alpha/icode/expr.h>
#include <alpha/icode/quad/quad.h>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class Expr;
class Lvalue;
class Primary;

class Term {
 private:
  using QuadLabel = icode::quad::Quad::Label;

 private:
  icode::Expr expr;

  QuadLabel true_list_head = 0;
  QuadLabel false_list_head = 0;

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

  QuadLabel get_true_list_head() const;
  void set_true_list_head(const QuadLabel& head);

  QuadLabel get_false_list_head() const;
  void set_false_list_head(const QuadLabel& head);
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
