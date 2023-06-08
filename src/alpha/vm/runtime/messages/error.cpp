#include <alpha/vm/runtime/messages/error.h>

#include <iostream>

#define ERROR_COLOR "\033[31m"
#define WARNING_COLOR "\033[33m"
#define DEFAULT_COLOR "\033[0m"

namespace alpha::vm::runtime::messages {

void error(const std::string& message) {
  std::cerr << ERROR_COLOR << "[Runtime Error]  " << message << DEFAULT_COLOR
            << std::endl;
}

void warning(const std::string& message) {
  std::cerr << WARNING_COLOR << "[Runtime Warning]  " << message
            << DEFAULT_COLOR << std::endl;
}

}  // namespace alpha::vm::runtime::messages
