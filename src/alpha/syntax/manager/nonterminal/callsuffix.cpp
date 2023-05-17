#include <alpha/syntax/manager/nonterminal/callsuffix.h>

#include <alpha/syntax/manager/nonterminal/methodcall.h>
#include <alpha/syntax/manager/nonterminal/normcall.h>

namespace alpha::syntax::manager::nonterminal {

Callsuffix::Callsuffix(const terminal::Identifier id) : id(id) {}

Callsuffix Callsuffix::from_normcall(const Normcall& normalcall) {
  Callsuffix callsuffix(normalcall.get_id());

  return callsuffix;
}

Callsuffix Callsuffix::from_methodcall(const Methodcall& methodcall) {
  Callsuffix callsuffix(methodcall.get_id());

  return callsuffix;
}

Callsuffix::ExprCollection Callsuffix::get_elist() const {
  return this->elist;
}

void Callsuffix::set_elist(const ExprCollection& elist) {
  this->elist = elist;
}

void Callsuffix::add_to_elist(const icode::Expr& expr) {
  this->elist.push_back(expr);
}

bool Callsuffix::is_method() const {
  return this->method;
}

bool Callsuffix::set_method(bool is_method) {
  this->method = is_method;
}

terminal::Identifier Callsuffix::get_id() const {
  return this->id;
}

void Callsuffix::set_id(const terminal::Identifier& id) {
  this->id = id;
}

}  // namespace alpha::syntax::manager::nonterminal
