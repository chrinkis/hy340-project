#include <alpha/syntax/handler/symbol/function/argument.h>
#include <alpha/syntax/manager/nonterminal/idlist_opt.h>

using namespace alpha::syntax::manager::nonterminal;

void IdlistOpt::commaTkn_identifierTkn(const terminal::Identifier& identifier) {
  handlers::symbol::function::add_arg(identifier);
}
