#include <alpha/syntax/handler/symbol/function/definition.h>
#include <alpha/syntax/manager/nonterminal/funcdef.h>

using namespace alpha::syntax::manager::nonterminal;
using alpha::syntax::handlers::symbol::function::end;
using alpha::syntax::handlers::symbol::function::start;

void Funcdef::functionTkn(const terminal::Function& function) {
  start(function);
}

void Funcdef::functionTkn_identifierTkn(
    const terminal::Identifier& identifier) {
  start(identifier);
}

void Funcdef::rightParenthesisTkn() {
  end();
}
