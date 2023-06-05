#include <alpha/lang/syntax/manager/nonterminal/methodcall.h>

#include <alpha/lang/syntax/manager/nonterminal/elist.h>

namespace alpha::syntax::manager::nonterminal {

Methodcall Methodcall::from_doubleDotTkn_identifier_lParTkn_elist_rParTkn(
    const terminal::Identifier& id,
    const Elist& elist) {
  Methodcall methodcall;

  methodcall.set_id(id);
  methodcall.set_elist(elist.get_icode_elist());
  methodcall.set_method(true);

  return methodcall;
}

Methodcall::ExprCollection Methodcall::get_elist() const {
  return this->elist;
}

void Methodcall::set_elist(const ExprCollection& elist) {
  this->elist = elist;
}

bool Methodcall::is_method() const {
  return this->method;
}

void Methodcall::set_method(bool is_method) {
  this->method = is_method;
}

terminal::Identifier Methodcall::get_id() const {
  return this->id;
}

void Methodcall::set_id(const terminal::Identifier& id) {
  this->id = id;
}

}  // namespace alpha::syntax::manager::nonterminal
