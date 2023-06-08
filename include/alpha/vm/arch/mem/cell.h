#pragma once

#include <alpha/vm/arch/mem/consts/consts.h>
#include <alpha/vm/runtime/table/table.h>

#include <memory>
#include <string>
#include <variant>

namespace alpha::vm::arch::mem {

class Cell {
 private:
  using Variant =
      std::variant<std::monostate,         // empty (nil/undef/uninitialized)
                   double,                 // number
                   std::string,            // string
                   bool,                   // boolean
                   runtime::table::Table,  // table
                   consts::UserFunc,       // user_func
                   std::string>;           // lib_func
 public:
  enum class Type {
    NUMBER = 0,
    STRING = 1,
    BOOLEAN = 2,
    TABLE = 3,
    USER_FUNC = 4,
    LIB_FUNC = 5,
    NIL = 6,
    UNDEF = 7,
  };

 private:
  Type type;

  Variant data;

 public:
  Cell();
  Cell(const Cell& cell);

  Cell& operator=(const Cell& cell);  // NOTE! returns itself
  std::string to_string() const;
  bool to_bool() const;

  void clear();

 public:
  static Cell for_number(double number);
  static Cell for_string(const std::string& string);
  static Cell for_boolean(bool boolean);
  static Cell for_table(const runtime::table::Table& table);
  static Cell for_user_func(const consts::UserFunc& user_func);
  static Cell for_lib_func(const std::string& func_name);
  static Cell for_nil();
  static Cell for_undef();

  Type get_type() const;
  std::string get_type_as_string() const;

  double get_number() const;
  std::string get_string() const;
  bool get_boolean() const;
  runtime::table::Table get_table() const;
  consts::UserFunc get_user_func() const;
  std::string get_lib_func() const;
};

}  // namespace alpha::vm::arch::mem
