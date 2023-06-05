#pragma once

#include <alpha/icode/expr.h>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class Const {
 private:
  icode::Expr expr;

 public:
  static Const from_integerTkn(const int i);
  static Const from_floatTkn(const double f);
  static Const from_stringTkn(const std::string s);
  static Const from_nilTkn();
  static Const from_trueTkn();
  static Const from_falseTkn();

 public:
  icode::Expr get_expr() const;
  void set_expr(const icode::Expr& expr);
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
