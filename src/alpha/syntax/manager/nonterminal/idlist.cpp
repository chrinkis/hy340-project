#include <alpha/syntax/handler/symbol/function/argument.h>
#include <alpha/syntax/manager/nonterminal/idlist.h>

using namespace alpha::syntax::manager::nonterminal;

void Idlist::identifierTkn(const terminal::Identifier& identifier) {
  handlers::symbol::function::add_arg(identifier);
}
