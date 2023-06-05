#pragma once

#include <alpha/lang/icode/quad/quad.h>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class WhilestmtWhile {
 public:
  using Quad = alpha::icode::quad::Quad;

 private:
  Quad::Label quad_address;

 public:
  static WhilestmtWhile from_whileTkn();

 public:
  Quad::Label get_quad_address() const;
  void set_quad_address(const Quad::Label& quad_address);
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
