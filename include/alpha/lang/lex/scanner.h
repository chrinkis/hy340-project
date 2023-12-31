#pragma once

#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include <alpha/lang/lex/status.h>
#include <alpha/lang/syntax/parser.h>
#include <alpha/lang/token/token.h>

#include <istream>
#include <stack>
#include <string>

namespace alpha {
namespace lex {

class Scanner : public yyFlexLexer {
 public:
  using Token = alpha::token::Token;
  using Status = alpha::lex::status::Status;

 private:
  std::stack<int> comment_stack;
  Token token;
  Status status;

 private:
  bool handle_error(alpha::syntax::Parser::location_type* location);

 public:
  Scanner(std::istream& in) : yyFlexLexer(&in){};
  virtual ~Scanner(){};

 public:
  virtual int alpha_yylex(
      alpha::syntax::Parser::semantic_type* const lval,
      alpha::syntax::Parser::location_type* location);  // implemented by Flex

  Status get_status() { return this->status; };

  Token get_token() { return this->token; };
};

};  // namespace lex
};  // namespace alpha
