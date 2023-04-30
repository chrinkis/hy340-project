#include <alpha/syntax/handler/block.h>
#include <alpha/syntax/manager/nonterminal/block.h>

using namespace alpha::syntax::manager::nonterminal;
using alpha::syntax::handlers::block::enter;
using alpha::syntax::handlers::block::exit;

void Block::leftCurlyBracketTkn() {
  enter();
}

void Block::rightCurlyBracketTkn() {
  exit();
}
