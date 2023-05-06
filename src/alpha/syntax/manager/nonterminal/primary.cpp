#include <alpha/syntax/manager/nonterminal/primary.h>

#include <alpha/syntax/manager/nonterminal/funcdef.h>
#include <alpha/syntax/manager/nonterminal/lvalue.h>

using namespace alpha::syntax::manager::nonterminal;

Primary Primary::from_lvalue(const Lvalue& lvalue) {
  Primary primary;

  primary.set_symbol(lvalue.get_symbol());

  return primary;
}

Primary Primary::from_call() {
  Primary primary;

  return primary;
}

Primary Primary::from_objectdef() {
  Primary primary;

  return primary;
}

Primary Primary::from_lParTkn_funcdef_rParTkn(const Funcdef& funcdef) {
  Primary primary;

  primary.set_symbol(funcdef.get_symbol());

  return primary;
}

Primary Primary::from_const() {
  Primary primary;

  return primary;
}
