#include <alpha/lang/syntax/manager/nonterminal/idlist_id.h>

#include <alpha/lang/symbol/table_manager.h>
#include <alpha/lang/syntax/error.h>

using namespace alpha::syntax::manager::nonterminal;

void IdlistId::identifierTkn(const terminal::Identifier& id) {
  if (!symTable.can_add_argument(id.get_name())) {
    error::invalid_argumnet_name(id.get_name(), id.get_location());

  } else {
    symTable.add_argument(id.get_name(), id.get_location());
  }
}
