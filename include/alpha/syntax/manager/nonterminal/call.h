#pragma once

#include <alpha/icode/expr.h>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class Elist;
class Callsuffix;
class Funcdef;

class Call {
 private:
  icode::Expr expr;

 public:
  static Call from_call_lParTkn_elist_rParTkn(const Call& call,
                                              const Elist& elist);

  static Call from_lvalue_callsuffix(const Callsuffix& callsuffix);

  static Call from_lParTkn_funcdef_rParTkn_lParTkn_elist_rParTkn(
      const Funcdef& funcdef,
      const Elist& elist);

 public:
  icode::Expr get_expr() const;
  void set_expr(const icode::Expr& expr);
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
