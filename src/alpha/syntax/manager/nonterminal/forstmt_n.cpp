#include <alpha/syntax/manager/nonterminal/forstmt_n.h>

#include <alpha/icode/quad/table.h>

using namespace alpha::syntax::manager::nonterminal;

ForstmtN ForstmtN::from_empty() {
  ForstmtN forstmt_n;

  Quad::Label quad_address = quadTable.get_next_label();
  forstmt_n.set_quad_address(quad_address);

  quadTable.emit_jump(0);

  return forstmt_n;
}

ForstmtN::Quad::Label ForstmtN::get_quad_address() const {
  return this->quad_address;
}

void ForstmtN::set_quad_address(const Quad::Label& quad_address) {
  this->quad_address = quad_address;
}
