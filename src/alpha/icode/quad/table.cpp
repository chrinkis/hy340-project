#include <alpha/icode/quad/table.h>

namespace alpha::icode::quad {

void Table::emit(const Quad& quad) {
  this->table.push_back(quad);
}

void Table::emit_assign(const Expr& dest, const Expr& src) {
  ;
}

void Table::emit_add(const Expr& result, const Expr& op_a, const Expr& op_b) {
  ;
}

void Table::emit_sub(const Expr& result, const Expr& op_a, const Expr& op_b) {
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

void Table::emit_uminus(const Expr& result, const Expr& operand) {
  ;
}

void Table::emit_and() {
  ;
}

void Table::emit_or() {
  ;
}

void Table::emit_not(const Expr& result, const Expr& operand) {
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

void Table::emit_funcstart() {
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

void Table::emit_tablesetelem(const Expr& table,
                              const Expr& index,
                              const Expr& val) {
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
