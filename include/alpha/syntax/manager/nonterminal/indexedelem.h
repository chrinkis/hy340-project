#pragma once

#include <alpha/icode/expr.h>
#include <utility>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class Expr;

class Indexedelem {
 public:
  using ExprPair = std::pair<icode::Expr, icode::Expr>;

 private:
  ExprPair icode_epair;

 public:
  static Indexedelem from_lCrlBrcktTkn_expr_dblClnTkn_expr_rCrlBrcktTkn(
      const Expr& expr1,
      const Expr& expr2);

 public:
  ExprPair get_icode_epair() const;
  void set_icode_epair(ExprPair& icode_epair);
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
