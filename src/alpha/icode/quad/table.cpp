#include <alpha/icode/quad/table.h>

namespace alpha::icode::quad {

void Table::emit(const Quad& quad) {
  this->table.push_back(quad);
}

void Table::emit_assign() {
  ;
}

void Table::emit_add() {
  ;
}

void Table::emit_sub() {
  ;
}

void Table::emit_mul() {
  ;
}

void Table::emit_div() {
  ;
}

void Table::emit_mod() {
  ;
}

void Table::emit_uminus() {
  ;
}

void Table::emit_and() {
  ;
}

void Table::emit_or() {
  ;
}

void Table::emit_not() {
  ;
}

void Table::emit_if_eq() {
  ;
}

void Table::emit_if_noteq() {
  ;
}

void Table::emit_if_lesseq() {
  ;
}

void Table::emit_if_greatereq() {
  ;
}

void Table::emit_if_less() {
  ;
}

void Table::emit_if_greater() {
  ;
}

void Table::emit_jump() {
  ;
}

void Table::emit_call() {
  ;
}

void Table::emit_param() {
  ;
}

void Table::emit_ret() {
  ;
}

void Table::emit_getretval() {
  ;
}

void Table::emit_funcstart(const std::string& name) {
  ;
}

void Table::emit_funcend() {
  ;
}

void Table::emit_tablecreate() {
  ;
}

void Table::emit_tablegetelem() {
  ;
}

void Table::emit_tablesetelem() {
  ;
}

Quad::Label Table::get_next_label() const {
  return 0;  // FIXME
}

std::ostream& operator<<(std::ostream& os, const Table& qt) {
  os << std::left;

  for (auto quad : qt.table) {
    os << quad << std::endl;
  }

  return os;
}

}  // namespace alpha::icode::quad
