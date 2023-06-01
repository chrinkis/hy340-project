#pragma once

#include <iostream>

#define RUNTIME_WARNING_COLOR \
  "\x1B[37m" /*fg*/           \
  "\x1B[41m" /*bg*/

#define WARN_EMPTY_FUNC_IMPL(...)                                              \
  {                                                                            \
    _Pragma("message(\"Use of unimplemented function\")");                     \
    std::cout << std::endl                                                     \
              << RUNTIME_WARNING_COLOR << "***"                                \
              << "[Runtime source code warning] unimplemented function called" \
              << "***"                                                         \
              << "\033[0m" << std::endl;                                       \
    __VA_OPT__(return __VA_ARGS__;)                                            \
  }
