#include <alpha/syntax/manager/nonterminal/funcdef.h>

#include <alpha/icode/quad/table.h>

using namespace alpha::syntax::manager::nonterminal;
using Opcode = alpha::icode::quad::Quad::Opcode;

using Symbol = alpha::symbol::Symbol;

Funcdef Funcdef::from_funcprefix_funcargs_funcbody(
    const Funcprefix& funcprefix) {
  Funcdef funcdef;

  funcdef.set_symbol(funcprefix.get_symbol());
  quadTable.emit(Opcode::FUNCEND,
                 icode::Expr::for_program_func(funcdef.get_symbol()));

  return funcdef;
}

Symbol::SharedPtr Funcdef::get_symbol() const {
  return this->symbol;
}

void Funcdef::set_symbol(const Symbol::SharedPtr& symbol) {
  this->symbol = symbol;
}
