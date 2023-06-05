#include <alpha/icode/quad/table.h>
#include <alpha/lex/error.h>
#include <alpha/lex/scanner.h>
#include <alpha/symbol/table.h>
#include <alpha/symbol/table_manager.h>
#include <alpha/syntax/error.h>
#include <alpha/syntax/parser.h>
#include <alpha/tcode/abc/table.h>
#include <alpha/tcode/abc/writer.h>

#include <fstream>
#include <iostream>

#define HAS_SYNTAX_ERROR (alpha::syntax::error::found)
#define HAS_LEX_ERROR (alpha::lex::error::found)

using Scanner = alpha::lex::Scanner;
using Parser = alpha::syntax::Parser;
using Table = alpha::symbol::Table;
using Writer = alpha::tcode::abc::Writer;

int main() {
  Scanner scanner(std::cin);
  Table symbol_table;
  Parser parser(scanner, symbol_table);

  parser.parse();

  std::cout << symTable << std::endl;

  if (HAS_LEX_ERROR || HAS_SYNTAX_ERROR) {
    return 1;
  }

  std::ofstream s_quads_txt("quads.txt");
  s_quads_txt << quadTable << std::endl;
  s_quads_txt.close();

  tcodeTable.parse_quad_table(quadTable);

  Writer writer;

  writer.write_text("tcode.txt");
  writer.write_binary("tcode.abc");

  return 0;
}
