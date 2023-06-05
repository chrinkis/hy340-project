#include <alpha/syntax/manager/nonterminal/normcall.h>

#include <alpha/syntax/manager/nonterminal/elist.h>

namespace alpha::syntax::manager::nonterminal {

Normcall Normcall::from_lParTkn_elist_rParTkn(const Elist& elist) {
  Normcall normcall;

  normcall.elist = elist.get_icode_elist();
  normcall.method = false;

  return normcall;
}

Normcall::ExprCollection Normcall::get_elist() const {
  return this->elist;
}

void Normcall::set_elist(const ExprCollection& elist) {
  this->elist = elist;
}

bool Normcall::is_method() const {
  return this->method;
}

void Normcall::set_method(bool is_method) {
  this->method = is_method;
}

}  // namespace alpha::syntax::manager::nonterminal
