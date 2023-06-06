#include <alpha/lang/tcode/abc/consts/consts.h>

namespace alpha::tcode::abc::consts {

UserFunc::UserFunc(const Address& address,
                   const std::string& id,
                   const LocalSize& local_size)
    : address(address), id(id), local_size(local_size) {}

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
  return (this->address == user_func.address) && (this->id == user_func.id) &&
         (this->local_size == user_func.local_size);
}

}  // namespace alpha::tcode::abc::consts
