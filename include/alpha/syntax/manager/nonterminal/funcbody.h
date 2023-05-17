#pragma once

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class Funcbody {
 public:
  using Counter = unsigned;

 private:
  Counter total_locals;

 public:
  static void block();
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
