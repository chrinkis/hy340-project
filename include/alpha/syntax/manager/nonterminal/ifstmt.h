#pragma once

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class Ifstmt_if;
class Ifstmt_else;
class Stmt;

class Ifstmt {
 public:
  static void IfstmtIf_Stmt(const Ifstmt_if& ifstmt_if, const Stmt& stmt);
  static void IfstmtIf_Stmt_IfstmtElse_Stmt(const Ifstmt_if& ifstmt_if,
                                            const Stmt& stmt1,
                                            const Ifstmt_else& ifstmt_else,
                                            const Stmt& stmt2);
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
