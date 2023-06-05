#pragma once

#include <alpha/icode/quad/quad.h>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class BlockBody;

class Block {
 public:
  using Quad = alpha::icode::quad::Quad;

 private:
  Quad::Label breaklist = 0;
  Quad::Label contlist = 0;

 public:
  static Block from_blockOpen_blockBody_blockClose(const BlockBody& block_body);

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
