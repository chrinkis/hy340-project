#pragma once

#include <alpha/icode/quad/quad.h>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class IfstmtIf;
class IfstmtElse;
class Stmt;

class Ifstmt {
 private:
  using Quad = alpha::icode::quad::Quad;

 private:
  Quad::Label breaklist = 0;
  Quad::Label contlist = 0;

 public:
  static Ifstmt from_ifstmtIf_stmt(const IfstmtIf& ifstmt_if, const Stmt& stmt);
  static Ifstmt from_ifstmtIf_stmt_ifstmtElse_stmt(
      const IfstmtIf& ifstmt_if,
      const Stmt& stmt1,
      const IfstmtElse& ifstmt_else,
      const Stmt& stmt2);

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
