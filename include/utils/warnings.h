#pragma once

#include <iostream>

#ifndef NDEBUG
#define RUNTIME_WARNING_COLOR \
  "\x1B[37m" /*fg*/           \
  "\x1B[41m" /*bg*/
#endif

#ifndef NDEBUG
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
#else
#define WARN_EMPTY_FUNC_IMPL(...)                       \
  {                                                     \
    statstatic_assert(false, "unimplemented function"); \
    ;                                                   \
  }
#endif

#ifndef NDEBUG
#define FIXME                                                    \
  {                                                              \
    _Pragma("message(\"Unfixed `FIXME`\")");                     \
    std::cout << std::endl                                       \
              << RUNTIME_WARNING_COLOR << "***"                  \
              << "[Runtime source code warning] Unfixed `FIXME`" \
              << "***"                                           \
              << "\033[0m" << std::endl;                         \
  }
#else
#define FIXME
#endif
