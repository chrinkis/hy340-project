#pragma once

namespace alpha::tcode::abc::instruction {

enum class Opcode {
  assign,
  ADD,
  SUB,
  MUL,
  DIV,
  MOD,
  UMINUS,
  AND,
  OR,
  NOT,
  JUMP,
  JEQ,
  JNE,
  JLE,
  JGE,
  JLT,
  JGT,
  CALL,
  PUSH_ARG,
  FUNC_ENTER,
  FUNC_EXIT,
  NEW_TABLE,
  TABLE_GET_ELEM,
  TABLE_SET_ELEM,
  NOP,
};

}  // namespace alpha::tcode::abc::instruction
