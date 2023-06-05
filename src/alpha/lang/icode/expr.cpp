#include <alpha/lang/icode/expr.h>

#include <assert.h>

namespace alpha::icode {

Expr::Expr() : type(Type::_NO_TYPE) {}

Expr Expr::for_var(const Symbol::SharedPtr& symbol) {
  assert(symbol->get_type() == Symbol::Type::FORMAL ||
         symbol->get_type() == Symbol::Type::GLOBAL ||
         symbol->get_type() == Symbol::Type::LOCAL);

  Expr expr;

  expr.type = Type::VAR;
  expr.symbol = symbol;

  return expr;
}

Expr Expr::for_program_func(const Symbol::SharedPtr& symbol) {
  assert(symbol->get_type() == Symbol::Type::USER_FUNCTION);

  Expr expr;

  expr.type = Type::PROGRAM_FUNC;
  expr.symbol = symbol;

  return expr;
}

Expr Expr::for_library_func(const Symbol::SharedPtr& symbol) {
  assert(symbol->get_type() == Symbol::Type::LIBRARY_FUNCTION);

  Expr expr;

  expr.type = Type::LIBRARY_FUNC;
  expr.symbol = symbol;

  return expr;
}

Expr Expr::for_table_item(const Expr& symbol_expr, const Expr& index) {
  Expr expr;

  expr.type = Type::TABLE_ITEM;

  if (symbol_expr.has_symbol()) {
    expr.symbol = symbol_expr.get_symbol();
  }

  expr.index = std::optional<Expr::SharedPtr>(new Expr());
  (*expr.index.value()) = index;

  return expr;
}

Expr Expr::for_new_table(const Symbol::SharedPtr& symbol) {
  Expr expr;

  expr.type = Type::NEW_TABLE;
  expr.symbol = symbol;

  return expr;
}

Expr Expr::for_assign_expr(const Expr& other) {
  Expr expr;

  expr = other;
  expr.type = Type::ASSIGN_EXPR;

  return expr;
}

Expr Expr::for_assign_expr(const Symbol::SharedPtr& symbol) {
  Expr expr;

  expr.type = Type::ASSIGN_EXPR;
  expr.symbol = symbol;

  return expr;
}

Expr Expr::for_arithm_expr(const Symbol::SharedPtr& symbol) {
  Expr expr;

  expr.type = Type::ARITHM_EXPR;
  expr.symbol = symbol;

  return expr;
}

Expr Expr::for_bool_expr(const Symbol::SharedPtr& symbol) {
  Expr expr;

  expr.type = Type::BOOL_EXPR;
  expr.symbol = symbol;

  return expr;
}

Expr Expr::for_const_num(double number) {
  Expr expr;

  expr.type = Type::CONST_NUM;
  expr.number_const = number;

  return expr;
}

Expr Expr::for_const_bool(bool value) {
  Expr expr;

  expr.type = Type::CONST_BOOL;
  expr.bool_const = value;

  return expr;
}

Expr Expr::for_const_string(const std::string& string) {
  Expr expr;

  expr.type = Type::CONST_STRING;
  expr.string_const = string;

  return expr;
}

Expr Expr::for_nil() {
  Expr expr;

  expr.type = Type::NIL;

  return expr;
}

Expr::Type Expr::get_type() const {
  return this->type;
}

bool Expr::has_symbol() const {
  return !!this->symbol;
}

Expr::Symbol::SharedPtr Expr::get_symbol() const {
  assert(this->has_symbol());

  return this->symbol.value();
}

bool Expr::has_index() const {
  return !!this->index;
}

Expr::SharedPtr Expr::get_index() const {
  assert(this->has_index());

  return this->index.value();
}

bool Expr::has_number_const() const {
  return !!this->number_const;
}

double Expr::get_number_const() const {
  assert(this->has_number_const());

  return this->number_const.value();
}

bool Expr::has_string_const() const {
  return !!this->string_const;
}

std::string Expr::get_string_const() const {
  assert(this->has_string_const());

  return this->string_const.value();
}

bool Expr::has_bool_const() const {
  return !!this->bool_const;
}

bool Expr::get_bool_const() const {
  assert(this->has_bool_const());

  return this->bool_const.value();
}

std::ostream& operator<<(std::ostream& os, const Expr& expr) {
  switch (expr.type) {
    case Expr::Type::VAR:
    case Expr::Type::TABLE_ITEM:
    case Expr::Type::PROGRAM_FUNC:
    case Expr::Type::LIBRARY_FUNC:
    case Expr::Type::ARITHM_EXPR:
    case Expr::Type::BOOL_EXPR:
    case Expr::Type::ASSIGN_EXPR:
    case Expr::Type::NEW_TABLE:
      os << expr.get_symbol()->get_name();
      break;
    case Expr::Type::CONST_NUM:
      os << expr.get_number_const();
      break;
    case Expr::Type::CONST_BOOL:
      os << (expr.get_bool_const() ? "true" : "false");
      break;
    case Expr::Type::CONST_STRING:
      os << "\"" + expr.get_string_const() + "\"";
      break;
    case Expr::Type::NIL:
      os << "nil";
      break;
    case Expr::Type::_NO_TYPE:
      break;
    default:
      assert(0);
  }

  return os;
}

}  // namespace alpha::icode
