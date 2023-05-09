#include <alpha/syntax/manager/nonterminal/block_open.h>

#include <alpha/symbol/table_manager.h>

using namespace alpha::syntax::manager::nonterminal;

void BlockOpen::leftCurlyBracketTkn() {
  symTable.increase_scope();
}
