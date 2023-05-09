#include <alpha/syntax/manager/nonterminal/lvalue.h>

#include <alpha/syntax/error.h>
#include <alpha/syntax/manager/nonterminal/member.h>

using namespace alpha::syntax::manager::nonterminal;

Member Member::from_lvalue_dotTkn_idTkn(const Lvalue& lvalue) {
  if (lvalue.get_symbol() && lvalue.get_symbol().value()->has_function_type()) {
    error::invalid_function_operation(error::Operator::DOT,
                                      lvalue.get_symbol().value());
  }

  Member member;

  return member;
}

Member Member::from_lvalue_lSqrBrackTkn_expr_rSqrtBrackTkn(
    const Lvalue& lvalue) {
  if (lvalue.get_symbol() && lvalue.get_symbol().value()->has_function_type()) {
    error::invalid_function_operation(error::Operator::SQUARE_BRACKETS,
                                      lvalue.get_symbol().value());
  }

  Member member;

  return member;
}

Member Member::from_call_dotTkn_idTkn() {
  Member member;

  return member;
}

Member Member::from_call_lSqrBrackTkn_expr_rSqrtBrackTkn() {
  Member member;

  return member;
}
