#pragma once

#include <alpha/syntax/manager/nonterminal/expr.h>
#include <alpha/syntax/manager/terminal/identifier.h>

#include <vector>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class Elist;

class Methodcall {
 public:
  using ExprCollection = std::vector<Expr>;

 private:
  ExprCollection elist;
  bool method;
  terminal::Identifier id;

 private:
  Methodcall(const terminal::Identifier& id);

 public:
  Methodcall();
  Methodcall operator=(const Methodcall& other);

 public:
  static Methodcall from_doubleDotTkn_identifier_lParTkn_elist_rParTkn(
      const terminal::Identifier& id,
      const Elist& elist);

 public:
  ExprCollection get_elist() const;
  void set_elist(const ExprCollection& elist);

  bool is_method() const;
  void set_method(bool is_method);

  terminal::Identifier get_id() const;
  void set_id(const terminal::Identifier& id);
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
