#include <alpha/vm/arch/mem/code/table.h>
#include <alpha/vm/arch/mem/consts/consts.h>
#include <alpha/vm/parser/parser.h>

#include <iostream>

using namespace alpha::vm;

using Parser = parser::Parser;
using CodeTable = arch::mem::code::Table;

int main() {
  CodeTable code_table;
  Parser parser(vmConsts, code_table);

  try {
    parser.parse("tcode.txt");
  } catch (std::runtime_error e) {
    std::cerr << e.what() << std::endl;
    exit(1);
  }

  return 0;
}
