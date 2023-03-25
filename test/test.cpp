#include <cassert>
#include <catch2/catch_test_macros.hpp>

#include <alpha/lex/scanner.h>
#include <alpha/syntax/parser.h>
#include <alpha/token/token.h>

#include <fstream>
#include <iostream>
#include <string>

using Scanner = alpha::lex::Scanner;
using Parser = alpha::syntax::Parser;
using Category = alpha::token::Token::Category;

static std::string file_path = "../../test/phase1_tests/";

static int next(Scanner& scanner) {
  return scanner.yylex(nullptr, nullptr);
}
