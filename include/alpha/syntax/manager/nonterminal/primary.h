#pragma once

#include <alpha/syntax/holder/Symbol.h>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class Lvalue;

class Primary : public holder::Symbol {
 public:
  static Primary from_lvalue(const Lvalue& lvalue);

  static Primary from_call();

  static Primary from_objectdef();

  static Primary from_lParTkn_funcdef_rParTkn();

  static Primary from_const();
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
