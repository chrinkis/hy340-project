#include <alpha/lang/syntax/manager/nonterminal/funcbody_post.h>

#include <alpha/lang/syntax/loop_counter.h>

using namespace alpha::syntax::manager::nonterminal;

void FuncbodyPost::emptyTkn() {
  loopCounter.restore();
}
