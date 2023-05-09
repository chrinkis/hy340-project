#include <alpha/syntax/manager/nonterminal/term.h>

#include <alpha/syntax/manager/nonterminal/expr.h>
#include <alpha/syntax/manager/nonterminal/lvalue.h>
#include <alpha/syntax/manager/nonterminal/primary.h>

#include <alpha/syntax/error.h>

using namespace alpha::syntax::manager::nonterminal;

Term Term::from_lParTkn_expr_rParTkn(const Expr& expr) {
  Term term;

  term.set_symbol(expr.get_symbol());

  return term;
}

Term Term::from_minusTkn_expr(const Expr& expr) {
  if (expr.get_symbol() && expr.get_symbol().value()->has_function_type()) {
    error::invalid_function_operation(error::Operator::MINUS,
                                      expr.get_symbol().value());
  }

  Term term;

  return term;
}

Term Term::from_notTkn_expr(const Expr& expr) {
  if (expr.get_symbol() && expr.get_symbol().value()->has_function_type()) {
    error::invalid_function_operation(error::Operator::NOT,
                                      expr.get_symbol().value());
  }

  Term term;

  return term;
}

Term Term::from_plusPlusTkn_lvalue(const Lvalue& lvalue) {
  if (lvalue.get_symbol() && lvalue.get_symbol().value()->has_function_type()) {
    error::invalid_function_operation(error::Operator::PLUS_PLUS_PRE,
                                      lvalue.get_symbol().value());
  }

  Term term;

  return term;
}

Term Term::from_lvalue_plusPlusTkn(const Lvalue& lvalue) {
  if (lvalue.get_symbol() && lvalue.get_symbol().value()->has_function_type()) {
    error::invalid_function_operation(error::Operator::PLUS_PLUS_POST,
                                      lvalue.get_symbol().value());
  }

  Term term;

  return term;
}

Term Term::from_minusMinusTkn_lvalue(const Lvalue& lvalue) {
  if (lvalue.get_symbol() && lvalue.get_symbol().value()->has_function_type()) {
    error::invalid_function_operation(error::Operator::MINUS_MINUS_PRE,
                                      lvalue.get_symbol().value());
  }

  Term term;

  return term;
}

Term Term::from_lvalue_minusMinusTkn(const Lvalue& lvalue) {
  if (lvalue.get_symbol() && lvalue.get_symbol().value()->has_function_type()) {
    error::invalid_function_operation(error::Operator::MINUS_MINUS_POST,
                                      lvalue.get_symbol().value());
  }

  Term term;

  return term;
}

Term Term::from_primary(const Primary& primary) {
  Term term;

  term.set_symbol(primary.get_symbol());

  return term;
}
