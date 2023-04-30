#pragma once

#include <alpha/syntax/holder/Symbol.h>

namespace alpha {
namespace syntax {
namespace handlers {
namespace symbol {

void continue_checking(holder::Symbol& symbol_holder,
                       const holder::Symbol& previous);

void stop_checking(holder::Symbol& symbol_holder);

}  // namespace symbol
}  // namespace handlers
}  // namespace syntax
}  // namespace alpha