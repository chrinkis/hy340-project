#pragma once

#include <alpha/icode/expr.h>
#include <alpha/syntax/manager/terminal/identifier.h>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class Lvalue {
 private:
  using Identifier = terminal::Identifier;

 private:
  icode::Expr expr;

 public:
  static Lvalue from_idTkn(const Identifier& identifier);

  static Lvalue from_localIdTkn(const Identifier& identifier);

  static Lvalue from_doubleColonTkn_localIdTkn(const Identifier& identifier);

  static Lvalue from_member();

 public:
  icode::Expr get_expr() const;
  void set_expr(const icode::Expr& expr);
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
