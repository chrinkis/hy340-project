#include <alpha/syntax/manager/nonterminal/ifstmt_else.h>

#include <alpha/icode/quad/table.h>

using namespace alpha::syntax::manager::nonterminal;

using Quad = alpha::icode::quad::Quad;

IfstmtElse IfstmtElse::from_elseTkn() {
  IfstmtElse ifstmt_else;

  ifstmt_else.set_quad_address(quadTable.get_next_label());
  quadTable.emit_jump(0);

  return ifstmt_else;
}

Quad::Label IfstmtElse::get_quad_address() const {
  return this->quad_address;
}

void IfstmtElse::set_quad_address(const Quad::Label& label) {
  this->quad_address = label;
}
