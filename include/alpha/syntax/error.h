#pragma once

#include <alpha/syntax/parser.h>

#include <alpha/icode/expr.h>
#include <string>
#include "alpha/symbol/symbol.h"

namespace alpha::syntax::error {

extern bool found;  // TODO find better solution

enum class Operator {
  ASSIGN,
  PLUS,
  MINUS,
  STAR,
  DIV,
  MOD,
  GREATER,
  GREATER_EQUAL,
  LESS,
  LESS_EQUAL,
  EQUAL,
  NOT_EQUAL,
  AND,
  OR,
  DOT,
  SQUARE_BRACKETS,
  UNARY_MINUS,
  NOT,
  PLUS_PLUS_PRE,     // ++foo
  PLUS_PLUS_POST,    // foo++
  MINUS_MINUS_PRE,   // --foo
  MINUS_MINUS_POST,  // foo--
};

void print(const std::string& message,
           const alpha::syntax::Parser::location_type& location);

void undefined_refference_to_global_var(
    const std::string& name,
    const alpha::syntax::Parser::location_type& location);

void inaccessible_refference_to_var(
    const std::string& name,
    const alpha::syntax::Parser::location_type& location);

void local_var_shadows_lib_function(
    const std::string& name,
    const alpha::syntax::Parser::location_type& location);

void invalid_argumnet_name(
    const std::string& name,
    const alpha::syntax::Parser::location_type& location);

void invalid_name_for_func_definition(
    const std::string& name,
    const alpha::syntax::Parser::location_type& location);

void invalid_function_operation(Operator op,
                                const alpha::symbol::Symbol::SharedPtr& symbol);

void invalid_use_of_break(const alpha::syntax::Parser::location_type& location);

void invalid_use_of_continue(
    const alpha::syntax::Parser::location_type& location);

void invalid_use_of_return(
    const alpha::syntax::Parser::location_type& location);

bool is_arithmetic(const icode::Expr& expr);

void illegal_arithm_expr(Operator op, const icode::Expr& expr);

}  // namespace alpha::syntax::error
