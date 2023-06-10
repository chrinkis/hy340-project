#pragma once

#include <alpha/lang/icode/quad/quad.h>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class Breakstmt;
class Continuestmt;
class Block;
class Ifstmt;

class Stmt {
 public:
  using Quad = alpha::icode::quad::Quad;

 private:
  Quad::Label breaklist = 0;
  Quad::Label contlist = 0;

 public:
  Stmt();

 public:
  static Stmt from_expr_smclnTkn();
  static Stmt from_ifstmt(const Ifstmt& ifstmt);
  static Stmt from_whilestmt();
  static Stmt from_forstmt();
  static Stmt from_returnstmt();
  static Stmt from_breakstmt(const Breakstmt& breakstmt);
  static Stmt from_continuestmt(const Continuestmt& continuestmt);
  static Stmt from_block(const Block& block);
  static Stmt from_funcdef();
  static Stmt from_smclnTkn();

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
