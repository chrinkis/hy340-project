#include <alpha/syntax/manager/nonterminal/expr.h>

#include <alpha/icode/quad/table.h>
#include <alpha/symbol/table_manager.h>
#include <alpha/syntax/error.h>
#include <alpha/syntax/manager/nonterminal/assignexpr.h>
#include <alpha/syntax/manager/nonterminal/term.h>

#define HAVE_CONST_NUM_TYPE(expr1, expr2)                           \
  ((expr1.get_expr().get_type() == icode::Expr::Type::CONST_NUM) && \
   (expr2.get_expr().get_type() == icode::Expr::Type::CONST_NUM))

#define HAVE_CONST_BOOL_TYPE(expr1, expr2)                           \
  ((expr1.get_expr().get_type() == icode::Expr::Type::CONST_BOOL) && \
   (expr2.get_expr().get_type() == icode::Expr::Type::CONST_BOOL))

using namespace alpha::syntax::manager::nonterminal;
using Opcode = alpha::icode::quad::Quad::Opcode;

Expr Expr::from_assignexpr(const Assignexpr& assignexpr) {
  Expr expr;

  expr.set_expr(assignexpr.get_expr());

  return expr;
}

Expr Expr::from_expr_plusTkn_expr(const Expr& left, const Expr& right) {
  if (!error::is_arithmetic(left.get_expr())) {
    error::illegal_arithm_expr(error::Operator::PLUS, left.get_expr());
  }

  if (!error::is_arithmetic(right.get_expr())) {
    error::illegal_arithm_expr(error::Operator::PLUS, right.get_expr());
  }

  Expr expr;

  if (!HAVE_CONST_NUM_TYPE(left, right)) {
    expr.set_expr(icode::Expr::for_arithm_expr(symTable.new_temp_variable()));
    quadTable.emit(Opcode::ADD, expr.get_expr(), left.get_expr(),
                   right.get_expr());

  } else {
    double result = left.get_expr().get_number_const() +
                    right.get_expr().get_number_const();

    expr.set_expr(icode::Expr::for_const_num(result));
  }

  return expr;
}

Expr Expr::from_expr_minusTkn_expr(const Expr& left, const Expr& right) {
  if (!error::is_arithmetic(left.get_expr())) {
    error::illegal_arithm_expr(error::Operator::MINUS, left.get_expr());
  }

  if (!error::is_arithmetic(right.get_expr())) {
    error::illegal_arithm_expr(error::Operator::MINUS, right.get_expr());
  }

  Expr expr;

  if (!HAVE_CONST_NUM_TYPE(left, right)) {
    expr.set_expr(icode::Expr::for_arithm_expr(symTable.new_temp_variable()));
    quadTable.emit(Opcode::SUB, expr.get_expr(), left.get_expr(),
                   right.get_expr());

  } else {
    double result = left.get_expr().get_number_const() -
                    right.get_expr().get_number_const();

    expr.set_expr(icode::Expr::for_const_num(result));
  }

  return expr;
}

Expr Expr::from_expr_starTkn_expr(const Expr& left, const Expr& right) {
  if (!error::is_arithmetic(left.get_expr())) {
    error::illegal_arithm_expr(error::Operator::STAR, left.get_expr());
  }

  if (!error::is_arithmetic(right.get_expr())) {
    error::illegal_arithm_expr(error::Operator::STAR, right.get_expr());
  }

  Expr expr;

  if (!HAVE_CONST_NUM_TYPE(left, right)) {
    expr.set_expr(icode::Expr::for_arithm_expr(symTable.new_temp_variable()));
    quadTable.emit(Opcode::MUL, expr.get_expr(), left.get_expr(),
                   right.get_expr());

  } else {
    double result = left.get_expr().get_number_const() *
                    right.get_expr().get_number_const();

    expr.set_expr(icode::Expr::for_const_num(result));
  }

  return expr;
}

Expr Expr::from_expr_divTkn_expr(const Expr& left, const Expr& right) {
  if (!error::is_arithmetic(left.get_expr())) {
    error::illegal_arithm_expr(error::Operator::DIV, left.get_expr());
  }

  if (!error::is_arithmetic(right.get_expr())) {
    error::illegal_arithm_expr(error::Operator::DIV, right.get_expr());
  }

  Expr expr;

  if (!HAVE_CONST_NUM_TYPE(left, right)) {
    expr.set_expr(icode::Expr::for_arithm_expr(symTable.new_temp_variable()));
    quadTable.emit(Opcode::DIV, expr.get_expr(), left.get_expr(),
                   right.get_expr());

  } else {
    double result = left.get_expr().get_number_const() /
                    right.get_expr().get_number_const();

    expr.set_expr(icode::Expr::for_const_num(result));
  }

  return expr;
}

