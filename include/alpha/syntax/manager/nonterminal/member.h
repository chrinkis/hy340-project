#pragma once

#include <alpha/icode/expr.h>
#include <alpha/syntax/manager/terminal/identifier.h>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class Call;
class Expr;
class Lvalue;

class Member {
 public:
  using Identifier = terminal::Identifier;

 private:
  icode::Expr expr;

 public:
  static Member from_lvalue_dotTkn_idTkn(const Lvalue& lvalue,
                                         const Identifier& id);

  static Member from_lvalue_lSqrBrackTkn_expr_rSqrtBrackTkn(
      const Lvalue& lvalue,
      const Expr& expr);

  static Member from_call_dotTkn_idTkn(const Call& call, const Identifier& id);

  static Member from_call_lSqrBrackTkn_expr_rSqrtBrackTkn(const Call& call,
                                                          const Expr& expr);

 public:
  icode::Expr get_expr() const;
  void set_expr(const icode::Expr& expr);
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
