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

 public:
  Counter get_total_locals() const;
  void set_total_locals(const Counter& total_locals);
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
