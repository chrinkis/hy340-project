#include <alpha/lang/syntax/loop_counter.h>

#include <cassert>

#define CHECK_INVARIANTS \
  { assert(!this->counter.empty()); }

namespace alpha::syntax {

LoopCounter::LoopCounter() {
  this->counter.push(0);

  CHECK_INVARIANTS
}

void LoopCounter::increase() {
  CHECK_INVARIANTS

  this->counter.top()++;

  CHECK_INVARIANTS
}

void LoopCounter::decrease() {
  CHECK_INVARIANTS
  assert(this->is_in_loop());

  this->counter.top()--;

  CHECK_INVARIANTS
}

void LoopCounter::store() {
  CHECK_INVARIANTS

  this->counter.push(0);

  CHECK_INVARIANTS
}

void LoopCounter::restore() {
  CHECK_INVARIANTS

  this->counter.pop();

  CHECK_INVARIANTS
}

bool LoopCounter::is_in_loop() const {
  CHECK_INVARIANTS

  return this->counter.top() != 0;
}

}  // namespace alpha::syntax
