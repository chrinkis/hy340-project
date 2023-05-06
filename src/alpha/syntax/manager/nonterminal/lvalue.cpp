#include <alpha/syntax/manager/nonterminal/lvalue.h>

#include <alpha/syntax/error.h>
#include <alpha/syntax/handler/symbol/variable/local.h>

using namespace alpha::syntax::manager::nonterminal;
namespace variable_handler = alpha::syntax::handlers::symbol::variable;

Lvalue Lvalue::from_idTkn(const Identifier& id) {
  Lvalue lvalue;

  auto result_opt = symTable.search_for_visible_symbol(id.get_name());

  if (!result_opt) {
    assert(symTable.can_add_variable(id.get_name()));

    auto symbol = symTable.add_variable(id.get_name(), id.get_location());

    lvalue.set_symbol(symbol);
  } else {
    auto result = result_opt.value();

    if (!result.accessible) {
      error::print_semantic(
          "can not access variable/function `" + id.get_name() + "`",
          id.get_location());
    } else {
      lvalue.set_symbol(result.symbol);
    }
  }

  return lvalue;
}

Lvalue Lvalue::from_localIdTkn(const Identifier& identifier) {
  Lvalue lvalue;

  variable_handler::ensure_local_exists(lvalue, identifier);

  return lvalue;
}

Lvalue Lvalue::from_doubleColonTkn_localIdTkn(const Identifier& identifier) {
  Lvalue lvalue;

  std::string name = identifier.get_name();
  auto result_opt = symTable.search_for_visible_global_symbol(name);

  if (!result_opt) {
    error::print_semantic(
        "undefined refference to global variable/function `" + name + "`",
        identifier.get_location());

  } else {
    auto result = result_opt.value();
    lvalue.set_symbol(holder::Symbol::Optional(result.symbol));
  }

  return lvalue;
}

Lvalue Lvalue::from_member() {
  Lvalue lvalue;

  return lvalue;
}
