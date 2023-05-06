#include <alpha/syntax/manager/nonterminal/expr.h>

#include <alpha/syntax/handler/symbol/function/error_checker.h>
#include <alpha/syntax/handler/symbol/symbol.h>
#include <alpha/syntax/manager/nonterminal/term.h>

using namespace alpha::syntax::manager::nonterminal;
namespace symbol_handler = alpha::syntax::handlers::symbol;
namespace function_handler = alpha::syntax::handlers::symbol::function;

Expr Expr::from_assignexpr() {
  Expr expr;

  return expr;
}

Expr Expr::from_expr_plusTkn_expr(const Expr& left, const Expr& right) {
  Expr expr;

  function_handler::check_for_errors(left, "\"+\" with");
  function_handler::check_for_errors(right, "\"+\" with");

  return expr;
}

Expr Expr::from_expr_minusTkn_expr(const Expr& left, const Expr& right) {
  Expr expr;

  function_handler::check_for_errors(left, "\"-\" with");
  function_handler::check_for_errors(right, "\"-\" with");

  return expr;
}

Expr Expr::from_expr_starTkn_expr(const Expr& left, const Expr& right) {
  Expr expr;

  function_handler::check_for_errors(left, "\"*\" with");
  function_handler::check_for_errors(right, "\"*\" with");

  return expr;
}

Expr Expr::from_expr_divTkn_expr(const Expr& left, const Expr& right) {
  Expr expr;

  function_handler::check_for_errors(left, "\"/\" with");
  function_handler::check_for_errors(right, "\"/\" with");

  return expr;
}

Expr Expr::from_expr_modTkn_expr(const Expr& left, const Expr& right) {
  Expr expr;

  function_handler::check_for_errors(left, "\"%\" with");
  function_handler::check_for_errors(right, "\"%\" with");

  return expr;
}

Expr Expr::from_expr_greaterTkn_expr(const Expr& left, const Expr& right) {
  Expr expr;

  function_handler::check_for_errors(left, "\">\" with");
  function_handler::check_for_errors(right, "\">\" with");

  return expr;
}

Expr Expr::from_expr_greaterEqTkn_expr(const Expr& left, const Expr& right) {
  Expr expr;

  function_handler::check_for_errors(left, "\">=\" with");
  function_handler::check_for_errors(right, "\">=\" with");

  return expr;
}

Expr Expr::from_expr_lessTkn_expr(const Expr& left, const Expr& right) {
  Expr expr;

  function_handler::check_for_errors(left, "\"<\" with");
  function_handler::check_for_errors(right, "\"<\" with");

  return expr;
}

Expr Expr::from_expr_lessEqTkn_expr(const Expr& left, const Expr& right) {
  Expr expr;

  function_handler::check_for_errors(left, "\"<=\" with");
  function_handler::check_for_errors(right, "\"<=\" with");

  return expr;
}

Expr Expr::from_expr_equalsTkn_expr(const Expr& left, const Expr& right) {
  Expr expr;

  function_handler::check_for_errors(left, "\"==\" with");
  function_handler::check_for_errors(right, "\"==\" with");

  return expr;
}

Expr Expr::from_expr_notEqualsTkn_expr(const Expr& left, const Expr& right) {
  Expr expr;

  function_handler::check_for_errors(left, "\"!=\" with");
  function_handler::check_for_errors(right, "\"!=\" with");

  return expr;
}

Expr Expr::from_expr_andTkn_expr(const Expr& left, const Expr& right) {
  Expr expr;

  function_handler::check_for_errors(left, "\"AND\" with");
  function_handler::check_for_errors(right, "\"AND\" with");

  return expr;
}

Expr Expr::from_expr_orTkn_expr(const Expr& left, const Expr& right) {
  Expr expr;

  function_handler::check_for_errors(left, "\"OR\" with");
  function_handler::check_for_errors(right, "\"OR\" with");

  return expr;
}

Expr Expr::from_term(const Term& term) {
  Expr expr;

  symbol_handler::continue_checking(expr, term);

  return expr;
}
