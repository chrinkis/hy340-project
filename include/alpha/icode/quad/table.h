#pragma once

#define quadTable (alpha::icode::quad::Table::get())
#define emptyExpr (alpha::icode::quad::Table::EmptyExpr())

#include <alpha/icode/expr.h>
#include <alpha/icode/quad/quad.h>
#include <alpha/symbol/symbol.h>

#include <optional>
#include <ostream>
#include <string>
#include <vector>

namespace alpha::icode::quad {

class Table {
 private:
  using Collection = std::vector<Quad>;

  using ExprOpt = std::optional<Expr>;
  using QuadLabelOpt = std::optional<Quad::Label>;

 public:
  static ExprOpt EmptyExpr() {
    static ExprOpt expr_opt;

    return expr_opt;
  }

  static const QuadLabelOpt EmptyLabel() {
    static QuadLabelOpt quad_label_opt;

    return quad_label_opt;
  }

 public:
  static Table& get() {
    static Table quad_table;

    return quad_table;
  }

 private:
  Collection table;

 public:
  Table();

  void emit(const Quad::Opcode& opcode,
            const ExprOpt& result = EmptyExpr(),
            const ExprOpt& arg_a = EmptyExpr(),
            const ExprOpt& arg_b = EmptyExpr(),
            const QuadLabelOpt& address = EmptyLabel());

  icode::Expr emit_if_table_item(const icode::Expr& expr);

  Quad::Label get_next_label() const;

  void patch_label(const Quad::Line& line, const Quad::Label& label);

  void patch_list(const Quad::Line& list_head, const Quad::Label& label);

  Quad::Line merge_lists(const Quad::Line& list_head_a,
                         const Quad::Line& list_head_b);

  friend std::ostream& operator<<(std::ostream& os, const Table& qt);

 public: /* Iterators */
  using ConstIterator = Collection::const_iterator;

  ConstIterator begin() const;
  ConstIterator end() const;
};

}  // namespace alpha::icode::quad
