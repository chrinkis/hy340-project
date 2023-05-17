#include <alpha/syntax/manager/nonterminal/term.h>

#include <alpha/icode/quad/table.h>
#include <alpha/symbol/table_manager.h>
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

  term.set_expr(icode::Expr::for_arithm_expr(symTable.new_temp_variable()));
  quadTable.emit_uminus(term.get_expr(), expr.get_expr());

  return term;
}

Term Term::from_notTkn_expr(const Expr& expr) {
  if (expr.get_expr().has_symbol() &&
      expr.get_expr().get_symbol()->has_function_type()) {
    error::invalid_function_operation(error::Operator::NOT,
                                      expr.get_expr().get_symbol());
  }

  Term term;

  term.set_expr(icode::Expr::for_bool_expr(symTable.new_temp_variable()));
  quadTable.emit_not(term.get_expr(), expr.get_expr());

  return term;
}

Term Term::from_plusPlusTkn_lvalue(const Lvalue& lvalue) {
  if (lvalue.get_expr().has_symbol() &&
      lvalue.get_expr().get_symbol()->has_function_type()) {
    error::invalid_function_operation(error::Operator::PLUS_PLUS_PRE,
                                      lvalue.get_expr().get_symbol());
  }

  Term term;

  term.set_expr(icode::Expr::for_var(symTable.new_temp_variable()));

  if (lvalue.get_expr().get_type() == icode::Expr::Type::TABLE_ITEM) {
    icode::Expr val = quadTable.emit_if_table_item(lvalue.get_expr());

    quadTable.emit_assign(term.get_expr(), val);

    quadTable.emit_add(val, icode::Expr::for_const_num(1), val);

    quadTable.emit_tablesetelem(lvalue.get_expr(),
                                *lvalue.get_expr().get_index(), val);
  } else {
    quadTable.emit_assign(term.get_expr(), lvalue.get_expr());

    quadTable.emit_add(lvalue.get_expr(), icode::Expr::for_const_num(1),
                       lvalue.get_expr());
  }

  return term;
}

Term Term::from_lvalue_plusPlusTkn(const Lvalue& lvalue) {
  if (lvalue.get_expr().has_symbol() &&
      lvalue.get_expr().get_symbol()->has_function_type()) {
    error::invalid_function_operation(error::Operator::PLUS_PLUS_POST,
                                      lvalue.get_expr().get_symbol());
  }

  Term term;

  if (lvalue.get_expr().get_type() == icode::Expr::Type::TABLE_ITEM) {
    term.set_expr(quadTable.emit_if_table_item(lvalue.get_expr()));

    quadTable.emit_add(term.get_expr(), icode::Expr::for_const_num(1),
                       term.get_expr());

    quadTable.emit_tablesetelem(
        lvalue.get_expr(), *lvalue.get_expr().get_index(), term.get_expr());
  } else {
    quadTable.emit_add(lvalue.get_expr(), icode::Expr::for_const_num(1),
                       lvalue.get_expr());

    term.set_expr(icode::Expr::for_arithm_expr(symTable.new_temp_variable()));

    quadTable.emit_assign(term.get_expr(), lvalue.get_expr());
  }

  return term;
}

Term Term::from_minusMinusTkn_lvalue(const Lvalue& lvalue) {
  if (lvalue.get_expr().has_symbol() &&
      lvalue.get_expr().get_symbol()->has_function_type()) {
    error::invalid_function_operation(error::Operator::MINUS_MINUS_PRE,
                                      lvalue.get_expr().get_symbol());
  }

  Term term;

  term.set_expr(icode::Expr::for_var(symTable.new_temp_variable()));

  if (lvalue.get_expr().get_type() == icode::Expr::Type::TABLE_ITEM) {
    icode::Expr val = quadTable.emit_if_table_item(lvalue.get_expr());

    quadTable.emit_assign(term.get_expr(), val);

    quadTable.emit_sub(val, icode::Expr::for_const_num(1), val);

    quadTable.emit_tablesetelem(lvalue.get_expr(),
                                *lvalue.get_expr().get_index(), val);
  } else {
    quadTable.emit_assign(term.get_expr(), lvalue.get_expr());

    quadTable.emit_sub(lvalue.get_expr(), icode::Expr::for_const_num(1),
                       lvalue.get_expr());
  }

  return term;
}

Term Term::from_lvalue_minusMinusTkn(const Lvalue& lvalue) {
  if (lvalue.get_expr().has_symbol() &&
      lvalue.get_expr().get_symbol()->has_function_type()) {
    error::invalid_function_operation(error::Operator::MINUS_MINUS_POST,
                                      lvalue.get_expr().get_symbol());
  }

  Term term;

  if (lvalue.get_expr().get_type() == icode::Expr::Type::TABLE_ITEM) {
    term.set_expr(quadTable.emit_if_table_item(lvalue.get_expr()));

    quadTable.emit_sub(term.get_expr(), icode::Expr::for_const_num(1),
                       term.get_expr());

    quadTable.emit_tablesetelem(
        lvalue.get_expr(), *lvalue.get_expr().get_index(), term.get_expr());
  } else {
    quadTable.emit_sub(lvalue.get_expr(), icode::Expr::for_const_num(1),
                       lvalue.get_expr());

    term.set_expr(icode::Expr::for_arithm_expr(symTable.new_temp_variable()));

    quadTable.emit_assign(term.get_expr(), lvalue.get_expr());
  }

  return term;
}

Term Term::from_primary(const Primary& primary) {
  Term term;

  term.set_expr(primary.get_expr());

  return term;
}

alpha::icode::Expr Term::get_expr() const {
  return this->expr;
}

void Term::set_expr(const icode::Expr& expr) {
  this->expr = expr;
}
