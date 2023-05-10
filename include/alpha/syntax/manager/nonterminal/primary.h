#pragma once

#include <alpha/icode/expr.h>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class Lvalue;
class Funcdef;

class Primary {
 private:
  icode::Expr expr;

 public:
  static Primary from_lvalue(const Lvalue& lvalue);

  static Primary from_call();

  static Primary from_objectdef();

  static Primary from_lParTkn_funcdef_rParTkn(const Funcdef& funcdef);

  static Primary from_const();

 public:
  icode::Expr get_expr() const;
  void set_expr(const icode::Expr& expr);
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
