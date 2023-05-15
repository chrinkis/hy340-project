#include <alpha/icode/expr.h>

#include <assert.h>

namespace alpha::icode {

Expr Expr::for_program_func(const Symbol::SharedPtr& symbol) {
  assert(symbol->get_type() == Symbol::Type::USER_FUNCTION);

  Expr expr;

  expr.type = Type::PROGRAM_FUNC;
  expr.symbol = symbol;

  return expr;
}

Expr::Type Expr::get_type() const {
  return this->type;
}

bool Expr::has_symbol() const {
  return !!this->symbol;
}

Expr::Symbol::SharedPtr Expr::get_symbol() const {
  return this->symbol.value();
}

Expr::SharedPtr Expr::get_index() const {
  return this->index.value();
}

double Expr::get_number_const() const {
  return this->number_const.value();
}

std::string Expr::get_string_const() const {
  return this->string_const.value();
}

bool Expr::get_bool_const() const {
  return this->bool_const.value();
}

std::ostream& operator<<(std::ostream& os, const Expr& expr) {
  switch (expr.type) {
    case Expr::Type::VAR:
      // FIXME
      break;
    case Expr::Type::TABLE_ITEM:
      // FIXME
      break;
    case Expr::Type::PROGRAM_FUNC:
      os << expr.get_symbol()->get_name();
      break;
    case Expr::Type::LIBRARY_FUNC:
      os << expr.get_symbol()->get_name();
      // FIXME
      break;
    case Expr::Type::ARITHM_EXPR:
      // FIXME
      break;
    case Expr::Type::BOOL_EXPR:
      // FIXME
      break;
    case Expr::Type::ASSIGN_EXPR:
      // FIXME
      break;
    case Expr::Type::NEW_TABLE:
      // FIXME
      break;
    case Expr::Type::CONST_NUM:
      // FIXME
      break;
    case Expr::Type::CONST_BOOL:
      // FIXME
      break;
    case Expr::Type::CONST_STRING:
      // FIXME
      break;
    case Expr::Type::NIL:
      // FIXME
      break;
    default:
      assert(0);
  }

  return os;
}

}  // namespace alpha::icode
