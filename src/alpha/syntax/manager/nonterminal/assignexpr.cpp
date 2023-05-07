#include <alpha/syntax/manager/nonterminal/assignexpr.h>

#include <alpha/syntax/error.h>
#include <alpha/syntax/manager/nonterminal/lvalue.h>

using namespace alpha::syntax::manager::nonterminal;

Assignexpr Assignexpr::from_lvalue_assignTkn_expr(const Lvalue& lvalue) {
  if (lvalue.get_symbol() && lvalue.get_symbol().value()->has_function_type()) {
    error::print(error::INVALID_FUNCTION_OPERATION, error::Operator::ASSIGN,
                 lvalue.get_symbol().value());
  }

  Assignexpr assignexpr;

  return assignexpr;
}
