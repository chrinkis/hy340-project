#pragma once

#include <alpha/lang/icode/quad/quad.h>
#include <alpha/lang/symbol/symbol.h>
#include <alpha/lang/syntax/manager/terminal/function.h>
#include <alpha/lang/syntax/manager/terminal/identifier.h>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class Funcprefix {
 public:
  using Symbol = symbol::Symbol;

 private:
  Symbol::SharedPtr symbol;

 public:
  static Funcprefix from_functionTkn(const terminal::Function& function);

  static Funcprefix from_functionTkn_identifierTkn(
      const terminal::Identifier& identifier);

 public:
  Symbol::SharedPtr get_symbol() const;
  void set_symbol(const Symbol::SharedPtr& symbol);
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
