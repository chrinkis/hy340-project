#include <alpha/lang/syntax/error.h>

#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

#define ERROR_COLOR "\033[31m"
#define DEFAULT_COLOR "\033[0m"

namespace alpha::syntax::error {

bool found = false;  // TODO find better solution

static std::string to_string(Operator op);

void print(const std::string& message,
           const alpha::syntax::Parser::location_type& location) {
  std::cerr << ERROR_COLOR << message << " at ("
            << "line: " << location.begin.line
            << ", column: " << location.begin.column << ")" << std::endl
            << DEFAULT_COLOR;

  found = true;
}

static void print_semantic(
    const std::string& message,
    const alpha::syntax::Parser::location_type& location) {
  std::cerr << ERROR_COLOR << "semantic error, " << message << " at ("
            << "line: " << location.begin.line
            << ", column: " << location.begin.column << ")" << std::endl
            << DEFAULT_COLOR;

  found = true;
}

static void print_semantic(const std::string& message) {
  std::cerr << ERROR_COLOR << "semantic error, " << message << std::endl
            << DEFAULT_COLOR;

  found = true;
}

void undefined_refference_to_global_var(
    const std::string& name,
    const alpha::syntax::Parser::location_type& location) {
  error::print_semantic(
      "undefined refference to global variable/function `" + name + "`",
      location);
}

void inaccessible_refference_to_var(
    const std::string& name,
    const alpha::syntax::Parser::location_type& location) {
  error::print_semantic("can not access variable/function `" + name + "`",
                        location);
}

void local_var_shadows_lib_function(
    const std::string& name,
    const alpha::syntax::Parser::location_type& location) {
  error::print_semantic(
      "can not define local variable with the libray function `" + name + "`",
      location);
}

void invalid_argumnet_name(
    const std::string& name,
    const alpha::syntax::Parser::location_type& location) {
  error::print_semantic("invalid argument name `" + name + "`", location);
}

void invalid_name_for_func_definition(
    const std::string& name,
    const alpha::syntax::Parser::location_type& location) {
  error::print_semantic("invalid name `" + name + "` for function definition",
                        location);
}

void invalid_function_operation(
    Operator op,
    const alpha::symbol::Symbol::SharedPtr& symbol) {
  print_semantic("cannot perform `" + to_string(op) + "` with function `" +
                 symbol->get_name() + "` as operand");
}

static std::string to_string(Operator op) {
  switch (op) {
    case Operator::ASSIGN:
      return "=";
    case Operator::PLUS:
      return "+";
    case Operator::MINUS:
      return "-";
    case Operator::STAR:
      return "*";
    case Operator::DIV:
      return "/";
    case Operator::MOD:
      return "%";
    case Operator::GREATER:
      return ">";
    case Operator::GREATER_EQUAL:
      return ">=";
    case Operator::LESS:
      return "<";
    case Operator::LESS_EQUAL:
      return "<=";
    case Operator::EQUAL:
      return "==";
    case Operator::NOT_EQUAL:
      return "!=";
    case Operator::AND:
      return "and";
    case Operator::OR:
      return "or";
    case Operator::DOT:
      return ".";
    case Operator::SQUARE_BRACKETS:
      return "[]";
    case Operator::UNARY_MINUS:
      return "-";
    case Operator::NOT:
      return "not";
    case Operator::PLUS_PLUS_PRE:
      return "++ (pre)";
    case Operator::PLUS_PLUS_POST:
      return "++ (post)";
    case Operator::MINUS_MINUS_PRE:
      return "-- (pre)";
    case Operator::MINUS_MINUS_POST:
      return "-- (post)";
    default:
      assert(0);
      return "";
  }
}

void invalid_use_of_break(
    const alpha::syntax::Parser::location_type& location) {
  error::print_semantic("invalid use of `break` statement", location);
}

void invalid_use_of_continue(
    const alpha::syntax::Parser::location_type& location) {
  error::print_semantic("invalid use of `continue` statement", location);
}

void invalid_use_of_return(
    const alpha::syntax::Parser::location_type& location) {
  error::print_semantic("invalid use of `return` statement", location);
}

bool is_arithmetic(const icode::Expr& expr) {
  switch (expr.get_type()) {
    case icode::Expr::Type::VAR:
    case icode::Expr::Type::TABLE_ITEM:
    case icode::Expr::Type::ARITHM_EXPR:
    case icode::Expr::Type::ASSIGN_EXPR:
    case icode::Expr::Type::CONST_NUM:
    case icode::Expr::Type::_NO_TYPE:
      return true;
    case icode::Expr::Type::PROGRAM_FUNC:
    case icode::Expr::Type::LIBRARY_FUNC:
    case icode::Expr::Type::BOOL_EXPR:
    case icode::Expr::Type::NEW_TABLE:
    case icode::Expr::Type::CONST_BOOL:
    case icode::Expr::Type::CONST_STRING:
    case icode::Expr::Type::NIL:
      return false;
    default:
      assert(0);
      return false;
  }
}

void illegal_arithm_expr(Operator op, const icode::Expr& expr) {
  std::stringstream expr_sstream;
  expr_sstream << expr;

  print_semantic("cannot use `" + to_string(op) + "` with `" +
                 expr_sstream.str() + "` as operand");
}

void illegal_arithm_expr_right_operand(Operator op, const icode::Expr& expr) {
  std::stringstream expr_sstream;
  expr_sstream << expr;

  print_semantic("cannot use `" + to_string(op) + "` with `" +
                 expr_sstream.str() + "` as right operand");
}

}  // namespace alpha::syntax::error
