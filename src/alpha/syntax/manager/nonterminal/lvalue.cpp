#include <alpha/syntax/manager/nonterminal/lvalue.h>

#include <alpha/syntax/handler/symbol/symbol.h>
#include <alpha/syntax/handler/symbol/variable/global.h>
#include <alpha/syntax/handler/symbol/variable/implicit.h>
#include <alpha/syntax/handler/symbol/variable/local.h>

using namespace alpha::syntax::manager::nonterminal;
namespace symbol_handler = alpha::syntax::handlers::symbol;
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

  variable_handler::ensure_global_exists(lvalue, identifier.get_name());

  return lvalue;
}

Lvalue Lvalue::from_member() {
  Lvalue lvalue;

  return lvalue;
}
