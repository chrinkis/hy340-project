#pragma once

#include <alpha/syntax/manager/nonterminal/expr.h>
#include <alpha/syntax/manager/terminal/identifier.h>

#include <vector>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class Elist;
class Normalcall;
class Methodcall;

class Callsuffix {
 public:
  using ExprCollection = std::vector<icode::Expr>;

 private:
  ExprCollection elist;
  bool method;
  terminal::Identifier id;

 public:
  static Callsuffix from_normalcall(const Normalcall& normalcall);
  static Callsuffix from_methodcall(const Methodcall& methodcall);

 public:
  ExprCollection get_elist() const;
  void set_elist(const ExprCollection& elist);

  bool is_method() const;
  bool set_method(bool is_method);

  terminal::Identifier get_id() const;
  void set_id(const terminal::Identifier& id);
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
