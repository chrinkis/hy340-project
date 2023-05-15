#pragma once

#include <alpha/icode/expr.h>
#include <vector>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class Expr;

class ElistOpt {
  using ExprCollection = std::vector<icode::Expr>;

  ExprCollection expr_list;

 public:
  static ElistOpt from_empty();
  static ElistOpt from_commaTkn_expr_elistOpt(const Expr& expr,
                                              const ElistOpt& elist_opt);

 public:
  ExprCollection get_expr_list() const;
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
