#include <alpha/syntax/manager/nonterminal/funcdef.h>

#include "alpha/syntax/handler/symbol/symbol.h"

using namespace alpha::syntax::manager::nonterminal;

Funcdef Funcdef::from_funcprefix_funcargs_funcbody(
    const Funcprefix& funcprefix) {
  Funcdef funcdef;

  handlers::symbol::continue_checking(funcdef, funcprefix);

  return funcdef;
}
