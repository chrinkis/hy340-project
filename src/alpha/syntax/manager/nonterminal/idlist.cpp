#include <alpha/syntax/manager/nonterminal/idlist.h>

#include <alpha/syntax/handler/symbol/function/argument.h>

using namespace alpha::syntax::manager::nonterminal;
using alpha::syntax::handlers::symbol::function::add_arg;

void Idlist::identifierTkn(const terminal::Identifier& identifier) {
  add_arg(identifier);
}
