#include <alpha/lang/syntax/manager/nonterminal/funcargs.h>

#include <alpha/lang/symbol/table_manager.h>

using namespace alpha::syntax::manager::nonterminal;

void Funcargs::lParTkn_idlist_rParTkn() {
  symTable.end_argument_list();
}
