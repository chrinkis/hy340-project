#pragma once

#include <alpha/syntax/parser.h>

#include <string>

namespace alpha::lex::error {

extern bool found;  // TODO find better solution

void print(const std::string& message,
           const alpha::syntax::Parser::location_type& location);

}  // namespace alpha::lex::error
