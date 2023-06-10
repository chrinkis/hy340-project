#pragma once

#include <alpha/lang/icode/quad/quad.h>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class Stmt;

class Stmts {
 public:
  using Quad = alpha::icode::quad::Quad;

 private:
  Quad::Label breaklist = 0;
  Quad::Label contlist = 0;

 public:
  static Stmts from_stmt(const Stmt& stmt);
  static Stmts from_stmts_stmt(const Stmts& stmts, const Stmt& stmt);

 public:
  Quad::Label get_breaklist() const;
  void set_breaklist(const Quad::Label& breaklist);
  Quad::Label get_contlist() const;
  void set_contlist(const Quad::Label& contlist);
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
