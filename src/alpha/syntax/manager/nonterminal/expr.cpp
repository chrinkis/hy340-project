#include <alpha/syntax/manager/nonterminal/expr.h>

#include <alpha/icode/quad/table.h>
#include <alpha/symbol/table_manager.h>
#include <alpha/syntax/error.h>
#include <alpha/syntax/manager/nonterminal/term.h>

using namespace alpha::syntax::manager::nonterminal;
using Opcode = alpha::icode::quad::Quad::Opcode;

Expr Expr::from_assignexpr() {
  Expr expr;

  return expr;
}

Expr Expr::from_expr_plusTkn_expr(const Expr& left, const Expr& right) {
  if (left.get_expr().has_symbol() &&
      left.get_expr().get_symbol()->has_function_type()) {
    error::invalid_function_operation(error::Operator::PLUS,
                                      left.get_expr().get_symbol());
  }

  if (right.get_expr().has_symbol() &&
      right.get_expr().get_symbol()->has_function_type()) {
    error::invalid_function_operation(error::Operator::PLUS,
                                      right.get_expr().get_symbol());
  }

  Expr expr;

  expr.set_expr(icode::Expr::for_arithm_expr(symTable.new_temp_variable()));
  quadTable.emit(Opcode::ADD, expr.get_expr(), left.get_expr(),
                 right.get_expr());

  return expr;
}

Expr Expr::from_expr_minusTkn_expr(const Expr& left, const Expr& right) {
  if (left.get_expr().has_symbol() &&
      left.get_expr().get_symbol()->has_function_type()) {
    error::invalid_function_operation(error::Operator::MINUS,
                                      left.get_expr().get_symbol());
  }

  if (right.get_expr().has_symbol() &&
      right.get_expr().get_symbol()->has_function_type()) {
    error::invalid_function_operation(error::Operator::MINUS,
                                      right.get_expr().get_symbol());
  }

  Expr expr;

  expr.set_expr(icode::Expr::for_arithm_expr(symTable.new_temp_variable()));
  quadTable.emit(Opcode::SUB, expr.get_expr(), left.get_expr(),
                 right.get_expr());

  return expr;
}

Expr Expr::from_expr_starTkn_expr(const Expr& left, const Expr& right) {
  if (left.get_expr().has_symbol() &&
      left.get_expr().get_symbol()->has_function_type()) {
    error::invalid_function_operation(error::Operator::STAR,
                                      left.get_expr().get_symbol());
  }

  if (right.get_expr().has_symbol() &&
      right.get_expr().get_symbol()->has_function_type()) {
    error::invalid_function_operation(error::Operator::STAR,
                                      right.get_expr().get_symbol());
  }

  Expr expr;

  expr.set_expr(icode::Expr::for_arithm_expr(symTable.new_temp_variable()));
  quadTable.emit(Opcode::MUL, expr.get_expr(), left.get_expr(),
                 right.get_expr());

  return expr;
}

Expr Expr::from_expr_divTkn_expr(const Expr& left, const Expr& right) {
  if (left.get_expr().has_symbol() &&
      left.get_expr().get_symbol()->has_function_type()) {
    error::invalid_function_operation(error::Operator::DIV,
                                      left.get_expr().get_symbol());
  }

  if (right.get_expr().has_symbol() &&
      right.get_expr().get_symbol()->has_function_type()) {
    error::invalid_function_operation(error::Operator::DIV,
                                      right.get_expr().get_symbol());
  }

  Expr expr;

  expr.set_expr(icode::Expr::for_arithm_expr(symTable.new_temp_variable()));
  quadTable.emit(Opcode::DIV, expr.get_expr(), left.get_expr(),
                 right.get_expr());

  return expr;
}

Expr Expr::from_expr_modTkn_expr(const Expr& left, const Expr& right) {
  if (left.get_expr().has_symbol() &&
      left.get_expr().get_symbol()->has_function_type()) {
    error::invalid_function_operation(error::Operator::MOD,
                                      left.get_expr().get_symbol());
  }

  if (right.get_expr().has_symbol() &&
      right.get_expr().get_symbol()->has_function_type()) {
    error::invalid_function_operation(error::Operator::MOD,
                                      right.get_expr().get_symbol());
  }

  Expr expr;

  expr.set_expr(icode::Expr::for_arithm_expr(symTable.new_temp_variable()));
  quadTable.emit(Opcode::MOD, expr.get_expr(), left.get_expr(),
                 right.get_expr());

  return expr;
}

