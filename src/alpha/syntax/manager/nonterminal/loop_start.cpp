#include <alpha/syntax/manager/nonterminal/loop_start.h>

#include <alpha/syntax/loop_counter.h>

using namespace alpha::syntax::manager::nonterminal;

void LoopStart::emptyTkn() {
  loopCounter.increase();
}
