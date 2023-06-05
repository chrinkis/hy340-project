#include <alpha/vm/arch/mem/consts/user_func.h>

#include <utils/warnings.h>

namespace alpha::vm::arch::mem::consts {

UserFunc::UserFunc(const Address& address,
                   const std::string& id,
                   const LocalSize& local_size) {
  WARN_EMPTY_FUNC_IMPL();
}

UserFunc::Address UserFunc::get_address() const {
  return this->address;
}

const std::string& UserFunc::get_id() const {
  return this->id;
}

UserFunc::LocalSize UserFunc::get_local_size() const {
  return this->local_size;
}

bool UserFunc::operator==(const UserFunc& user_func) const {
  WARN_EMPTY_FUNC_IMPL(false);
}

}  // namespace alpha::vm::arch::mem::consts