Expr Expr::from_expr_greaterTkn_expr(const Expr& left, const Expr& right) {
  if (left.get_expr().has_symbol() &&
      left.get_expr().get_symbol()->has_function_type()) {
    error::invalid_function_operation(error::Operator::GREATER,
                                      left.get_expr().get_symbol());
  }

  if (right.get_expr().has_symbol() &&
      right.get_expr().get_symbol()->has_function_type()) {
    error::invalid_function_operation(error::Operator::GREATER,
                                      right.get_expr().get_symbol());
  }

  Expr expr;

  expr.set_expr(icode::Expr::for_bool_expr(symTable.new_temp_variable()));
  quadTable.emit(Opcode::IF_GREATER, emptyExpr, left.get_expr(),
                 right.get_expr(), quadTable.get_next_label() + 3);

  quadTable.emit(Opcode::ASSIGN, expr.get_expr(),
                 icode::Expr::for_const_bool(false));

  quadTable.emit(Opcode::JUMP, emptyExpr, emptyExpr, emptyExpr,
                 quadTable.get_next_label() + 2);

  quadTable.emit(Opcode::ASSIGN, expr.get_expr(),
                 icode::Expr::for_const_bool(true));

  return expr;
}

Expr Expr::from_expr_greaterEqTkn_expr(const Expr& left, const Expr& right) {
  if (left.get_expr().has_symbol() &&
      left.get_expr().get_symbol()->has_function_type()) {
    error::invalid_function_operation(error::Operator::GREATER_EQUAL,
                                      left.get_expr().get_symbol());
  }

  if (right.get_expr().has_symbol() &&
      right.get_expr().get_symbol()->has_function_type()) {
    error::invalid_function_operation(error::Operator::GREATER_EQUAL,
                                      right.get_expr().get_symbol());
  }

  Expr expr;

  expr.set_expr(icode::Expr::for_bool_expr(symTable.new_temp_variable()));
  quadTable.emit(Opcode::IF_GREATEREQ, emptyExpr, left.get_expr(),
                 right.get_expr(), quadTable.get_next_label() + 3);

  quadTable.emit(Opcode::ASSIGN, expr.get_expr(),
                 icode::Expr::for_const_bool(false));

  quadTable.emit(Opcode::JUMP, emptyExpr, emptyExpr, emptyExpr,
                 quadTable.get_next_label() + 2);

  quadTable.emit(Opcode::ASSIGN, expr.get_expr(),
                 icode::Expr::for_const_bool(true));

  return expr;
}

Expr Expr::from_expr_lessTkn_expr(const Expr& left, const Expr& right) {
  if (left.get_expr().has_symbol() &&
      left.get_expr().get_symbol()->has_function_type()) {
    error::invalid_function_operation(error::Operator::LESS,
                                      left.get_expr().get_symbol());
  }

  if (right.get_expr().has_symbol() &&
      right.get_expr().get_symbol()->has_function_type()) {
    error::invalid_function_operation(error::Operator::LESS,
                                      right.get_expr().get_symbol());
  }

  Expr expr;

  expr.set_expr(icode::Expr::for_bool_expr(symTable.new_temp_variable()));
  quadTable.emit(Opcode::IF_LESS, emptyExpr, left.get_expr(), right.get_expr(),
                 quadTable.get_next_label() + 3);

  quadTable.emit(Opcode::ASSIGN, expr.get_expr(),
                 icode::Expr::for_const_bool(false));

  quadTable.emit(Opcode::JUMP, emptyExpr, emptyExpr, emptyExpr,
                 quadTable.get_next_label() + 2);

  quadTable.emit(Opcode::ASSIGN, expr.get_expr(),
                 icode::Expr::for_const_bool(true));

  return expr;
}

Expr Expr::from_expr_lessEqTkn_expr(const Expr& left, const Expr& right) {
  if (left.get_expr().has_symbol() &&
      left.get_expr().get_symbol()->has_function_type()) {
    error::invalid_function_operation(error::Operator::LESS_EQUAL,
                                      left.get_expr().get_symbol());
  }

  if (right.get_expr().has_symbol() &&
      right.get_expr().get_symbol()->has_function_type()) {
    error::invalid_function_operation(error::Operator::LESS_EQUAL,
                                      right.get_expr().get_symbol());
  }

  Expr expr;

  expr.set_expr(icode::Expr::for_bool_expr(symTable.new_temp_variable()));
  quadTable.emit(Opcode::IF_LESSEQ, emptyExpr, left.get_expr(),
                 right.get_expr(), quadTable.get_next_label() + 3);

  quadTable.emit(Opcode::ASSIGN, expr.get_expr(),
                 icode::Expr::for_const_bool(false));

  quadTable.emit(Opcode::JUMP, emptyExpr, emptyExpr, emptyExpr,
                 quadTable.get_next_label() + 2);

  quadTable.emit(Opcode::ASSIGN, expr.get_expr(),
                 icode::Expr::for_const_bool(true));

  return expr;
}

