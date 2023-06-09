#include <alpha/vm/arch/cpu/cpu.h>
#include <alpha/vm/arch/mem/code/table.h>
#include <alpha/vm/arch/mem/consts/consts.h>
#include <alpha/vm/arch/mem/stack/stack.h>
#include <alpha/vm/parser/parser.h>

#include <iostream>

using namespace alpha::vm;

using Parser = parser::Parser;
using CodeTable = arch::mem::code::Table;
using Consts = arch::mem::consts::Consts;
using Stack = arch::mem::stack::Stack;
using Cpu = arch::cpu::Cpu;

int main() {
  struct {
    CodeTable code;
    Consts consts;
    Stack stack;
  } mem;

  Parser parser(mem.consts, mem.code);

  try {
    parser.parse("tcode.txt");
  } catch (std::runtime_error e) {
    std::cerr << e.what() << std::endl;

    return 1;
  }

  Cpu cpu(mem.stack, mem.consts, mem.code, parser.get_total_globals());

  return 0;
}
