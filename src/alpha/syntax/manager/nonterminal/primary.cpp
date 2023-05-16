#include <alpha/syntax/manager/nonterminal/primary.h>

#include <alpha/icode/quad/table.h>
#include <alpha/syntax/manager/nonterminal/call.h>
#include <alpha/syntax/manager/nonterminal/const.h>
#include <alpha/syntax/manager/nonterminal/funcdef.h>
#include <alpha/syntax/manager/nonterminal/lvalue.h>
#include <alpha/syntax/manager/nonterminal/objectdef.h>

using namespace alpha::syntax::manager::nonterminal;

Primary Primary::from_lvalue(const Lvalue& lvalue) {
  Primary primary;

  primary.set_expr(quadTable.emit_if_table_item(lvalue.get_expr()));

  return primary;
}

Primary Primary::from_call(const Call& call) {
  Primary primary;

  primary.set_expr(call.get_expr());

  return primary;
}

Primary Primary::from_objectdef(const Objectdef& objectdef) {
  Primary primary;

  primary.set_expr(objectdef.get_expr());

  return primary;
}

Primary Primary::from_lParTkn_funcdef_rParTkn(const Funcdef& funcdef) {
  Primary primary;

  primary.set_expr(icode::Expr::for_program_func(funcdef.get_symbol()));

  return primary;
}

Primary Primary::from_const(const Const& constant) {
  Primary primary;

  primary.set_expr(constant.get_expr());

  return primary;
}
