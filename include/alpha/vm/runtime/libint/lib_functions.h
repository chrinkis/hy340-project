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

void lib_print(arch::cpu::Cpu& _cpu) noexcept(false);
void lib_input(arch::cpu::Cpu& _cpu) noexcept(false);
void lib_typeof(arch::cpu::Cpu& _cpu) noexcept(false);
void lib_argument(arch::cpu::Cpu& _cpu) noexcept(false);
void lib_totalarguments(arch::cpu::Cpu& _cpu) noexcept(false);
void lib_strtonum(arch::cpu::Cpu& _cpu) noexcept(false);
void lib_sqrt(arch::cpu::Cpu& _cpu) noexcept(false);
void lib_cos(arch::cpu::Cpu& _cpu) noexcept(false);
void lib_sin(arch::cpu::Cpu& _cpu) noexcept(false);

}  // namespace alpha::vm::runtime::libint
