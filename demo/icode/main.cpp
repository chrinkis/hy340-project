#include <alpha/icode/quad/table.h>
#include <alpha/lex/scanner.h>
#include <alpha/symbol/table.h>
#include <alpha/symbol/table_manager.h>
#include <alpha/syntax/parser.h>

#include <iostream>

using Scanner = alpha::lex::Scanner;
using Parser = alpha::syntax::Parser;
using Table = alpha::symbol::Table;

int main() {
  Scanner scanner(std::cin);
  Table symbol_table;
  Parser parser(scanner, symbol_table);

  parser.parse();

  std::cout << symTable << std::endl;
  std::cout << quadTable << std::endl;

  return 0;
}
