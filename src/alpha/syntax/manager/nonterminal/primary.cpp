#include <alpha/syntax/manager/nonterminal/funcdef.h>
#include <alpha/syntax/manager/nonterminal/lvalue.h>

#include <alpha/syntax/manager/nonterminal/primary.h>

#include <alpha/syntax/handler/symbol/symbol.h>

using namespace alpha::syntax::manager::nonterminal;
namespace symbol_handler = alpha::syntax::handlers::symbol;

Primary Primary::from_lvalue(const Lvalue& lvalue) {
  Primary primary;

  symbol_handler::continue_checking(primary, lvalue);

  return primary;
}

Primary Primary::from_call() {
  Primary primary;

  symbol_handler::stop_checking(primary);

  return primary;
}

Primary Primary::from_objectdef() {
  Primary primary;

  symbol_handler::stop_checking(primary);

  return primary;
}

Primary Primary::from_lParTkn_funcdef_rParTkn(const Funcdef& funcdef) {
  Primary primary;

  symbol_handler::continue_checking(primary, funcdef);

  return primary;
}

Primary Primary::from_const() {
  Primary primary;

  symbol_handler::stop_checking(primary);

  return primary;
}