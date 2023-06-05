#include <alpha/lang/lex/error.h>

#include <iostream>
#include <string>

#define ERROR_COLOR "\033[91m"
#define DEFAULT_COLOR "\033[0m"

namespace alpha::lex::error {

bool found = false;  // TODO find better solution

void print(const std::string& message,
           const alpha::syntax::Parser::location_type& location) {
  std::cerr << ERROR_COLOR << "lexicographic error, " << message << " at ("
            << "line: " << location.begin.line
            << ", column: " << location.begin.column << ")" << std::endl
            << DEFAULT_COLOR;

  found = true;
}

}  // namespace alpha::lex::error
