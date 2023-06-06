#pragma once

#include <alpha/lang/syntax/manager/nonterminal/funcprefix.h>

#include <alpha/lang/symbol/symbol.h>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class Funcdef {
 public:
  using Symbol = symbol::Symbol;

 private:
  Symbol::SharedPtr symbol;

 public:
  static Funcdef from_funcprefix_funcargs_funcbody(
      const Funcprefix& funcprefix);

 public:
  Symbol::SharedPtr get_symbol() const;
  void set_symbol(const Symbol::SharedPtr& symbol);
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
