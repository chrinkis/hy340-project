#pragma once

#include <alpha/syntax/parser.h>

#include <string>
#include "alpha/symbol/symbol.h"

namespace alpha::syntax::error {

enum Type {
  UNDEFINED_REFFERENCE_TO_GLOBAL_VAR,
};

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

void print_semantic(const std::string& message,
                    const alpha::syntax::Parser::location_type& location);

void print_semantic(const std::string& message);

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

}  // namespace alpha::syntax::error
