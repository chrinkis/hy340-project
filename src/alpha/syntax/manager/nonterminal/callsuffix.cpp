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

}  // namespace alpha::syntax::manager::nonterminal
