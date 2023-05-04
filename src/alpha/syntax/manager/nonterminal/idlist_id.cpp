#include <alpha/syntax/manager/nonterminal/idlist_id.h>

#include <alpha/syntax/handler/symbol/function/argument.h>

using namespace alpha::syntax::manager::nonterminal;
namespace function = alpha::syntax::handlers::symbol::function;

void IdlistId::identifierTkn(const terminal::Identifier& identifier) {
  function::add_arg(identifier);
}
