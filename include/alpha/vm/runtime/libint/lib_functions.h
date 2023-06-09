#pragma once

#include <functional>
#include <map>
#include <utility>

#include <string>

namespace alpha::vm::arch::cpu {
class Cpu;
}

namespace alpha::vm::runtime::libint {
class LibFunctions {
 private:
  using Address = unsigned;
  using Cpu = arch::cpu::Cpu;
  using LibFuncType = std::function<void(Cpu& cpu) noexcept(false)>;

 private:
  std::map<std::string, LibFuncType> lib_funcs;

 public:
  LibFunctions();

 public:
  void call(const std::string& func_name, Cpu& cpu) noexcept(false);
  bool supports_lib_func(const std::string& func_name) const;
};

}  // namespace alpha::vm::runtime::libint
