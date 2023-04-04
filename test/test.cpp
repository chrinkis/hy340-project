#include <cassert>
#include <catch2/catch_test_macros.hpp>

#include <alpha/lex/scanner.h>
#include <alpha/syntax/location.h>
#include <alpha/syntax/parser.h>
#include <alpha/token/token.h>

#include <fstream>
#include <iostream>
#include <string>

using Scanner = alpha::lex::Scanner;
using Parser = alpha::syntax::Parser;
using Category = alpha::token::Token::Category;
using Location = alpha::syntax::location;

static std::string file_path = "../../test/phase1_tests/";

static alpha::syntax::Parser::semantic_type lval;

static int next(Scanner& scanner, Location& location) {
  return scanner.alpha_yylex(&lval, &location);
}

TEST_CASE("comments", "") {
  std::ifstream input(file_path + "comments.alpha");
  REQUIRE(input.good());

  Scanner scanner(input);
  Location location;

  CHECK(next(scanner, location) == Category::IDENTIFIER);
  CHECK(next(scanner, location) == Category::END_OF_FILE);

  input.close();
}
