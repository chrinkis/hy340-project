#pragma once

#include <alpha/icode/quad/quad.h>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class Expr;

class IfstmtIf {
 private:
  using Quad = icode::quad::Quad;

 private:
  Quad::Label label;

 public:
  static IfstmtIf from_ifTkn_lParTkn_expr_rParTkn(const Expr& expr);

 public:
  Quad::Label get_label() const;
  void set_label(const Quad::Label& label);
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
