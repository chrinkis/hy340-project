#include <alpha/syntax/handler/symbol/function/definition.h>
#include <alpha/syntax/manager/nonterminal/funcdef.h>

using namespace alpha::syntax::manager::nonterminal;

void Funcdef::functionTkn(const terminal::Function& function) {
  handlers::symbol::function::start(function);
}

void Funcdef::functionTkn_identifierTkn(
    const terminal::Identifier& identifier) {
  handlers::symbol::function::start(identifier);
}

void Funcdef::rightParenthesisTkn() {
  handlers::symbol::function::end();
}
