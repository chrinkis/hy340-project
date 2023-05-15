#include <alpha/syntax/manager/nonterminal/term.h>

#include <alpha/syntax/manager/nonterminal/expr.h>
#include <alpha/syntax/manager/nonterminal/lvalue.h>
#include <alpha/syntax/manager/nonterminal/primary.h>

#include <alpha/syntax/error.h>

using namespace alpha::syntax::manager::nonterminal;

Term Term::from_lParTkn_expr_rParTkn(const Expr& expr) {
  Term term;

  term.set_expr(expr.get_expr());

  return term;
}

Term Term::from_minusTkn_expr(const Expr& expr) {
  if (expr.get_expr().has_symbol() &&
      expr.get_expr().get_symbol()->has_function_type()) {
    error::invalid_function_operation(error::Operator::MINUS,
                                      expr.get_expr().get_symbol());
  }

  Term term;

  return term;
}

Term Term::from_notTkn_expr(const Expr& expr) {
  if (expr.get_expr().has_symbol() &&
      expr.get_expr().get_symbol()->has_function_type()) {
    error::invalid_function_operation(error::Operator::NOT,
                                      expr.get_expr().get_symbol());
  }

  Term term;

  return term;
}

Term Term::from_plusPlusTkn_lvalue(const Lvalue& lvalue) {
  if (lvalue.get_expr().has_symbol() &&
      lvalue.get_expr().get_symbol()->has_function_type()) {
    error::invalid_function_operation(error::Operator::PLUS_PLUS_PRE,
                                      lvalue.get_expr().get_symbol());
  }

  Term term;

  return term;
}

Term Term::from_lvalue_plusPlusTkn(const Lvalue& lvalue) {
  if (lvalue.get_expr().has_symbol() &&
      lvalue.get_expr().get_symbol()->has_function_type()) {
    error::invalid_function_operation(error::Operator::PLUS_PLUS_POST,
                                      lvalue.get_expr().get_symbol());
  }

  Term term;

  return term;
}

Term Term::from_minusMinusTkn_lvalue(const Lvalue& lvalue) {
  if (lvalue.get_expr().has_symbol() &&
      lvalue.get_expr().get_symbol()->has_function_type()) {
    error::invalid_function_operation(error::Operator::MINUS_MINUS_PRE,
                                      lvalue.get_expr().get_symbol());
  }

  Term term;

  return term;
}

Term Term::from_lvalue_minusMinusTkn(const Lvalue& lvalue) {
  if (lvalue.get_expr().has_symbol() &&
      lvalue.get_expr().get_symbol()->has_function_type()) {
    error::invalid_function_operation(error::Operator::MINUS_MINUS_POST,
                                      lvalue.get_expr().get_symbol());
  }

  Term term;

  return term;
}

Term Term::from_primary(const Primary& primary) {
  Term term;

  term.set_expr(primary.get_expr());

  return term;
}
