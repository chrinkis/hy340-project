#include <alpha/lex/scanner.h>
#include <alpha/symbol/table.h>
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

  std::cout << symbol_table << std::endl;

  return 0;
}
