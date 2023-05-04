#pragma once

#include <alpha/syntax/manager/nonterminal/funcprefix.h>

#include <alpha/syntax/holder/Symbol.h>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class Funcdef : public holder::Symbol {
 public:
  static Funcdef from_funcprefix_funcargs_funcbody(
      const Funcprefix& funcprefix);
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
