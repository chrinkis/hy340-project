#include <alpha/syntax/manager/nonterminal/funcbody_post.h>

#include <alpha/syntax/loop_counter.h>

using namespace alpha::syntax::manager::nonterminal;

void FuncbodyPost::emptyTkn() {
  loopCounter.restore();
}
