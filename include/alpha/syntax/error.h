#pragma once

#include <alpha/syntax/parser.h>

#include <string>

namespace alpha::syntax::error {

void print(const std::string& message,
           const alpha::syntax::Parser::location_type& location);

void print_semantic(const std::string& message,
                    const alpha::syntax::Parser::location_type& location);

void print_semantic(const std::string& message);

}  // namespace alpha::syntax::error
