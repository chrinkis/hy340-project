#pragma once

#include <string>

namespace alpha::vm::runtime::messages {

void error(const std::string& message);

void warning(const std::string& message);

}  // namespace alpha::vm::runtime::messages