Expr Expr::from_expr_modTkn_expr(const Expr& left, const Expr& right) {
  if (!error::is_arithmetic(left.get_expr())) {
    error::illegal_arithm_expr(error::Operator::MOD, left.get_expr());
  }

  if (!error::is_arithmetic(right.get_expr())) {
    error::illegal_arithm_expr(error::Operator::MOD, right.get_expr());
  }

  Expr expr;

  if (!HAVE_CONST_NUM_TYPE(left, right)) {
    expr.set_expr(icode::Expr::for_arithm_expr(symTable.new_temp_variable()));
    quadTable.emit(Opcode::MOD, expr.get_expr(), left.get_expr(),
                   right.get_expr());

  } else {
    double result = ((int)left.get_expr().get_number_const()) %
                    ((int)right.get_expr().get_number_const());

    expr.set_expr(icode::Expr::for_const_num(result));
  }

  return expr;
}

Expr Expr::from_expr_greaterTkn_expr(const Expr& left, const Expr& right) {
  if (!error::is_arithmetic(left.get_expr())) {
    error::illegal_arithm_expr(error::Operator::GREATER, left.get_expr());
  }

  if (!error::is_arithmetic(right.get_expr())) {
    error::illegal_arithm_expr(error::Operator::GREATER, right.get_expr());
  }

  Expr expr;

  if (!HAVE_CONST_NUM_TYPE(left, right)) {
    expr.set_true_list_head(quadTable.get_next_label());
    quadTable.emit(Opcode::IF_GREATER, emptyExpr, left.get_expr(),
                   right.get_expr(), 0);

    expr.set_false_list_head(quadTable.get_next_label());
    quadTable.emit(Opcode::JUMP, emptyExpr, emptyExpr, emptyExpr, 0);

    expr.set_expr(icode::Expr::for_bool_expr());
  } else {
    bool result = left.get_expr().get_number_const() >
                  right.get_expr().get_number_const();

    expr.set_expr(icode::Expr::for_const_bool(result));
  }

  return expr;
}

Expr Expr::from_expr_greaterEqTkn_expr(const Expr& left, const Expr& right) {
  if (!error::is_arithmetic(left.get_expr())) {
    error::illegal_arithm_expr(error::Operator::GREATER_EQUAL, left.get_expr());
  }

  if (!error::is_arithmetic(right.get_expr())) {
    error::illegal_arithm_expr(error::Operator::GREATER_EQUAL,
                               right.get_expr());
  }

  Expr expr;

  if (!HAVE_CONST_NUM_TYPE(left, right)) {
    expr.set_true_list_head(quadTable.get_next_label());
    quadTable.emit(Opcode::IF_GREATEREQ, emptyExpr, left.get_expr(),
                   right.get_expr(), 0);

    expr.set_false_list_head(quadTable.get_next_label());
    quadTable.emit(Opcode::JUMP, emptyExpr, emptyExpr, emptyExpr, 0);

    expr.set_expr(icode::Expr::for_bool_expr());
  } else {
    bool result = left.get_expr().get_number_const() >=
                  right.get_expr().get_number_const();

    expr.set_expr(icode::Expr::for_const_bool(result));
  }

  return expr;
}

Expr Expr::from_expr_lessTkn_expr(const Expr& left, const Expr& right) {
  if (!error::is_arithmetic(left.get_expr())) {
    error::illegal_arithm_expr(error::Operator::LESS, left.get_expr());
  }

  if (!error::is_arithmetic(right.get_expr())) {
    error::illegal_arithm_expr(error::Operator::LESS, right.get_expr());
  }

  Expr expr;

  if (!HAVE_CONST_NUM_TYPE(left, right)) {
    expr.set_true_list_head(quadTable.get_next_label());
    quadTable.emit(Opcode::IF_LESS, emptyExpr, left.get_expr(),
                   right.get_expr(), 0);

    expr.set_false_list_head(quadTable.get_next_label());
    quadTable.emit(Opcode::JUMP, emptyExpr, emptyExpr, emptyExpr, 0);

    expr.set_expr(icode::Expr::for_bool_expr());
  } else {
    bool result = left.get_expr().get_number_const() <
                  right.get_expr().get_number_const();

    expr.set_expr(icode::Expr::for_const_bool(result));
  }

  return expr;
}

