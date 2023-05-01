#include <alpha/syntax/error.h>

#include <iostream>
#include <string>

#define ERROR_COLOR "\033[31m"
#define DEFAULT_COLOR "\033[0m"

namespace alpha::syntax::error {

void print(const std::string& message,
           const alpha::syntax::Parser::location_type& location) {
  std::cerr << ERROR_COLOR << message << " at ("
            << "line: " << location.begin.line
            << ", column: " << location.begin.column << ")" << std::endl
            << DEFAULT_COLOR;
}

void print_semantic(const std::string& message,
                    const alpha::syntax::Parser::location_type& location) {
  std::cerr << ERROR_COLOR << "semantic error, " << message << " at ("
            << "line: " << location.begin.line
            << ", column: " << location.begin.column << ")" << std::endl
            << DEFAULT_COLOR;
}

void print_semantic(const std::string& message) {
  std::cerr << ERROR_COLOR << "semantic error, " << message << std::endl
            << DEFAULT_COLOR;
}

}  // namespace alpha::syntax::error
