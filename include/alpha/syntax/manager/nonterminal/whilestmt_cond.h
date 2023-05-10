#pragma once

#include <alpha/icode/quad/quad.h>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class Expr;

class Whilestmt_cond {
 public:
  using Quad = alpha::icode::quad::Quad;

 private:
  Quad::Label quad_address;

 public:
  static Whilestmt_cond from_lParTkn_expr_rParTkn(const Expr& expr);

 public:
  Quad::Label get_quad_address() const;
  void set_quad_address(const Quad::Label& quad_address);
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
