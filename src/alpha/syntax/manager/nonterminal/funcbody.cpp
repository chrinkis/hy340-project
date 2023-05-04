#include <alpha/syntax/manager/nonterminal/funcbody.h>

#include <alpha/syntax/handler/symbol/function/definition.h>

using namespace alpha::syntax::manager::nonterminal;
namespace function = alpha::syntax::handlers::symbol::function;

void Funcbody::block() {
  function::end();
}
