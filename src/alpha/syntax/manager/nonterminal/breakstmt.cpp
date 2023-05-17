#include <alpha/syntax/manager/nonterminal/breakstmt.h>

#include <alpha/icode/quad/table.h>

using namespace alpha::syntax::manager::nonterminal;

using Quad = alpha::icode::quad::Quad;

Breakstmt::Breakstmt() : break_list_head(0), continue_list_head(0) {}

Breakstmt Breakstmt::from_breakTkn() {
  Breakstmt breakstmt;

  breakstmt.break_list_head = quadTable.new_list(quadTable.get_next_label());
  quadTable.emit_jump(0);

  return breakstmt;
}

Quad::Label Breakstmt::get_break_list_head() const {
  return this->break_list_head;
}

void Breakstmt::set_break_list_head(const Quad::Label& label) {
  this->break_list_head = label;
}

Quad::Label Breakstmt::get_continue_list_head() const {
  return this->continue_list_head;
}

void Breakstmt::set_continue_list_head(const Quad::Label& label) {
  this->continue_list_head = label;
}
