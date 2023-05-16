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

void Table::emit_mul(const Expr& result, const Expr& op_a, const Expr& op_b) {
  ;
}

void Table::emit_div(const Expr& result, const Expr& op_a, const Expr& op_b) {
  ;
}

void Table::emit_mod(const Expr& result, const Expr& op_a, const Expr& op_b) {
  ;
}

void Table::emit_uminus(const Expr& result, const Expr& operand) {
  ;
}

void Table::emit_and(const Expr& result, const Expr& op_a, const Expr& op_b) {
  ;
}

void Table::emit_or(const Expr& result, const Expr& op_a, const Expr& op_b) {
  ;
}

void Table::emit_not(const Expr& result, const Expr& operand) {
  ;
}

void Table::emit_if_eq(const Expr& op_a,
                       const Expr& op_b,
                       const Expr& address) {
  ;
}

void Table::emit_if_noteq(const Expr& op_a,
                          const Expr& op_b,
                          const Expr& address) {
  ;
}

void Table::emit_if_lesseq(const Expr& op_a,
                           const Expr& op_b,
                           const Expr& address) {
  ;
}

void Table::emit_if_greatereq(const Expr& op_a,
                              const Expr& op_b,
                              const Expr& address) {
  ;
}

void Table::emit_if_less(const Expr& op_a,
                         const Expr& op_b,
                         const Expr& address) {
  ;
}

void Table::emit_if_greater(const Expr& op_a,
                            const Expr& op_b,
                            const Expr& address) {
  ;
}

void Table::emit_jump(const Expr& address) {
  ;
}

void emit_call(const Expr& expr) {
  ;
}

void emit_param(const Expr& expr) {
  ;
}

void Table::emit_ret() {
  ;
}

void emit_getretval(const Expr& expr) {
  ;
}

void Table::emit_funcstart() {
  ;
}

void Table::emit_funcend(const symbol::Symbol::SharedPtr& function) {
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
