#pragma once

#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

namespace alpha {
namespace lex {

class Scanner : public yyFlexLexer {
 public:
  virtual int yylex(void*);  // implemented by Flex
};

};  // namespace lex
};  // namespace alpha
