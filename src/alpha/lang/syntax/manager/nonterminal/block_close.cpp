#include <alpha/lang/syntax/manager/nonterminal/block_close.h>

#include <alpha/lang/symbol/table_manager.h>

using namespace alpha::syntax::manager::nonterminal;

void BlockClose::rightCurlyBracketTkn() {
  symTable.decrease_scope();
}
