#pragma once

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class IfstmtIf;
class IfstmtElse;
class Stmt;

class Ifstmt {
 public:
  static void ifstmtIf_stmt(const IfstmtIf& ifstmt_if, const Stmt& stmt);
  static void ifstmtIf_stmt_ifstmtElse_stmt(const IfstmtIf& ifstmt_if,
                                            const Stmt& stmt1,
                                            const IfstmtElse& ifstmt_else,
                                            const Stmt& stmt2);
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
