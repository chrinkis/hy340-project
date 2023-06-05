#include <alpha/syntax/manager/nonterminal/block_body.h>

#include <alpha/syntax/manager/nonterminal/stmts.h>

using namespace alpha::syntax::manager::nonterminal;

using Quad = alpha::icode::quad::Quad;

BlockBody BlockBody::from_empty() {
  BlockBody block_body;

  return block_body;
}

BlockBody BlockBody::from_stmts(const Stmts& stmts) {
  BlockBody block_body;

  block_body.set_breaklist(stmts.get_breaklist());
  block_body.set_contlist(stmts.get_contlist());

  return block_body;
}

Quad::Label BlockBody::get_breaklist() const {
  return this->breaklist;
}

void BlockBody::set_breaklist(const Quad::Label& breaklist) {
  this->breaklist = breaklist;
}

Quad::Label BlockBody::get_contlist() const {
  return this->contlist;
}

void BlockBody::set_contlist(const Quad::Label& contlist) {
  this->contlist = contlist;
}
