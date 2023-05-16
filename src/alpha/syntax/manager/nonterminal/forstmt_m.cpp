#include <alpha/syntax/manager/nonterminal/forstmt_m.h>

#include <alpha/icode/quad/table.h>

using namespace alpha::syntax::manager::nonterminal;

ForstmtM ForstmtM::from_empty() {
  ForstmtM forstmt_m;

  Quad::Label quad_address = quadTable.get_next_label();
  forstmt_m.set_quad_address(quad_address);

  return forstmt_m;
}

ForstmtM::Quad::Label ForstmtM::get_quad_address() const {
  return this->quad_address;
}

void ForstmtM::set_quad_address(const Quad::Label& quad_address) {
  this->quad_address = quad_address;
}
