#pragma once

#include <alpha/lang/icode/expr.h>
#include <vector>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class ElistOpt;
class Expr;

class Elist {
 public:
  using ExprCollection = std::vector<icode::Expr>;

 private:
  ExprCollection icode_elist;

 public:
  static Elist from_empty();
  static Elist from_expr_elistOpt(const Expr& expr, const ElistOpt& elist_opt);

 public:
  ExprCollection get_icode_elist() const;
  void set_icode_elist(const ExprCollection& icode_elist);
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
