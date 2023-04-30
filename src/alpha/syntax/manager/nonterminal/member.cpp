#include <alpha/syntax/manager/nonterminal/lvalue.h>

#include <alpha/syntax/handler/symbol/function/error_checker.h>
#include <alpha/syntax/handler/symbol/symbol.h>
#include <alpha/syntax/manager/nonterminal/member.h>

using namespace alpha::syntax::manager::nonterminal;
using alpha::syntax::handlers::symbol::stop_checking;
using alpha::syntax::handlers::symbol::function::check_for_errors;

Member Member::from_lvalue_dotTkn_idTkn(const Lvalue& lvalue) {
  check_for_errors(lvalue, "\".\" with");

  Member member;

  stop_checking(member);

  return member;
}

Member Member::from_lvalue_lSqrBrackTkn_expr_rSqrtBrackTkn(
    const Lvalue& lvalue) {
  check_for_errors(lvalue, "\"[]\" with");

  Member member;

  stop_checking(member);

  return member;
}

Member Member::from_call_dotTkn_idTkn() {
  Member member;

  stop_checking(member);

  return member;
}

Member Member::from_call_lSqrBrackTkn_expr_rSqrtBrackTkn() {
  Member member;

  stop_checking(member);

  return member;
}
