#include <alpha/icode/quad/table.h>

#include <alpha/symbol/table_manager.h>

#include <cassert>

namespace alpha::icode::quad {

void Table::emit(const Quad::Opcode& opcode,
                 const ExprOpt& result,
                 const ExprOpt& arg_a,
                 const ExprOpt& arg_b,
                 const QuadLabelOpt& address) {
  Quad quad(opcode, this->get_next_label());

  if (result) {
    quad.set_result(result.value());
  }

  if (arg_a) {
    quad.set_arg1(arg_a.value());
  }

  if (arg_b) {
    quad.set_arg2(arg_b.value());
  }

  if (address) {
    quad.set_label(address.value());
  }

  this->table.push_back(quad);

  assert(quad.get_line() == this->get_next_label() - 1);
}

icode::Expr Table::emit_if_table_item(const icode::Expr& expr) {
  if (expr.get_type() != Expr::Type::TABLE_ITEM) {
    return expr;
  }

  Expr result = Expr::for_var(symTable.new_temp_variable());
  this->emit(Quad::Opcode::TABLEGETELEM, result, expr, *expr.get_index());

  return result;
}

Quad::Label Table::get_next_label() const {
  return this->table.size();
}

void Table::patch_label(const Quad::Line& line, const Quad::Label& label) {
  assert(line < this->get_next_label() - 1);
  assert(!this->table.at(line).get_label());

  this->table.at(line).set_label(label);
}

void Table::patch_list(const Quad::Line& list_head, const Quad::Label& label) {
  Quad::Line current = list_head;

  while (current) {
    Quad::Line next = this->table.at(current).get_label();

    this->table.at(current).set_label(label);

    current = next;
  }
}

std::ostream& operator<<(std::ostream& os, const Table& qt) {
  os << std::left;

  for (auto quad : qt.table) {
    os << quad << std::endl;
  }

  return os;
}

}  // namespace alpha::icode::quad
