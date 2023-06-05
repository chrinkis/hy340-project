#include <alpha/syntax/manager/nonterminal/funcbody.h>

#include <alpha/symbol/table_manager.h>

using namespace alpha::syntax::manager::nonterminal;

void Funcbody::block() {
  symTable.end_function();
}
