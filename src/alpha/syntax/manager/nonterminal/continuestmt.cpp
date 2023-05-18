#include <alpha/syntax/manager/nonterminal/continuestmt.h>

#include <alpha/icode/quad/table.h>
#include <alpha/syntax/error.h>
#include <alpha/syntax/loop_counter.h>

using namespace alpha::syntax::manager::nonterminal;
using Opcode = alpha::icode::quad::Quad::Opcode;
using Quad = alpha::icode::quad::Quad;

Continuestmt::Continuestmt() : break_list_head(0), continue_list_head(0) {}

Continuestmt Continuestmt::from_continueTkn(const location& loc) {
  Continuestmt continuestmt;

  if (!loopCounter.is_in_loop()) {
    error::invalid_use_of_continue(loc);

  } else {
    continuestmt.continue_list_head = quadTable.get_next_label();
    quadTable.emit(Opcode::JUMP, emptyExpr, emptyExpr, emptyExpr, 0);
  }

  return continuestmt;
}

Quad::Label Continuestmt::get_break_list_head() const {
  return this->break_list_head;
}

void Continuestmt::set_break_list_head(const Quad::Label& label) {
  this->break_list_head = label;
}

Quad::Label Continuestmt::get_continue_list_head() const {
  return this->continue_list_head;
}

void Continuestmt::set_continue_list_head(const Quad::Label& label) {
  this->continue_list_head = label;
}