Expr Expr::from_expr_equalsTkn_expr(const Expr& left, const Expr& right) {
  if (left.get_expr().has_symbol() &&
      left.get_expr().get_symbol()->has_function_type()) {
    error::invalid_function_operation(error::Operator::EQUAL,
                                      left.get_expr().get_symbol());
  }

  if (right.get_expr().has_symbol() &&
      right.get_expr().get_symbol()->has_function_type()) {
    error::invalid_function_operation(error::Operator::EQUAL,
                                      right.get_expr().get_symbol());
  }

  Expr expr;

  expr.set_expr(icode::Expr::for_bool_expr(symTable.new_temp_variable()));
  quadTable.emit(Opcode::IF_EQ, emptyExpr, left.get_expr(), right.get_expr(),
                 quadTable.get_next_label() + 3);

  quadTable.emit(Opcode::ASSIGN, expr.get_expr(),
                 icode::Expr::for_const_bool(false));

  quadTable.emit(Opcode::JUMP, emptyExpr, emptyExpr, emptyExpr,
                 quadTable.get_next_label() + 2);

  quadTable.emit(Opcode::ASSIGN, expr.get_expr(),
                 icode::Expr::for_const_bool(true));

  return expr;
}

Expr Expr::from_expr_notEqualsTkn_expr(const Expr& left, const Expr& right) {
  if (left.get_expr().has_symbol() &&
      left.get_expr().get_symbol()->has_function_type()) {
    error::invalid_function_operation(error::Operator::NOT_EQUAL,
                                      left.get_expr().get_symbol());
  }

  if (right.get_expr().has_symbol() &&
      right.get_expr().get_symbol()->has_function_type()) {
    error::invalid_function_operation(error::Operator::NOT_EQUAL,
                                      right.get_expr().get_symbol());
  }

  Expr expr;

  expr.set_expr(icode::Expr::for_bool_expr(symTable.new_temp_variable()));
  quadTable.emit(Opcode::IF_NOTEQ, emptyExpr, left.get_expr(), right.get_expr(),
                 quadTable.get_next_label() + 3);

  quadTable.emit(Opcode::ASSIGN, expr.get_expr(),
                 icode::Expr::for_const_bool(false));

  quadTable.emit(Opcode::JUMP, emptyExpr, emptyExpr, emptyExpr,
                 quadTable.get_next_label() + 2);

  quadTable.emit(Opcode::ASSIGN, expr.get_expr(),
                 icode::Expr::for_const_bool(true));

  return expr;
}

Expr Expr::from_expr_andTkn_expr(const Expr& left, const Expr& right) {
  if (left.get_expr().has_symbol() &&
      left.get_expr().get_symbol()->has_function_type()) {
    error::invalid_function_operation(error::Operator::AND,
                                      left.get_expr().get_symbol());
  }

  if (right.get_expr().has_symbol() &&
      right.get_expr().get_symbol()->has_function_type()) {
    error::invalid_function_operation(error::Operator::AND,
                                      right.get_expr().get_symbol());
  }

  Expr expr;

  expr.set_expr(icode::Expr::for_bool_expr(symTable.new_temp_variable()));
  quadTable.emit(Opcode::AND, expr.get_expr(), left.get_expr(),
                 right.get_expr());

  return expr;
}

Expr Expr::from_expr_orTkn_expr(const Expr& left, const Expr& right) {
  if (left.get_expr().has_symbol() &&
      left.get_expr().get_symbol()->has_function_type()) {
    error::invalid_function_operation(error::Operator::OR,
                                      left.get_expr().get_symbol());
  }

  if (right.get_expr().has_symbol() &&
      right.get_expr().get_symbol()->has_function_type()) {
    error::invalid_function_operation(error::Operator::OR,
                                      right.get_expr().get_symbol());
  }

  Expr expr;

  expr.set_expr(icode::Expr::for_bool_expr(symTable.new_temp_variable()));
  quadTable.emit(Opcode::OR, expr.get_expr(), left.get_expr(),
                 right.get_expr());

  return expr;
}

Expr Expr::from_term(const Term& term) {
  Expr expr;

  expr.set_expr(term.get_expr());

  return expr;
}

alpha::icode::Expr Expr::get_expr() const {
  return this->expr;
}

void Expr::set_expr(const icode::Expr& expr) {
  this->expr = expr;
}
