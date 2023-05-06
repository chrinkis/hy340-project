#include <alpha/syntax/manager/nonterminal/term.h>

#include <alpha/syntax/handler/symbol/function/error_checker.h>
#include <alpha/syntax/handler/symbol/symbol.h>
#include <alpha/syntax/manager/nonterminal/expr.h>
#include <alpha/syntax/manager/nonterminal/lvalue.h>
#include <alpha/syntax/manager/nonterminal/primary.h>

using namespace alpha::syntax::manager::nonterminal;

using alpha::syntax::handlers::symbol::continue_checking;
using alpha::syntax::handlers::symbol::function::check_for_errors;

Term Term::from_lParTkn_expr_rParTkn(const Expr& expr) {
  Term term;

  continue_checking(term, expr);

  return term;
}

Term Term::from_minusTkn_expr(const Expr& expr) {
  check_for_errors(expr, "unary \"-\" with");

  Term term;

  return term;
}

Term Term::from_notTkn_expr(const Expr& expr) {
  check_for_errors(expr, "\"NOT\" with");

  Term term;

  return term;
}

Term Term::from_plusPlusTkn_lvalue(const Lvalue& lvalue) {
  check_for_errors(lvalue, "\"++\" with");

  Term term;

  return term;
}

Term Term::from_lvalue_plusPlusTkn(const Lvalue& lvalue) {
  check_for_errors(lvalue, "\"++\" with");

  Term term;

  return term;
}

Term Term::from_minusMinusTkn_lvalue(const Lvalue& lvalue) {
  check_for_errors(lvalue, "\"--\" with");

  Term term;

  return term;
}

Term Term::from_lvalue_minusMinusTkn(const Lvalue& lvalue) {
  check_for_errors(lvalue, "\"--\" with");

  Term term;

  return term;
}

Term Term::from_primary(const Primary& primary) {
  Term term;

  continue_checking(term, primary);

  return term;
}
