#include <alpha/vm/runtime/table/table.h>

#include <utils/warnings.h>

namespace alpha::vm::runtime::table {

_Table::_Table() {
  WARN_EMPTY_FUNC_IMPL();
}

_Table::SharedPtr _Table::create() {
  WARN_EMPTY_FUNC_IMPL(_Table::SharedPtr());
}

void _Table::increase_counter() {
  WARN_EMPTY_FUNC_IMPL();
}

void _Table::deccrease_counter() {
  WARN_EMPTY_FUNC_IMPL();
}

}  // namespace alpha::vm::runtime::table
