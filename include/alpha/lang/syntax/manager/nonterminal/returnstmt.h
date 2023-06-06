#pragma once

#include <alpha/lang/syntax/location.h>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class Expr;

class Returnstmt {
 public:
  static void returnTkn_semicolonTkn(const location& loc);

  static void returnTkn_expr_semicolonTkn(const location& loc,
                                          const Expr& expr);
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
