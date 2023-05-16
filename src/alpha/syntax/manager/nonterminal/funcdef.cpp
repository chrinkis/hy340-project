#include <alpha/syntax/manager/nonterminal/funcdef.h>

#include <alpha/icode/quad/table.h>

using namespace alpha::syntax::manager::nonterminal;

Funcdef Funcdef::from_funcprefix_funcargs_funcbody(
    const Funcprefix& funcprefix) {
  Funcdef funcdef;

  funcdef.set_symbol(funcprefix.get_symbol());
  quadTable.emit_funcend(funcdef.get_symbol());

  return funcdef;
}
