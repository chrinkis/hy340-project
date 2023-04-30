#include <alpha/syntax/handler/symbol/function/error_checker.h>
#include <alpha/syntax/handler/symbol/symbol.h>
#include <alpha/syntax/manager/nonterminal/assignexpr.h>

using namespace alpha::syntax::manager::nonterminal;

using alpha::syntax::handlers::symbol::stop_checking;
using alpha::syntax::handlers::symbol::function::check_for_errors;

Assignexpr Assignexpr::from_lvalue_assignTkn_expr(const Lvalue& lvalue) {
  check_for_errors(lvalue, "assignment to");

  Assignexpr assignexpr;

  stop_checking(assignexpr);

  return assignexpr;
}
