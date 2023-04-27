#pragma once

#include <alpha/syntax/holder/Symbol.h>

#include <alpha/syntax/manager/terminal/identifier.h>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class Lvalue : private holder::Symbol {
 private:
  using Identifier = terminal::Identifier;

 public:
  static Lvalue from_idTkn(const Identifier& identifier);

  static Lvalue from_localIdTkn(const Identifier& identifier);

  static Lvalue from_doubleColonTkn_localIdTkn(const Identifier& identifier);

  static Lvalue from_member();
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
