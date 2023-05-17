#include <alpha/syntax/manager/nonterminal/funcdef.h>

#include <alpha/icode/quad/table.h>

using namespace alpha::syntax::manager::nonterminal;

using Symbol = alpha::symbol::Symbol;

Funcdef Funcdef::from_funcprefix_funcargs_funcbody(
    const Funcprefix& funcprefix) {
  Funcdef funcdef;

  funcdef.set_symbol(funcprefix.get_symbol());
  quadTable.emit_funcend(funcdef.get_symbol());

  return funcdef;
}

Symbol::SharedPtr Funcdef::get_symbol() const {
  return this->symbol;
}

void Funcdef::set_symbol(const Symbol::SharedPtr& symbol) {
  this->symbol = symbol;
}
