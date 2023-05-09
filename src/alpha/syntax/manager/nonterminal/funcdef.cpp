#include <alpha/syntax/manager/nonterminal/funcdef.h>

using namespace alpha::syntax::manager::nonterminal;

Funcdef Funcdef::from_funcprefix_funcargs_funcbody(
    const Funcprefix& funcprefix) {
  Funcdef funcdef;

  funcdef.set_symbol(funcprefix.get_symbol());

  return funcdef;
}
