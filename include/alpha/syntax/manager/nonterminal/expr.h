#pragma once

#include <alpha/syntax/holder/Symbol.h>
#include <alpha/syntax/parser.h>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class Expr;
class Term;

class Expr : public holder::Symbol {
 public:
  static Expr from_assignexpr();

  static Expr from_expr_plusTkn_expr(const Expr& left, const Expr& right);

  static Expr from_expr_minusTkn_expr(const Expr& left, const Expr& right);

  static Expr from_expr_starTkn_expr(const Expr& left, const Expr& right);

  static Expr from_expr_divTkn_expr(const Expr& left, const Expr& right);

  static Expr from_expr_modTkn_expr(const Expr& left, const Expr& right);

  static Expr from_expr_greaterTkn_expr(const Expr& left, const Expr& right);

  static Expr from_expr_greaterEqTkn_expr(const Expr& left, const Expr& right);

  static Expr from_expr_lessTkn_expr(const Expr& left, const Expr& right);

  static Expr from_expr_lessEqTkn_expr(const Expr& left, const Expr& right);

  static Expr from_expr_equalsTkn_expr(const Expr& left, const Expr& right);

  static Expr from_expr_notEqualsTkn_expr(const Expr& left, const Expr& right);

  static Expr from_expr_andTkn_expr(const Expr& left, const Expr& right);

  static Expr from_expr_orTkn_expr(const Expr& left, const Expr& right);

  static Expr from_term(const Term& term);

 public:
  SearchResult get_result() const;
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
