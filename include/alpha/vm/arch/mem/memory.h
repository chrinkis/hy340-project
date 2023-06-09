#pragma once

#include <alpha/vm/arch/mem/code/table.h>
#include <alpha/vm/arch/mem/consts/consts.h>
#include <alpha/vm/arch/mem/stack/stack.h>

namespace alpha::vm::arch::mem {

/**
 * @brief This struct just groups the parts of the memory
 */
struct Memory {
  using Code = arch::mem::code::Table;
  using Consts = arch::mem::consts::Consts;
  using Stack = arch::mem::stack::Stack;

  Code code;
  Consts consts;
  Stack stack;
};

}  // namespace alpha::vm::arch::mem
