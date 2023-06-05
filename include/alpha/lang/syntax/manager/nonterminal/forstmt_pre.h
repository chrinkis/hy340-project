#pragma once

#include <alpha/icode/quad/quad.h>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class ForstmtM;
class Expr;

class ForstmtPre {
 public:
  using Quad = alpha::icode::quad::Quad;

 private:
  Quad::Label test;
  Quad::Label enter;

 public:
  static ForstmtPre from_forTkn_lParTkn_elist_smclnTkn_M_expr_smclnTkn(
      const ForstmtM& M,
      const Expr& expr);

 public:
  Quad::Label get_test() const;
  void set_test(const Quad::Label& test);
  Quad::Label get_enter() const;
  void set_enter(const Quad::Label& enter);
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
