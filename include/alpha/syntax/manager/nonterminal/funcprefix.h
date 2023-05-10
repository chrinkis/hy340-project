#pragma once

#include <alpha/icode/quad/quad.h>
#include <alpha/symbol/symbol.h>
#include <alpha/syntax/manager/terminal/function.h>
#include <alpha/syntax/manager/terminal/identifier.h>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class Funcprefix {
 public:
  using Quad = icode::quad::Quad;
  using Symbol = symbol::Symbol;

 private:
  Quad::Label quad_label;
  Symbol::SharedPtr symbol;

 public:
  static Funcprefix from_functionTkn(const terminal::Function& function);

  static Funcprefix from_functionTkn_identifierTkn(
      const terminal::Identifier& identifier);

 public:
  Quad::Label get_quad_label() const;
  void set_quad_label(const Quad::Label& quad_label);

  Symbol::SharedPtr get_symbol() const;
  void set_symbol(const Symbol::SharedPtr& symbol);
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
