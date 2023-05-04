#pragma once

#include <alpha/syntax/manager/terminal/function.h>
#include <alpha/syntax/manager/terminal/identifier.h>

#include <alpha/syntax/holder/Symbol.h>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class Funcprefix : public holder::Symbol {
 public:
  static Funcprefix from_functionTkn(const terminal::Function& function);

  static Funcprefix from_functionTkn_identifierTkn(
      const terminal::Identifier& identifier);
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
