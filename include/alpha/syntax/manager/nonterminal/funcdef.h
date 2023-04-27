#pragma once

#include <alpha/syntax/manager/terminal/function.h>
#include <alpha/syntax/manager/terminal/identifier.h>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class Funcdef {
 public:
  static void functionTkn(const terminal::Function& function);
  static void functionTkn_identifierTkn(const terminal::Identifier& identifier);
  static void rightParenthesisTkn();
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
