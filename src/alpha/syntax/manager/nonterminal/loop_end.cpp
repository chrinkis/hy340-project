#include <alpha/syntax/manager/nonterminal/loop_end.h>

#include <alpha/syntax/loop_counter.h>

using namespace alpha::syntax::manager::nonterminal;

void LoopEnd::emptyTkn() {
  loopCounter.decrease();
}
