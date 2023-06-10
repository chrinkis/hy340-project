#include <alpha/vm/arch/cpu/cpu.h>
#include <alpha/vm/arch/mem/memory.h>
#include <alpha/vm/loader/loader.h>
#include <alpha/vm/runtime/libint/lib_functions.h>

#include <iostream>

using namespace alpha::vm;

using Loader = loader::Loader;
using Memory = arch::mem::Memory;
using Cpu = arch::cpu::Cpu;
using LibFuncs = runtime::libint::LibFunctions;

int main() {
  Memory mem;
  Loader loader(mem.consts, mem.code);

  try {
    loader.load_from("tcode.abc");
  } catch (std::runtime_error e) {
    std::cerr << e.what() << std::endl;

    return 1;
  }

  LibFuncs lib_funcs;

  Cpu cpu(mem, lib_funcs, loader.get_total_globals());

  while (!cpu.has_finished()) {
    cpu.execute_cycle();
  }

  return 0;
}
