#include <alpha/syntax/manager/nonterminal/lvalue.h>

#include <alpha/syntax/error.h>
#include <alpha/syntax/handler/symbol/variable/implicit.h>
#include <alpha/syntax/handler/symbol/variable/local.h>

using namespace alpha::syntax::manager::nonterminal;
namespace variable_handler = alpha::syntax::handlers::symbol::variable;

Lvalue Lvalue::from_idTkn(const Identifier& identifier) {
  Lvalue lvalue;

  variable_handler::ensure_exists(lvalue, identifier);

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
