#include <alpha/syntax/manager/nonterminal/assignexpr.h>

#include <alpha/syntax/handler/symbol/function/error_checker.h>
#include <alpha/syntax/manager/nonterminal/lvalue.h>

using namespace alpha::syntax::manager::nonterminal;

using alpha::syntax::handlers::symbol::function::check_for_errors;

Assignexpr Assignexpr::from_lvalue_assignTkn_expr(const Lvalue& lvalue) {
  check_for_errors(lvalue, "assignment to");

  Assignexpr assignexpr;

  return assignexpr;
}
