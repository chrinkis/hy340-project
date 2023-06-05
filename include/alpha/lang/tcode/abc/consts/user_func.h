#pragma once

#include <string>

namespace alpha::tcode::abc::consts {

class UserFunc {
 public:
  using Address = unsigned;
  using LocalSize = unsigned;

 private:
  Address address;
  std::string id;
  LocalSize local_size;

 public:
  UserFunc(const Address& address,
           const std::string& id,
           const LocalSize& local_size);

  Address get_address() const;
  const std::string& get_id() const;
  LocalSize get_local_size() const;

 public:
  bool operator==(const UserFunc& user_func) const;
};

}  // namespace alpha::tcode::abc::consts
