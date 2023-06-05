#pragma once

#define tcodeConsts (alpha::tcode::abc::consts::Consts::get())

#include <alpha/lang/tcode/abc/consts/user_func.h>

#include <string>
#include <vector>

namespace alpha::tcode::abc::consts {

class Consts {
 private:
  using Index = unsigned;

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
  Index number(double number);
  Index string(const std::string& string);
  Index lib_func_name(const std::string& lib_func_name);
  Index user_func(const UserFunc& user_func);

  const NumCollection& get_numbers() const;
  const StrCollection& get_strings() const;
  const LibFuncNameCollection& get_lib_func_names() const;
  const UserFuncCollection& get_user_funcs() const;
};

}  // namespace alpha::tcode::abc::consts
