#pragma once

#include <alpha/lang/icode/expr.h>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class Elist;
class Indexed;

class Objectdef {
 private:
  icode::Expr expr;

 public:
  static Objectdef from_lSqrBrackTkn_elist_rSqrBrackTkn(const Elist& elist);
  static Objectdef from_lSqrBrackTkn_indexed_rSqrBrackTkn(
      const Indexed& indexed);

 public:
  icode::Expr get_expr() const;
  void set_expr(const icode::Expr& expr);
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
