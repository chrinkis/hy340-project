#pragma once

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class Expr;

class Returnstmt {
 public:
  static void returnTkn_semicolonTkn();

  static void returnTkn_expr_semicolonTkn(const Expr& expr);
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
