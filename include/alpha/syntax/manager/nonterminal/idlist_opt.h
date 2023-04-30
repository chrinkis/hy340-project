#pragma once

#include <alpha/syntax/manager/terminal/identifier.h>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class IdlistOpt {
 public:
  static void commaTkn_identifierTkn(const terminal::Identifier& identifier);
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
