#pragma once

#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include <alpha/token/token.h>

#include <stack>

namespace alpha {
namespace lex {

class Scanner : public yyFlexLexer {
  std::stack<int> comment_stack;

 public:
  virtual int yylex(alpha::token::Token& token);  // implemented by Flex
};

};  // namespace lex
};  // namespace alpha
