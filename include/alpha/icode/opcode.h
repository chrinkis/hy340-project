#pragma once

namespace alpha::icode {

enum class Opcode {
  ASSIGN,
  ADD,
  SUB,
  MUL,
  DIV,
  MOD,
  UMINUS,
  AND,
  OR,
  NOT,
  IF_EQ,
  IF_NOTEQ,
  IF_LESSEQ,
  IF_GREATEREQ,
  IF_LESS,
  IF_GREATER,
  CALL,
  PARAM,
  RET,
  GETRETVAL,
  FUNCSTART,
  FUNCEND,
  TABLECREATE,
  TABLEGETELEM,
  TABLESETELEM,
};

}
