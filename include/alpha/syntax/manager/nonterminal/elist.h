#pragma once

#include <alpha/icode/expr.h>
#include <vector>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class ElistOpt;
class Expr;

class Elist {
  using ExprCollection = std::vector<icode::Expr>;

 private:
  ExprCollection icode_elist;

 public:
  static Elist from_empty();
  static Elist from_expr_elistOpt(const Expr& expr, const ElistOpt& elist_opt);

 public:
  ExprCollection get_icode_elist() const;
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
