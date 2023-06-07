#pragma once

#define vmConsts (alpha::vm::arch::mem::consts::Consts::get())

#include <alpha/vm/arch/mem/consts/user_func.h>

#include <string>
#include <vector>

namespace alpha::vm::arch::mem::consts {

class Consts {
 public:
  using Index = unsigned;

 private:
  using NumCollection = std::vector<double>;
  using StrCollection = std::vector<std::string>;
  using LibFuncNameCollection = std::vector<std::string>;
  using UserFuncCollection = std::vector<UserFunc>;

 public:
  static Consts& get() {
    static Consts tcode_consts;

    return tcode_consts;
  }

 private:
  NumCollection num_collection;
  StrCollection str_collection;
  LibFuncNameCollection lib_func_name_collection;
  UserFuncCollection user_func_collection;

 public:
  void insert_number(double number);
  void insert_string(const std::string& string);
  void insert_lib_func_name(const std::string& lib_func_name);
  void insert_user_func(const UserFunc& user_func);

  double number_at(const Index& index);
  const std::string& string_at(const Index& index);
  const std::string& lib_func_name_at(const Index& index);
  const UserFunc& user_func_at(const Index& index);
};

}  // namespace alpha::vm::arch::mem::consts
