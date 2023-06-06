#pragma once

// TODO where this file belongs in the structure?

#include <alpha/lang/symbol/symbol.h>

#include <memory>
#include <optional>
#include <ostream>
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

    _NO_TYPE
  };

 private:
  Type type;

  std::optional<Symbol::SharedPtr> symbol;
  std::optional<Expr::SharedPtr> index;
  std::optional<double> number_const;
  std::optional<std::string> string_const;
  std::optional<bool> bool_const;

 public:
  Expr();

 public:
  static Expr for_var(const Symbol::SharedPtr& symbol);
  static Expr for_program_func(const Symbol::SharedPtr& symbol);
  static Expr for_library_func(const Symbol::SharedPtr& symbol);

  static Expr for_table_item(const Expr& symbol_expr, const Expr& index);
  static Expr for_new_table(const Symbol::SharedPtr& symbol);

  static Expr for_assign_expr(const Expr& other);
  static Expr for_assign_expr(const Symbol::SharedPtr& symbol);

  static Expr for_arithm_expr(const Symbol::SharedPtr& symbol);
  static Expr for_bool_expr(const Symbol::SharedPtr& symbol);

  static Expr for_const_num(double number);
  static Expr for_const_bool(bool value);
  static Expr for_const_string(const std::string& string);

  static Expr for_nil();

 public:
  Type get_type() const;

  bool has_symbol() const;
  Symbol::SharedPtr get_symbol() const;

  bool has_index() const;
  SharedPtr get_index() const;

  bool has_number_const() const;
  double get_number_const() const;

  bool has_string_const() const;
  std::string get_string_const() const;

  bool has_bool_const() const;
  bool get_bool_const() const;

 public:
  friend std::ostream& operator<<(std::ostream& os, const Expr& expr);
};

}  // namespace alpha::icode
