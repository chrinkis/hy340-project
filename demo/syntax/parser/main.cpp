#include <alpha/lex/scanner.h>
#include <alpha/syntax/parser.h>

#include <iostream>

using Scanner = alpha::lex::Scanner;
using Parser = alpha::syntax::Parser;

int main() {
  Scanner scanner(std::cin);
  Parser parser(scanner);

  parser.parse();

  return 0;
}
