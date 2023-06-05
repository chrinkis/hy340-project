#pragma once

#include <string>

namespace alpha::vm::runtime::libint {

class LibFunctions {
 private:
  using Address = unsigned;

 public:
  LibFunctions();

 public:
  void load_lib_func(const std::string& func_name);
  void call(const std::string& func_name);
};

}  // namespace alpha::vm::runtime::libint
