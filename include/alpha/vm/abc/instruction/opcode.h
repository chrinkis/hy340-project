#pragma once

namespace alpha::vm::abc::instruction {

enum class Opcode : char {
  ASSIGN,
  ADD,
  SUB,
  MUL,
  DIV,
  MOD,
  UMINUS,
  CALL,
  FUNC_ENTER,
  FUNC_EXIT,
  AND,
  OR,
  NOT,
  JUMP,
  JEQ,
  JNE,
  JGT,
  JLT,
  JGE,
  JLE,
  NEW_TABLE,
  TABLE_GET_ELEM,
  TABLE_SET_ELEM,
  PUSH_ARG,
  NOP,
};

}  // namespace alpha::vm::abc::instruction
