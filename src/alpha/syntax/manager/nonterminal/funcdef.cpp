#include <alpha/syntax/handler/symbol/function/argument.h>
#include <alpha/syntax/handler/symbol/function/definition.h>
#include <alpha/syntax/manager/nonterminal/funcdef.h>

using namespace alpha::syntax::manager::nonterminal;
using alpha::syntax::handlers::symbol::function::end;
using alpha::syntax::handlers::symbol::function::end_arg_list;
using alpha::syntax::handlers::symbol::function::start;

Funcdef Funcdef::from_functionTkn(const terminal::Function& function) {
  Funcdef funcdef;

  start(funcdef, function);

  return funcdef;
}

Funcdef Funcdef::from_functionTkn_identifierTkn(
    const terminal::Identifier& identifier) {
  Funcdef funcdef;

  start(funcdef, identifier);

  return funcdef;
}

Funcdef Funcdef::rightParenthesisTkn() {
  end_arg_list();

  return Funcdef();
}

Funcdef Funcdef::block() {
  end();

  return Funcdef();
}
