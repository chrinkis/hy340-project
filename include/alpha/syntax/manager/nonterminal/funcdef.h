#pragma once

#include <alpha/syntax/manager/terminal/function.h>
#include <alpha/syntax/manager/terminal/identifier.h>

#include <alpha/syntax/holder/Symbol.h>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class Funcdef : public holder::Symbol {
 public:
  static Funcdef from_functionTkn(const terminal::Function& function);

  static Funcdef from_functionTkn_identifierTkn(
      const terminal::Identifier& identifier);

  static Funcdef from_rightParenthesisTkn();

  static Funcdef from_block();
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
