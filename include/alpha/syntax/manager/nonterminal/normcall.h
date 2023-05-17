#pragma once

#include <alpha/icode/expr.h>

#include <vector>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class Elist;

class Normcall {
 public:
  using ExprCollection = std::vector<icode::Expr>;

 private:
  ExprCollection elist;
  bool method;

 public:
  static Normcall from_lParTkn_elist_rParTkn(const Elist& elist);

 public:
  ExprCollection get_elist() const;
  void set_elist(const ExprCollection& elist);

  bool is_method() const;
  void set_method(bool is_method);
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
