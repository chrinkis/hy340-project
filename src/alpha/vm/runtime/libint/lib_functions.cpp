#include <alpha/vm/runtime/libint/lib_functions.h>

#include <alpha/vm/arch/cpu/cpu.h>
#include <alpha/vm/runtime/messages/error.h>
#include <alpha/vm/runtime/table/table.h>

#include <utils/warnings.h>

#include <cassert>
#include <cmath>
#include <iostream>
#include <stdexcept>

#define NUM_ACTUALS_OFFSET arch::cpu::Cpu::NUM_ACTUALS_OFFSET
#define STACK_ENV_SIZE arch::cpu::Cpu::STACK_ENV_SIZE
#define SAVED_TOPSP_OFFSET arch::cpu::Cpu::SAVED_TOPSP_OFFSET

#define RADIAN_UNITS(angle) (((angle) / 180.0) * (double)M_PI)

namespace alpha::vm::runtime::libint {

void print_table(const arch::mem::Cell& cell) {
  using MemCell = arch::mem::Cell;

  assert(cell.get_type() == MemCell::Type::TABLE);

  std::cout << "[";

  for (const auto& pair : cell.get_table()) {
    std::cout << "{";

    if (pair.first.get_type() == MemCell::Type::TABLE) {
      print_table(pair.first);
    } else {
      std::cout << pair.first.to_string();
    }

    std::cout << ": ";

    if (pair.second.get_type() == MemCell::Type::TABLE) {
      print_table(pair.second);
    } else {
      std::cout << pair.second.to_string();
    }

    std::cout << "}, ";
  }

  std::cout << "]";
}

void lib_print(arch::cpu::Cpu& _cpu) noexcept(false) {
  const auto& cpu = _cpu;

  auto n = cpu.get_total_actuals_from_stack();

  for (unsigned i = 0; i < n; i++) {
    const auto& cell = cpu.get_actual_from_stack_at(i);

    if (cell.get_type() == arch::mem::Cell::Type::UNDEF) {
      throw std::invalid_argument("Can't print an undefined value");
    } else if (cell.get_type() == arch::mem::Cell::Type::TABLE) {
      print_table(cell);
    } else {
      std::cout << cell.to_string();
    }

    std::cout << std::endl;
  }
}

void lib_input(arch::cpu::Cpu& cpu) noexcept(false) {
  auto n = cpu.get_total_actuals_from_stack();

  if (n != 0) {
    throw std::invalid_argument(
        "`input` expected `0` arguments, but recieved `" + std::to_string(n) +
        "`");
  }

  char c = std::cin.get();

  cpu.registers.retval.clear();
  std::string char_sequence;

  if (c == '"') {
    c = std::cin.get();
    while (c != '"') {
      char_sequence += c;
      c = std::cin.get();
    }

    cpu.registers.retval = arch::mem::Cell::for_string(char_sequence);

  } else {
    std::cin.putback(c);

    std::getline(std::cin, char_sequence);

    try {
      double number = std::stod(char_sequence);
      cpu.registers.retval = arch::mem::Cell::for_number(number);
      return;
    } catch (std::invalid_argument e) {
      // Try next type
    }

    if (char_sequence == "true") {
      cpu.registers.retval = arch::mem::Cell::for_boolean(true);
    } else if (char_sequence == "false") {
      cpu.registers.retval = arch::mem::Cell::for_boolean(false);
    } else if (char_sequence == "nil") {
      cpu.registers.retval = arch::mem::Cell::for_nil();
    } else {
      cpu.registers.retval = arch::mem::Cell::for_string(char_sequence);
    }
  }
}

void lib_typeof(arch::cpu::Cpu& cpu) noexcept(false) {
  auto n = cpu.get_total_actuals_from_stack();

  if (n != 1) {
    throw std::invalid_argument(
        "`typeof` expected `1` argument, but recieved `" + std::to_string(n) +
        "`");
  }

  const auto& cell = cpu.get_actual_from_stack_at(0);

  if (cell.get_type() == arch::mem::Cell::Type::UNDEF) {
    throw std::invalid_argument("Can't use `typeof` with an undefined value");
  }

  cpu.registers.retval.clear();
  cpu.registers.retval = arch::mem::Cell::for_string(cell.get_type_as_string());
}

void lib_totalarguments(arch::cpu::Cpu& cpu) noexcept(false) {
  auto prev_topsp =
      cpu.get_enviroment_value(cpu.registers.topsp + SAVED_TOPSP_OFFSET);

  cpu.registers.retval.clear();

  if (prev_topsp == cpu.get_global_topsp()) {
    runtime::messages::warning("`totalarguments` called outside a function!");
    cpu.registers.retval = arch::mem::Cell::for_nil();

    return;
  }

  auto value = cpu.get_enviroment_value(prev_topsp + NUM_ACTUALS_OFFSET);
  cpu.registers.retval = arch::mem::Cell::for_number(value);
}

void lib_argument(arch::cpu::Cpu& cpu) noexcept(false) {
  auto prev_topsp =
      cpu.get_enviroment_value(cpu.registers.topsp + SAVED_TOPSP_OFFSET);

  if (prev_topsp == cpu.get_global_topsp()) {
    runtime::messages::warning("`argument` called outside a function!");
    cpu.registers.retval = arch::mem::Cell::for_nil();

    return;
  }

  auto n = cpu.get_total_actuals_from_stack();

  if (n != 1) {
    throw std::invalid_argument(
        "`argument` function expected `1` argument, but recieved `" +
        std::to_string(n) + "`");
  }

  const auto& arg_cell = cpu.get_actual_from_stack_at(0);

  if (arg_cell.get_type() != arch::mem::Cell::Type::NUMBER) {
    throw std::invalid_argument("`argument`'s argument should be number");
  }

  assert(arg_cell.get_type() == arch::mem::Cell::Type::NUMBER);
  unsigned index = arg_cell.get_number();
  FIXME;  // ^^^ Before cast to `unsigned`, check it's an Integer

  auto prev_num_of_args = cpu.get_enviroment_value(prev_topsp + STACK_ENV_SIZE);

  if (index >= prev_num_of_args) {
    throw std::invalid_argument(
        "Requested arg with index `" + std::to_string(index) +
        "` in a function with `" + std::to_string(prev_num_of_args) +
        "` arguments");
  }

  auto requested_arg = cpu.mem.stack[prev_topsp + STACK_ENV_SIZE + index + 1];

  cpu.registers.retval = requested_arg;
}

void lib_strtonum(arch::cpu::Cpu& cpu) noexcept(false) {
  auto n = cpu.get_total_actuals_from_stack();

  if (n != 1) {
    throw std::invalid_argument(
        "`strtonum` expected `1` arguments, but recieved `" +
        std::to_string(n) + "`");
  }

  const auto& cell = cpu.get_actual_from_stack_at(0);

  if (cell.get_type() != arch::mem::Cell::Type::STRING) {
    throw std::invalid_argument("`strtonum`'s argument should be string");
  }

  cpu.registers.retval.clear();

  try {
    double number = std::stod(cell.get_string());
    cpu.registers.retval = arch::mem::Cell::for_number(number);
  } catch (std::invalid_argument e) {
    cpu.registers.retval = arch::mem::Cell::for_nil();
  }
}

void lib_sqrt(arch::cpu::Cpu& cpu) noexcept(false) {
  auto n = cpu.get_total_actuals_from_stack();

  if (n != 1) {
    throw std::invalid_argument(
        "`sqrt` expected `1` arguments, but recieved `" + std::to_string(n) +
        "`");
  }

  const auto& cell = cpu.get_actual_from_stack_at(0);

  if (cell.get_type() != arch::mem::Cell::Type::NUMBER) {
    throw std::invalid_argument("`sqrt`'s argument should be number");
  }

  cpu.registers.retval.clear();

  auto number = cell.get_number();
  if (number >= 0) {
    cpu.registers.retval = arch::mem::Cell::for_number(std::sqrt(number));
  } else {
    cpu.registers.retval = arch::mem::Cell::for_nil();
  }
}

void lib_cos(arch::cpu::Cpu& cpu) noexcept(false) {
  auto n = cpu.get_total_actuals_from_stack();

  if (n != 1) {
    throw std::invalid_argument("`cos` expected `1` arguments, but recieved `" +
                                std::to_string(n) + "`");
  }

  const auto& cell = cpu.get_actual_from_stack_at(0);

  if (cell.get_type() != arch::mem::Cell::Type::NUMBER) {
    throw std::invalid_argument("`cos`'s argument should be number");
  }

  auto angle = cell.get_number();
  cpu.registers.retval.clear();
  cpu.registers.retval =
      arch::mem::Cell::for_number(std::cos(RADIAN_UNITS(angle)));
}

void lib_sin(arch::cpu::Cpu& cpu) noexcept(false) {
  auto n = cpu.get_total_actuals_from_stack();

  if (n != 1) {
    throw std::invalid_argument("`sin` expected `1` arguments, but recieved `" +
                                std::to_string(n) + "`");
  }

  const auto& cell = cpu.get_actual_from_stack_at(0);

  if (cell.get_type() != arch::mem::Cell::Type::NUMBER) {
    throw std::invalid_argument("`sin`'s argument should be number");
  }

  auto angle = cell.get_number();
  cpu.registers.retval.clear();
  cpu.registers.retval =
      arch::mem::Cell::for_number(std::sin(RADIAN_UNITS(angle)));
}

void lib_objectmemberkeys(arch::cpu::Cpu& cpu) noexcept(false) {
  auto n = cpu.get_total_actuals_from_stack();

  if (n != 1) {
    throw std::invalid_argument(
        "`objectmemberkeys` expected `1` arguments, but recieved `" +
        std::to_string(n) + "`");
  }

  const auto& cell = cpu.get_actual_from_stack_at(0);

  if (cell.get_type() != arch::mem::Cell::Type::TABLE) {
    throw std::invalid_argument(
        "`objectmemberkeys`'s argument should be table");
  }

  auto table = cell.get_table();
  table::Table key_table = table::Table::create();

  int current_key = 0;
  for (auto pair : table) {
    auto index = arch::mem::Cell ::for_number(current_key++);
    key_table.set_element(index, pair.first);
  }

  cpu.registers.retval.clear();
  cpu.registers.retval = arch::mem::Cell::for_table(key_table);
}

void lib_objecttotalmembers(arch::cpu::Cpu& cpu) noexcept(false) {
  auto n = cpu.get_total_actuals_from_stack();

  if (n != 1) {
    throw std::invalid_argument(
        "`objecttotalmembers` expected `1` arguments, but recieved `" +
        std::to_string(n) + "`");
  }

  const auto& cell = cpu.get_actual_from_stack_at(0);

  if (cell.get_type() != arch::mem::Cell::Type::TABLE) {
    throw std::invalid_argument(
        "`objecttotalmembers`'s argument should be table");
  }

  auto table = cell.get_table();

  cpu.registers.retval.clear();
  cpu.registers.retval = arch::mem::Cell::for_number(table.get_size());
}

void lib_objectcopy(arch::cpu::Cpu& cpu) noexcept(false) {
  auto n = cpu.get_total_actuals_from_stack();

  if (n != 1) {
    throw std::invalid_argument(
        "`objectcopy` expected `1` arguments, but recieved `" +
        std::to_string(n) + "`");
  }

  const auto& cell = cpu.get_actual_from_stack_at(0);

  if (cell.get_type() != arch::mem::Cell::Type::TABLE) {
    throw std::invalid_argument("`objectcopy`'s argument should be table");
  }

  auto table = cell.get_table();
  table::Table table_copy = table::Table::create();

  for (auto pair : table) {
    table_copy.set_element(pair.first, pair.second);
  }

  cpu.registers.retval.clear();
  cpu.registers.retval = arch::mem::Cell::for_table(table_copy);
}

LibFunctions::LibFunctions()
    : lib_funcs{{"print", lib_print},
                {"input", lib_input},
                {"typeof", lib_typeof},
                {"totalarguments", lib_totalarguments},
                {"argument", lib_argument},
                {"strtonum", lib_strtonum},
                {"sqrt", lib_sqrt},
                {"cos", lib_cos},
                {"sin", lib_sin},
                {"objectmemberkeys", lib_objectmemberkeys},
                {"objecttotalmembers", lib_objecttotalmembers},
                {"objectcopy", lib_objectcopy}} {}

void LibFunctions::call(const std::string& func_name,
                        Cpu& cpu) noexcept(false) {
  auto pair = this->lib_funcs.find(func_name);

  assert(pair != this->lib_funcs.end());
  assert(pair->first == func_name);

  pair->second(cpu);
}

bool LibFunctions::supports_lib_func(const std::string& func_name) const {
  return this->lib_funcs.find(func_name) != this->lib_funcs.end();
}

}  // namespace alpha::vm::runtime::libint
