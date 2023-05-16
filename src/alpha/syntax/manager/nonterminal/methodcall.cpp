#include <alpha/syntax/manager/nonterminal/methodcall.h>

namespace alpha::syntax::manager::nonterminal {

Methodcall::Methodcall(const terminal::Identifier& id) : id(id) {}

Methodcall Methodcall::from_doubleDotTkn_identifier_lParTkn_elist_rParTkn(
    const terminal::Identifier& id,
    const Elist& elist) {
  Methodcall methodcall(id);

  methodcall.set_elist(elist.get_list());
  methodcall.set_method(true);

  return methodcall;
}

}  // namespace alpha::syntax::manager::nonterminal
