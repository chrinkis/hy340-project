#pragma once

// TODO where this file belongs in the structure?

#include <memory>

namespace alpha::icode {

class Expr {
 public:
  using SharedPtr = std::shared_ptr<Expr>;
};

}  // namespace alpha::icode
