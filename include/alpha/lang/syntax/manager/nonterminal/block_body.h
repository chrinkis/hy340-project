#pragma once

#include <alpha/icode/quad/quad.h>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class Stmts;

class BlockBody {
 public:
  using Quad = alpha::icode::quad::Quad;

 private:
  Quad::Label breaklist = 0;
  Quad::Label contlist = 0;

 public:
  static BlockBody from_empty();
  static BlockBody from_stmts(const Stmts& stmts);

 public:
  Quad::Label get_breaklist() const;
  void set_breaklist(const Quad::Label& breaklist);
  Quad::Label get_contlist() const;
  void set_contlist(const Quad::Label& contlist);
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
