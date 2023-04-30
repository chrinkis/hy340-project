#include <alpha/syntax/handler/symbol/function/error_checker.h>
#include <alpha/syntax/handler/symbol/symbol.h>
#include <alpha/syntax/manager/nonterminal/assignexpr.h>
#include <alpha/syntax/manager/nonterminal/lvalue.h>
#include "alpha/syntax/holder/Symbol.h"

using namespace alpha::syntax::manager::nonterminal;

Assignexpr Assignexpr::from_lvalue_assignTkn_expr(const Lvalue& lvalue) {
  handlers::symbol::function::check_for_errors(lvalue, "assignment to");

  Assignexpr assignexpr;

  handlers::symbol::stop_checking(assignexpr);

  return assignexpr;
}
