#pragma once

#define quadTable (alpha::icode::quad::Table::get())

#include <alpha/icode/expr.h>
#include <alpha/icode/quad/quad.h>
#include <alpha/symbol/symbol.h>

#include <ostream>
#include <vector>

namespace alpha::icode::quad {

class Table {
 private:
  using Collection = std::vector<Quad>;

 public:
  static Table& get() {
    static Table quad_table;

    return quad_table;
  }

 private:
  Collection table;

 public:
  void emit(const Quad& quad);

  void emit_assign(const Expr& dest, const Expr& src);
  void emit_add(const Expr& result, const Expr& op_a, const Expr& op_b);
  void emit_sub(const Expr& result, const Expr& op_a, const Expr& op_b);
  void emit_mul(const Expr& result, const Expr& op_a, const Expr& op_b);
  void emit_div(const Expr& result, const Expr& op_a, const Expr& op_b);
  void emit_mod(const Expr& result, const Expr& op_a, const Expr& op_b);
  void emit_and(const Expr& result, const Expr& op_a, const Expr& op_b);
  void emit_or(const Expr& result, const Expr& op_a, const Expr& op_b);
  void emit_if_eq(const Expr& op_a, const Expr& op_b, const Expr& address);
  void emit_if_noteq(const Expr& op_a, const Expr& op_b, const Expr& address);
  void emit_if_lesseq(const Expr& op_a, const Expr& op_b, const Expr& address);
  void emit_if_greatereq(const Expr& op_a,
                         const Expr& op_b,
                         const Expr& address);
  void emit_if_less(const Expr& op_a, const Expr& op_b, const Expr& address);
  void emit_if_greater(const Expr& op_a, const Expr& op_b, const Expr& address);
  void emit_jump(const Expr& address);
  void emit_uminus(const Expr& result, const Expr& operand);
  void emit_not(const Expr& result, const Expr& operand);
  void emit_call(const Expr& expr);
  void emit_param(const Expr& expr);
  void emit_ret();
  void emit_getretval(const Expr& expr);
  void emit_funcstart();
  void emit_funcend(const symbol::Symbol::SharedPtr& function);
  void emit_tablecreate();
  void emit_tablegetelem();
  void emit_tablesetelem(const Expr& table, const Expr& index, const Expr& val);

  icode::Expr emit_if_table_item(const icode::Expr& expr);

  Quad::Label get_next_label() const;

  void patch_label(const Quad::Line& line, const Quad::Label& label);

  void patch_list(const Quad::Line& list_head, const Quad::Label& label);

  Quad& new_list(const Quad::Line& start);

  Quad::Line merge_lists(const Quad::Line& list_head_a,
                         const Quad::Line& list_head_b);

  friend std::ostream& operator<<(std::ostream& os, const Table& qt);
};

}  // namespace alpha::icode::quad
