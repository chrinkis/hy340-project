#include <alpha/vm/arch/cpu/cpu.h>

#include <alpha/vm/runtime/messages/error.h>

#include <utils/warnings.h>

#include <cassert>
#include <stdexcept>

namespace alpha::vm::arch::cpu {

void Cpu::execute_jump(const AbcInstruction& instr) {
  assert(instr.get_result().get_type() == abc::instruction::Arg::Type::LABEL);

  this->pc = instr.get_result().get_value();

  assert(this->pc < this->mem.code.get_size());
}

static bool operator==(const mem::Cell& a, const mem::Cell& b) noexcept(false) {
  if (a.get_type() == mem::Cell::Type::UNDEF ||
      b.get_type() == mem::Cell::Type::UNDEF) {
    throw std::invalid_argument("`undef` invlolved in comparation");
  }

  if (a.get_type() == mem::Cell::Type::BOOLEAN ||
      b.get_type() == mem::Cell::Type::BOOLEAN) {
    return a.to_bool() == b.to_bool();
  }

  if (a.get_type() == mem::Cell::Type::NIL ||
      b.get_type() == mem::Cell::Type::NIL) {
    return a.get_type() == mem::Cell::Type::NIL &&
           b.get_type() == mem::Cell::Type::NIL;
  }

  if (a.get_type() != b.get_type()) {
    throw std::invalid_argument(
        "invalid pair-of-types invlolved in comparation");
  }

  assert(a.get_type() == b.get_type());

  switch (a.get_type()) {
    case mem::Cell::Type::NUMBER: {
      return a.get_number() == b.get_number();
    }
    case mem::Cell::Type::STRING: {
      return a.get_string() == b.get_string();
    }
    case mem::Cell::Type::TABLE: {
      return a.get_table() == b.get_table();
    }
    case mem::Cell::Type::USER_FUNC: {
      return a.get_user_func() == b.get_user_func();
    }
    case mem::Cell::Type::LIB_FUNC: {
      return a.get_lib_func() == b.get_lib_func();
    }
    case mem::Cell::Type::BOOLEAN:
    case mem::Cell::Type::NIL:
    case mem::Cell::Type::UNDEF:
    default:
      assert(0);
      return false;
  }

  assert(0);
}

static bool operator>(const mem::Cell& a, const mem::Cell& b) noexcept(false) {
  if (a.get_type() != mem::Cell::Type::NUMBER ||
      b.get_type() != mem::Cell::Type::NUMBER) {
    throw std::invalid_argument("expected numbers in comparation");
  }

  assert(a.get_type() == mem::Cell::Type::NUMBER);
  assert(b.get_type() == mem::Cell::Type::NUMBER);

  return a.get_number() > b.get_number();
}

static bool operator>=(const mem::Cell& a, const mem::Cell& b) noexcept(false) {
  if (a.get_type() != mem::Cell::Type::NUMBER ||
      b.get_type() != mem::Cell::Type::NUMBER) {
    throw std::invalid_argument("expected numbers in comparation");
  }

  assert(a.get_type() == mem::Cell::Type::NUMBER);
  assert(b.get_type() == mem::Cell::Type::NUMBER);

  return a.get_number() >= b.get_number();
}

void Cpu::execute_cmp_jump(
    const AbcInstruction& instr,
    const std::function<bool(const mem::Cell&,
                             const mem::Cell&) noexcept(false)>& compare) {
  assert(instr.get_result().get_type() == abc::instruction::Arg::Type::LABEL);

  mem::Cell& rv_a =
      this->translate_arg_to_cell(instr.get_arg_a(), this->registers.arg_a);

  mem::Cell& rv_b =
      this->translate_arg_to_cell(instr.get_arg_b(), this->registers.arg_b);

  try {
    if (compare(rv_a, rv_b)) {
      this->pc = instr.get_result().get_value();
      assert(this->pc < this->mem.code.get_size());
    }
  } catch (const std::invalid_argument& err) {
    runtime::messages::error("Invalid comparation with `" + rv_a.to_string() +
                             "` and `" + rv_b.to_string() + "`!");
    this->execution_finished = true;

    return;
  }
}

void Cpu::execute_jeq(const AbcInstruction& instr) {
  this->execute_cmp_jump(instr, [](auto a, auto b) { return a == b; });
}

void Cpu::execute_jne(const AbcInstruction& instr) {
  this->execute_cmp_jump(instr, [](auto a, auto b) { return !(a == b); });
}

void Cpu::execute_jle(const AbcInstruction& instr) {
  this->execute_cmp_jump(instr, [](auto a, auto b) { return !(a > b); });
}

void Cpu::execute_jge(const AbcInstruction& instr) {
  this->execute_cmp_jump(instr, [](auto a, auto b) { return a >= b; });
}

void Cpu::execute_jlt(const AbcInstruction& instr) {
  this->execute_cmp_jump(instr, [](auto a, auto b) { return !(a >= b); });
}

void Cpu::execute_jgt(const AbcInstruction& instr) {
  this->execute_cmp_jump(instr, [](auto a, auto b) { return a > b; });
}

}  // namespace alpha::vm::arch::cpu
