#pragma once

#define quadTable (alpha::icode::quad::Table::get())

#include <alpha/icode/expr.h>
#include <alpha/icode/quad/quad.h>

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

  void emit_assign();
  void emit_add();
  void emit_sub();
  void emit_mul();
  void emit_div();
  void emit_mod();
  void emit_uminus();
  void emit_and();
  void emit_or();
  void emit_not();
  void emit_if_eq();
  void emit_if_noteq();
  void emit_if_lesseq();
  void emit_if_greatereq();
  void emit_if_less();
  void emit_if_greater();
  void emit_jump();
  void emit_call();
  void emit_param();
  void emit_ret();
  void emit_getretval();
  void emit_funcstart();
  void emit_funcend();
  void emit_tablecreate();
  void emit_tablegetelem();
  void emit_tablesetelem();

  icode::Expr emit_if_table_item(const icode::Expr& expr);

  Quad::Label get_next_label() const;

  void patch_label(const Quad::Line& line, const Quad::Label& label);

  friend std::ostream& operator<<(std::ostream& os, const Table& qt);
};

}  // namespace alpha::icode::quad
