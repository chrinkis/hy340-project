#include <alpha/syntax/manager/nonterminal/const.h>

using namespace alpha::syntax::manager::nonterminal;

Const Const::from_integerTkn(const int i) {
  Const const_returning;

  icode::Expr icode_expr = icode::Expr::for_const_num(i);

  const_returning.set_expr(icode_expr);

  return const_returning;
}

Const Const::from_floatTkn(const double f) {
  Const const_returning;

  icode::Expr icode_expr = icode::Expr::for_const_num(f);

  const_returning.set_expr(icode_expr);

  return const_returning;
}

Const Const::from_stringTkn(const std::string s) {
  Const const_returning;

  icode::Expr icode_expr = icode::Expr::for_const_string(s);

  const_returning.set_expr(icode_expr);

  return const_returning;
}

Const Const::from_nilTkn() {
  Const const_returning;

  icode::Expr icode_expr = icode::Expr::for_nil();

  const_returning.set_expr(icode_expr);

  return const_returning;
}

Const Const::from_trueTkn() {
  Const const_returning;

  icode::Expr icode_expr = icode::Expr::for_const_bool(true);

  const_returning.set_expr(icode_expr);

  return const_returning;
}

Const Const::from_falseTkn() {
  Const const_returning;

  icode::Expr icode_expr = icode::Expr::for_const_bool(false);

  const_returning.set_expr(icode_expr);

  return const_returning;
}

alpha::icode::Expr Const::get_expr() const {
  return this->expr;
}

void Const::set_expr(const icode::Expr& expr) {
  this->expr = expr;
}
