#include <alpha/syntax/manager/nonterminal/funcbody_pre.h>

#include <alpha/syntax/loop_counter.h>

using namespace alpha::syntax::manager::nonterminal;

void FuncbodyPre::emptyTkn() {
  loopCounter.store();
}
