#include <alpha/lang/syntax/manager/nonterminal/block.h>

#include <alpha/lang/syntax/manager/nonterminal/block_body.h>

using namespace alpha::syntax::manager::nonterminal;

using Quad = alpha::icode::quad::Quad;

Block Block::from_blockOpen_blockBody_blockClose(const BlockBody& block_body) {
  Block block;

  block.set_breaklist(block_body.get_breaklist());
  block.set_contlist(block_body.get_contlist());

  return block;
}

Quad::Label Block::get_breaklist() const {
  return this->breaklist;
}

void Block::set_breaklist(const Quad::Label& breaklist) {
  this->breaklist = breaklist;
}

Quad::Label Block::get_contlist() const {
  return this->contlist;
}

void Block::set_contlist(const Quad::Label& contlist) {
  this->contlist = contlist;
}
