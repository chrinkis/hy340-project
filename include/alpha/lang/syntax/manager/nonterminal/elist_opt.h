#pragma once

#include <alpha/lang/icode/expr.h>
#include <vector>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class Expr;

class ElistOpt {
 public:
  using ExprCollection = std::vector<icode::Expr>;

 private:
  ExprCollection icode_elist;

 public:
  static ElistOpt from_empty();
  static ElistOpt from_commaTkn_expr_elistOpt(const Expr& expr,
                                              const ElistOpt& elist_opt);

 public:
  ExprCollection get_icode_elist() const;
  void set_icode_elist(const ExprCollection& icode_elist);
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
