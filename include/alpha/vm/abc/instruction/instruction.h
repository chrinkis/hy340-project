#pragma once

#include <alpha/vm/abc/instruction/arg.h>
#include <alpha/vm/abc/instruction/opcode.h>

namespace alpha::vm::abc::instruction {

class Instruction {
 public:
  using SrcLine = unsigned;

 private:
  Opcode opcode;

  Arg result;
  Arg arg_a;
  Arg arg_b;

  SrcLine src_line;

 public:
  Instruction(const SrcLine& src_line,
              const Opcode& opcode,
              const Arg& result,
              const Arg& arg_a,
              const Arg& arg_b);

  Instruction(const Instruction& instruction);

 public:
  Opcode get_opcode() const;

  Arg get_result() const;

  Arg get_arg_a() const;

  Arg get_arg_b() const;

  SrcLine get_src_line() const;
};

}  // namespace alpha::vm::abc::instruction
