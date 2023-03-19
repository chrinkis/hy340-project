#pragma once

#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include <alpha/lex/status.h>
#include <alpha/token/token.h>

#include <stack>

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

 public:
  virtual int yylex();  // implemented by Flex

  Status get_status() { return this->status; };

  Token get_token() { return this->token; };
};

};  // namespace lex
};  // namespace alpha
