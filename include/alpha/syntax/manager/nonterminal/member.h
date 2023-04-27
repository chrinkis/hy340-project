#pragma once

#include <alpha/syntax/holder/Symbol.h>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class Lvalue;

class Member : private holder::Symbol {
 public:
  static Member from_lvalue_dotTkn_idTkn(const Lvalue& lvalue);

  static Member from_lvalue_lSqrBrackTkn_expr_rSqrtBrackTkn(
      const Lvalue& lvalue);

  static Member from_call_dotTkn_idTkn();

  static Member from_call_lSqrBrackTkn_expr_rSqrtBrackTkn();
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
