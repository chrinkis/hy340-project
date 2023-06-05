#pragma once

#include <alpha/lang/icode/expr.h>
#include <alpha/lang/syntax/manager/terminal/identifier.h>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class Member;

class Lvalue {
 private:
  using Identifier = terminal::Identifier;
  using Symbol = symbol::Symbol;

 private:
  icode::Expr expr;

 public:
  static Lvalue from_idTkn(const Identifier& identifier);

  static Lvalue from_localIdTkn(const Identifier& identifier);

  static Lvalue from_doubleColonTkn_localIdTkn(const Identifier& identifier);

  static Lvalue from_member(const Member& member);

 public:
  icode::Expr get_expr() const;
  void set_expr(const icode::Expr& expr);

 private:
  void set_expr_from_symbol(const Symbol::SharedPtr& symbol);
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
