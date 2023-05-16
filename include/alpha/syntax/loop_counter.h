#pragma once

#define loopCounter (LoopCounter::get())

#include <stack>

namespace alpha::syntax {

class LoopCounter {
 public:
  static LoopCounter get() {
    static LoopCounter loop_counter;

    return loop_counter;
  }

 private:
  using Counter = unsigned;

 private:
  std::stack<Counter> counter;

 public:
  void increase();
  void decrease();
  void store();
  void restore();

  bool is_in_loop() const;
};

}  // namespace alpha::syntax
