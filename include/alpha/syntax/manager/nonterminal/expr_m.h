#pragma once

#include <alpha/icode/quad/quad.h>

namespace alpha::syntax::manager::nonterminal {

class ExprM {
 private:
  using QuadLabel = icode::quad::Quad::Label;

 private:
  QuadLabel label = 0;

 public:
  static ExprM from_empty();

 public:
  QuadLabel get_quad_label() const;
  void set_quad_label(const QuadLabel& quad_label);
};

}  // namespace alpha::syntax::manager::nonterminal
