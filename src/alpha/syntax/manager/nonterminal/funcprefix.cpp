#include <alpha/syntax/manager/nonterminal/funcprefix.h>

#include <alpha/syntax/handler/symbol/function/definition.h>

using namespace alpha::syntax::manager::nonterminal;
namespace function = alpha::syntax::handlers::symbol::function;

Funcprefix Funcprefix::from_functionTkn(const terminal::Function& function) {
  Funcprefix funcprefix;

  function::start(funcprefix, function);

  return funcprefix;
}

Funcprefix Funcprefix::from_functionTkn_identifierTkn(
    const terminal::Identifier& identifier) {
  Funcprefix funcprefix;

  function::start(funcprefix, identifier);

  return funcprefix;
}
