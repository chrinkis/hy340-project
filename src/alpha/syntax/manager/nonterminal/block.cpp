#include <alpha/syntax/handler/block.h>
#include <alpha/syntax/manager/nonterminal/block.h>

using namespace alpha::syntax::manager::nonterminal;

void Block::leftCurlyBracketTkn() {
  handlers::block::enter();
}

void Block::rightCurlyBracketTkn() {
  handlers::block::exit();
}
