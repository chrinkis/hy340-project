#include <alpha/vm/arch/cpu/cpu.h>
#include <alpha/vm/arch/mem/memory.h>
#include <alpha/vm/parser/parser.h>

#include <iostream>

using namespace alpha::vm;

using Parser = parser::Parser;
using Memory = arch::mem::Memory;
using Cpu = arch::cpu::Cpu;

int main() {
  Memory mem;
  Parser parser(mem.consts, mem.code);

  try {
    parser.parse("tcode.txt");
  } catch (std::runtime_error e) {
    std::cerr << e.what() << std::endl;

    return 1;
  }

  Cpu cpu(mem, parser.get_total_globals());

  return 0;
}
