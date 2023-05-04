#include <alpha/syntax/manager/nonterminal/funcargs.h>

#include <alpha/syntax/handler/symbol/function/argument.h>

using namespace alpha::syntax::manager::nonterminal;
namespace function = alpha::syntax::handlers::symbol::function;

void Funcargs::lParTkn_idlist_rParTkn() {
  function::end_arg_list();
}
