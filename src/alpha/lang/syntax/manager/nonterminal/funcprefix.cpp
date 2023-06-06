#include <alpha/lang/syntax/manager/nonterminal/funcprefix.h>

#include <alpha/lang/icode/quad/table.h>
#include <alpha/lang/symbol/table_manager.h>
#include <alpha/lang/syntax/error.h>

using namespace alpha::syntax::manager::nonterminal;
using Opcode = alpha::icode::quad::Quad::Opcode;

Funcprefix Funcprefix::from_functionTkn(const terminal::Function& function) {
  Funcprefix funcprefix;

  auto symbol = symTable.start_function(function.get_location(),
                                        quadTable.get_next_label());

  funcprefix.set_symbol(symbol);
  quadTable.emit(Opcode::FUNCSTART, icode::Expr::for_program_func(symbol));

  return funcprefix;
}

Funcprefix Funcprefix::from_functionTkn_identifierTkn(
    const terminal::Identifier& id) {
  Funcprefix funcprefix;

  Symbol::SharedPtr symbol;

  if (!symTable.can_add_function(id.get_name())) {
    error::invalid_name_for_func_definition(id.get_name(), id.get_location());

    symbol =
        symTable.start_function(id.get_location(), quadTable.get_next_label());

    funcprefix.set_symbol(symbol);
  } else {
    symbol = symTable.start_function(id.get_name(), id.get_location(),
                                     quadTable.get_next_label());

    funcprefix.set_symbol(symbol);
  }

  quadTable.emit(Opcode::FUNCSTART, icode::Expr::for_program_func(symbol));

  return funcprefix;
}

Funcprefix::Symbol::SharedPtr Funcprefix::get_symbol() const {
  return this->symbol;
}

void Funcprefix::set_symbol(const Symbol::SharedPtr& symbol) {
  this->symbol = symbol;
}