Expr Expr::from_expr_lessEqTkn_expr(const Expr& left, const Expr& right) {
  if (!error::is_arithmetic(left.get_expr())) {
    error::illegal_arithm_expr(error::Operator::LESS_EQUAL, left.get_expr());
  }

  if (!error::is_arithmetic(right.get_expr())) {
    error::illegal_arithm_expr(error::Operator::LESS_EQUAL, right.get_expr());
  }

  Expr expr;

  if (!HAVE_CONST_NUM_TYPE(left, right)) {
    expr.set_true_list_head(quadTable.get_next_label());
    quadTable.emit(Opcode::IF_LESSEQ, emptyExpr, left.get_expr(),
                   right.get_expr(), 0);

    expr.set_false_list_head(quadTable.get_next_label());
    quadTable.emit(Opcode::JUMP, emptyExpr, emptyExpr, emptyExpr, 0);

    expr.set_expr(icode::Expr::for_bool_expr());
  } else {
    bool result = left.get_expr().get_number_const() <=
                  right.get_expr().get_number_const();

    expr.set_expr(icode::Expr::for_const_bool(result));
  }

  return expr;
}

Expr Expr::from_expr_equalsTkn_expr(const Expr& left, const Expr& right) {
  Expr expr;

  expr.set_true_list_head(quadTable.get_next_label());
  quadTable.emit(Opcode::IF_EQ, emptyExpr, left.get_expr(), right.get_expr(),
                 0);

  expr.set_false_list_head(quadTable.get_next_label());
  quadTable.emit(Opcode::JUMP, emptyExpr, emptyExpr, emptyExpr, 0);

  expr.set_expr(icode::Expr::for_bool_expr());

  return expr;
}

Expr Expr::from_expr_notEqualsTkn_expr(const Expr& left, const Expr& right) {
  Expr expr;

  expr.set_true_list_head(quadTable.get_next_label());
  quadTable.emit(Opcode::IF_NOTEQ, emptyExpr, left.get_expr(), right.get_expr(),
                 0);

  expr.set_false_list_head(quadTable.get_next_label());
  quadTable.emit(Opcode::JUMP, emptyExpr, emptyExpr, emptyExpr, 0);

  expr.set_expr(icode::Expr::for_bool_expr());

  return expr;
}

Expr Expr::from_expr_andTkn_exprM_expr(const Expr& left,
                                       const ExprM& expr_m,
                                       const Expr& right) {
  Expr expr;

  if (!HAVE_CONST_BOOL_TYPE(left, right)) {
    quadTable.patch_list(left.true_list_head, expr_m.get_quad_label());
    expr.set_true_list_head(right.get_true_list_head());
    expr.set_false_list_head(quadTable.merge_lists(
        left.get_false_list_head(), right.get_false_list_head()));

    expr.set_expr(icode::Expr::for_bool_expr());
  } else {
    bool result =
        left.get_expr().get_bool_const() && right.get_expr().get_bool_const();

    expr.set_expr(icode::Expr::for_const_bool(result));
  }

  return expr;
}

Expr Expr::from_expr_orTkn_exprM_expr(const Expr& left,
                                      const ExprM& expr_m,
                                      const Expr& right) {
  Expr expr;

  if (!HAVE_CONST_BOOL_TYPE(left, right)) {
    quadTable.patch_list(left.false_list_head, expr_m.get_quad_label());
    expr.set_true_list_head(quadTable.merge_lists(left.get_true_list_head(),
                                                  right.get_true_list_head()));
    expr.set_false_list_head(right.false_list_head);
  } else {
    bool result =
        left.get_expr().get_bool_const() || right.get_expr().get_bool_const();

    expr.set_expr(icode::Expr::for_const_bool(result));
  }

  expr.set_expr(icode::Expr::for_bool_expr());

  return expr;
}

Expr Expr::from_term(const Term& term) {
  Expr expr;

  expr.set_expr(term.get_expr());
  expr.set_true_list_head(term.get_true_list_head());
  expr.set_false_list_head(term.get_false_list_head());

  return expr;
}

alpha::icode::Expr Expr::get_expr() const {
  return this->expr;
}

void Expr::set_expr(const icode::Expr& expr) {
  this->expr = expr;
}

Expr::QuadLabel Expr::get_true_list_head() const {
  return this->true_list_head;
}

void Expr::set_true_list_head(const QuadLabel& head) {
  this->true_list_head = head;
}

Expr::QuadLabel Expr::get_false_list_head() const {
  return this->false_list_head;
}

void Expr::set_false_list_head(const QuadLabel& head) {
  this->false_list_head = head;
}
