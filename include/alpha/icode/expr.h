#pragma once

// TODO where this file belongs in the structure?

#include <alpha/symbol/symbol.h>

#include <memory>
#include <optional>
#include <string>

namespace alpha::icode {

class Expr {
 public:
  using SharedPtr = std::shared_ptr<Expr>;

  using Symbol = symbol::Symbol;

  enum class Type {
    VAR,
    TABLE_ITEM,

    PROGRAM_FUNC,
    LIBRARY_FUNC,

    ARITHM_EXPR,
    BOOL_EXPR,
    ASSIGN_EXPR,
    NEW_TABLE,

    CONST_NUM,
    CONST_BOOL,
    CONST_STRING,

    NIL,
  };

 private:
  Type type;

  std::optional<Symbol::SharedPtr> symbol;
  std::optional<Expr::SharedPtr> index;
  std::optional<double> number_const;
  std::optional<std::string> string_const;
  std::optional<bool> bool_const;

 public:
  // static Expr for_var(const Symbol::SharedPtr& symbol);
  static Expr for_program_func(const Symbol::SharedPtr& symbol);
  // static Expr for_library_func(const Symbol::SharedPtr& symbol);

  // static Expr for_table_item(const Symbol::SharedPtr& symbol,
  //                            const SharedPtr& index);

  // static Expr for_assign_expr(const SharedPtr& other);
  // static Expr for_assign_expr(const Symbol::SharedPtr& symbol);

  // static Expr for_const_num(double number);
  // static Expr for_const_bool(bool value);
  // static Expr for_const_string(const std::string& string);

 public:
  Type get_type() const;

  Symbol::SharedPtr get_symbol() const;
  SharedPtr get_index() const;
  double get_number_const() const;
  std::string get_string_const() const;
  bool get_bool_const() const;
};

}  // namespace alpha::icode
