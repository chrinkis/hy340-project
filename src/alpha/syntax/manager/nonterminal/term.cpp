#include <alpha/syntax/manager/nonterminal/term.h>

#include <alpha/icode/quad/table.h>
#include <alpha/symbol/table_manager.h>
#include <alpha/syntax/manager/nonterminal/expr.h>
#include <alpha/syntax/manager/nonterminal/lvalue.h>
#include <alpha/syntax/manager/nonterminal/primary.h>

#include <alpha/syntax/error.h>

using namespace alpha::syntax::manager::nonterminal;
using Opcode = alpha::icode::quad::Quad::Opcode;

Term Term::from_lParTkn_expr_rParTkn(const Expr& expr) {
  Term term;

  term.set_expr(expr.get_expr());

  return term;
}

Term Term::from_minusTkn_expr(const Expr& expr) {
  if (!error::is_arithmetic(expr.get_expr())) {
    error::illegal_arithm_expr(error::Operator::MINUS, expr.get_expr());
  }

  Term term;

  term.set_expr(icode::Expr::for_arithm_expr(symTable.new_temp_variable()));
  quadTable.emit(Opcode::UMINUS, term.get_expr(), expr.get_expr());

  return term;
}

Term Term::from_notTkn_expr(const Expr& expr) {
  Term term;

  term.set_expr(icode::Expr::for_bool_expr(symTable.new_temp_variable()));
  quadTable.emit(Opcode::NOT, term.get_expr(), expr.get_expr());

  return term;
}

Term Term::from_plusPlusTkn_lvalue(const Lvalue& lvalue) {
  if (!error::is_arithmetic(lvalue.get_expr())) {
    error::illegal_arithm_expr(error::Operator::PLUS_PLUS_POST,
                               lvalue.get_expr());
  }

  Term term;

  if (lvalue.get_expr().get_type() == icode::Expr::Type::TABLE_ITEM) {
    term.set_expr(quadTable.emit_if_table_item(lvalue.get_expr()));

    quadTable.emit(Opcode::ADD, term.get_expr(), term.get_expr(),
                   icode::Expr::for_const_num(1));

    quadTable.emit(Opcode::TABLESETELEM, term.get_expr(), lvalue.get_expr(),
                   *lvalue.get_expr().get_index());
  } else {
    quadTable.emit(Opcode::ADD, lvalue.get_expr(), lvalue.get_expr(),
                   icode::Expr::for_const_num(1));

    term.set_expr(icode::Expr::for_arithm_expr(symTable.new_temp_variable()));

    quadTable.emit(Opcode::ASSIGN, term.get_expr(), lvalue.get_expr());
  }

  return term;
}

Term Term::from_lvalue_plusPlusTkn(const Lvalue& lvalue) {
  if (!error::is_arithmetic(lvalue.get_expr())) {
    error::illegal_arithm_expr(error::Operator::PLUS_PLUS_PRE,
                               lvalue.get_expr());
  }

  Term term;

  term.set_expr(icode::Expr::for_var(symTable.new_temp_variable()));

  if (lvalue.get_expr().get_type() == icode::Expr::Type::TABLE_ITEM) {
    icode::Expr val = quadTable.emit_if_table_item(lvalue.get_expr());

    quadTable.emit(Opcode::ASSIGN, term.get_expr(), val);

    quadTable.emit(Opcode::ADD, val, val, icode::Expr::for_const_num(1));

    quadTable.emit(Opcode::TABLESETELEM, val, lvalue.get_expr(),
                   *lvalue.get_expr().get_index());
  } else {
    quadTable.emit(Opcode::ASSIGN, term.get_expr(), lvalue.get_expr());

    quadTable.emit(Opcode::ADD, lvalue.get_expr(), lvalue.get_expr(),
                   icode::Expr::for_const_num(1));
  }

  return term;
}

Term Term::from_minusMinusTkn_lvalue(const Lvalue& lvalue) {
  if (!error::is_arithmetic(lvalue.get_expr())) {
    error::illegal_arithm_expr(error::Operator::MINUS_MINUS_POST,
                               lvalue.get_expr());
  }

  Term term;

  if (lvalue.get_expr().get_type() == icode::Expr::Type::TABLE_ITEM) {
    term.set_expr(quadTable.emit_if_table_item(lvalue.get_expr()));

    quadTable.emit(Opcode::SUB, term.get_expr(), term.get_expr(),
                   icode::Expr::for_const_num(1));

    quadTable.emit(Opcode::TABLESETELEM, term.get_expr(), lvalue.get_expr(),
                   *lvalue.get_expr().get_index());
  } else {
    quadTable.emit(Opcode::SUB, lvalue.get_expr(), lvalue.get_expr(),
                   icode::Expr::for_const_num(1));

    term.set_expr(icode::Expr::for_arithm_expr(symTable.new_temp_variable()));

    quadTable.emit(Opcode::ASSIGN, term.get_expr(), lvalue.get_expr());
  }

  return term;
}

Term Term::from_lvalue_minusMinusTkn(const Lvalue& lvalue) {
  if (!error::is_arithmetic(lvalue.get_expr())) {
    error::illegal_arithm_expr(error::Operator::MINUS_MINUS_PRE,
                               lvalue.get_expr());
  }

  Term term;

  term.set_expr(icode::Expr::for_var(symTable.new_temp_variable()));

  if (lvalue.get_expr().get_type() == icode::Expr::Type::TABLE_ITEM) {
    icode::Expr val = quadTable.emit_if_table_item(lvalue.get_expr());

    quadTable.emit(Opcode::ASSIGN, term.get_expr(), val);

    quadTable.emit(Opcode::SUB, val, val, icode::Expr::for_const_num(1));

    quadTable.emit(Opcode::TABLESETELEM, val, lvalue.get_expr(),
                   *lvalue.get_expr().get_index());
  } else {
    quadTable.emit(Opcode::ASSIGN, term.get_expr(), lvalue.get_expr());

    quadTable.emit(Opcode::SUB, lvalue.get_expr(), lvalue.get_expr(),
                   icode::Expr::for_const_num(1));
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
