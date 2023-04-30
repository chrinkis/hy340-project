#pragma once

#include <alpha/syntax/holder/Symbol.h>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class Lvalue;

class Assignexpr : public holder::Symbol {
 public:
  static Assignexpr from_lvalue_assignTkn_expr(const Lvalue& lvalue);
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
