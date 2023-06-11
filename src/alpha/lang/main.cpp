#include <alpha/lang/icode/quad/table.h>
#include <alpha/lang/lex/error.h>
#include <alpha/lang/lex/scanner.h>
#include <alpha/lang/symbol/table.h>
#include <alpha/lang/symbol/table_manager.h>
#include <alpha/lang/syntax/error.h>
#include <alpha/lang/syntax/parser.h>
#include <alpha/lang/tcode/abc/table.h>
#include <alpha/lang/tcode/abc/writer.h>

#include <fstream>
#include <iostream>

#define HAS_SYNTAX_ERROR (alpha::syntax::error::found)
#define HAS_LEX_ERROR (alpha::lex::error::found)

#define OUTPUT_FILE_NAME "out"

using Scanner = alpha::lex::Scanner;
using Parser = alpha::syntax::Parser;
using Writer = alpha::tcode::abc::Writer;

void check_file_is_open(const std::string& name, const std::ifstream& stream) {
  if (!stream.is_open()) {
    std::cerr << "Can't open file \"" + name + "\" to read!" << std::endl;
    exit(3);
  };
}

void check_file_is_open(const std::string& name, const std::ofstream& stream) {
  if (!stream.is_open()) {
    std::cerr << "Can't open file \"" + name + "\" to write!" << std::endl;
    exit(4);
  };
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Alpha compiler needs one (and only) input file" << std::endl;
    return 5;
  } else if (!argv[1]) {
    std::cerr << "Compiler's `main` function argument failure" << std::endl;
    return 6;
  }
  std::ifstream s_source_code(argv[1]);
  check_file_is_open(argv[1], s_source_code);

  Scanner scanner(s_source_code);
  Parser parser(scanner);

  parser.parse();
  s_source_code.close();

#ifndef NDEBUG
  std::string sym_table_file_name("symTable.txt");
  std::ofstream s_sym_table_txt(sym_table_file_name);
  check_file_is_open(sym_table_file_name, s_sym_table_txt);

  s_sym_table_txt << symTable << std::endl;
  s_sym_table_txt.close();
#endif

  if (HAS_LEX_ERROR || HAS_SYNTAX_ERROR) {
    return 1;
  }

#ifndef NDEBUG
  std::string quads_file_name = "quads.txt";
  std::ofstream s_quads_txt(quads_file_name);
  check_file_is_open(quads_file_name, s_quads_txt);

  s_quads_txt << quadTable << std::endl;
  s_quads_txt.close();
#endif

  tcodeTable.parse_quad_table(quadTable);

  Writer writer;

  try {
    writer.write_text(OUTPUT_FILE_NAME ".txt");
    writer.write_binary(OUTPUT_FILE_NAME ".abc");
  } catch (std::runtime_error e) {
    std::cerr << e.what() << std::endl;
    return 2;
  }

  std::cout << "Compiled succesfully!" << std::endl;

  return 0;
}
