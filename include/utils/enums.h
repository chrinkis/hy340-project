#pragma once

#include <type_traits>

namespace utils::enums {

template <typename Enumeration>
auto to_underlying_value(Enumeration const value) ->
    typename std::underlying_type<Enumeration>::type {
  return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

}  // namespace utils::enums
