#include <alpha/syntax/manager/nonterminal/block_close.h>

#include <alpha/syntax/handler/block.h>

using namespace alpha::syntax::manager::nonterminal;
namespace block = alpha::syntax::handlers::block;

void BlockClose::rightCurlyBracketTkn() {
  block::exit();
}
