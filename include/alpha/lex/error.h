#pragma once

#include <alpha/syntax/parser.h>

#include <string>

namespace alpha::lex::error {

void print(const std::string& message,
           const alpha::syntax::Parser::location_type& location);

}
