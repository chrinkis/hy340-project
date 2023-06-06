#include <alpha/lang/syntax/manager/nonterminal/loop_end.h>

#include <alpha/lang/syntax/loop_counter.h>

using namespace alpha::syntax::manager::nonterminal;

void LoopEnd::emptyTkn() {
  loopCounter.decrease();
}
