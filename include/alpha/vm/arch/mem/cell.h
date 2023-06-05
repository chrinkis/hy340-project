#pragma once

#include <alpha/vm/runtime/table/table.h>

#include <memory>
#include <string>
#include <variant>

namespace alpha::vm::arch::mem {

class Cell {
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

  std::variant<double,                 // number
               std::string,            // string
               bool,                   // boolean
               runtime::table::Table,  // table
               unsigned,               // func_val
               std::string>            // lib_func
      data;

 private:
  Cell(const Type& type);

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
  static Cell for_func_val(unsigned func_no);
  static Cell for_lib_func(const std::string& func_name);
  static Cell for_nil();

  Type get_type() const;
  std::string get_type_as_string() const;

  double get_number() const;
  std::string get_string() const;
  bool get_boolean() const;
  runtime::table::Table get_table() const;
  unsigned get_func_val() const;
  std::string get_lib_func() const;
};

}  // namespace alpha::vm::arch::mem
