#include <alpha/vm/arch/mem/consts/consts.h>

#include <utils/warnings.h>

namespace alpha::vm::arch::mem::consts {

void Consts::insert_number(double number) {
  WARN_EMPTY_FUNC_IMPL();
}

void Consts::insert_string(const std::string& string) {
  WARN_EMPTY_FUNC_IMPL();
}

void Consts::insert_lib_func_name(const std::string& lib_func_name) {
  WARN_EMPTY_FUNC_IMPL();
}

void Consts::insert_user_func(const UserFunc& user_func) {
  WARN_EMPTY_FUNC_IMPL();
}

double Consts::number_at(const Index& index) {
  WARN_EMPTY_FUNC_IMPL(0.);
}

const std::string& Consts::string_at(const Index& index) {
  WARN_EMPTY_FUNC_IMPL(
      (this->str_collection.emplace_back("hey"), this->str_collection.at(0)));
}

const std::string& Consts::lib_func_name_at(const Index& index) {
  WARN_EMPTY_FUNC_IMPL((this->lib_func_name_collection.emplace_back("hey"),
                        this->lib_func_name_collection.at(0)));
}

const UserFunc& Consts::user_func_at(const Index& index) {
  WARN_EMPTY_FUNC_IMPL((this->user_func_collection.emplace_back(0, "hey", 0),
                        this->user_func_collection.at(0)));
}

}  // namespace alpha::vm::arch::mem::consts
