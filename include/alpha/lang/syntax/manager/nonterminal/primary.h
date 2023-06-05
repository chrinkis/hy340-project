#pragma once

#include <alpha/lang/icode/expr.h>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class Lvalue;
class Funcdef;
class Call;
class Objectdef;
class Const;

class Primary {
 private:
  icode::Expr expr;

 public:
  static Primary from_lvalue(const Lvalue& lvalue);

  static Primary from_call(const Call& call);

  static Primary from_objectdef(const Objectdef& objectdef);

  static Primary from_lParTkn_funcdef_rParTkn(const Funcdef& funcdef);

  static Primary from_const(const Const& constant);

 public:
  icode::Expr get_expr() const;
  void set_expr(const icode::Expr& expr);
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
