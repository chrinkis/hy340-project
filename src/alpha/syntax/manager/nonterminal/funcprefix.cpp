#include <alpha/syntax/manager/nonterminal/funcprefix.h>

#include <alpha/symbol/table_manager.h>
#include <alpha/syntax/error.h>

using namespace alpha::syntax::manager::nonterminal;

Funcprefix Funcprefix::from_functionTkn(const terminal::Function& function) {
  Funcprefix funcprefix;

  auto symbol = symTable.start_function(function.get_location());

  funcprefix.set_symbol(symbol);

  return funcprefix;
}

Funcprefix Funcprefix::from_functionTkn_identifierTkn(
    const terminal::Identifier& id) {
  Funcprefix funcprefix;

  if (!symTable.can_add_function(id.get_name())) {
    error::invalid_name_for_func_definition(id.get_name(), id.get_location());

    auto symbol = symTable.start_function(id.get_location());

    funcprefix.set_symbol(symbol);
  } else {
    auto symbol = symTable.start_function(id.get_name(), id.get_location());

    funcprefix.set_symbol(symbol);
  }

  return funcprefix;
}
