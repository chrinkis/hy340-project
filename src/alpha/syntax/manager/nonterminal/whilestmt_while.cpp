#include <alpha/syntax/manager/nonterminal/whilestmt_while.h>

#include <alpha/icode/quad/table.h>

using namespace alpha::syntax::manager::nonterminal;

WhilestmtWhile WhilestmtWhile::from_whileTkn() {
  WhilestmtWhile whilestmt_while;

  whilestmt_while.set_quad_address(quadTable.get_next_label());

  return whilestmt_while;
}

WhilestmtWhile::Quad::Label WhilestmtWhile::get_quad_address() const {
  return this->quad_address;
}

void WhilestmtWhile::set_quad_address(const Quad::Label& quad_address) {
  this->quad_address = quad_address;
}
