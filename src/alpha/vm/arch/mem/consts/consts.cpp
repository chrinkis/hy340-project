#include <alpha/vm/arch/mem/consts/consts.h>

#include <algorithm>

#define ITERATOR_TYPE(collection) decltype(collection)::iterator

#define FIND_ELEMENT(collection, element) \
  (std::find((collection).begin(), (collection).end(), (element)))

#define INDEX(collection, iterator) \
  (std::distance((collection).begin(), (iterator)))

#define INSERT_TO_SET_COLLECTION(element, collection)                     \
  {                                                                       \
    ITERATOR_TYPE(collection) it = FIND_ELEMENT((collection), (element)); \
    Consts::Index index = INDEX((collection), it);                        \
    if (index == (collection).size()) {                                   \
      (collection).push_back(element);                                    \
    }                                                                     \
  }

namespace alpha::vm::arch::mem::consts {

void Consts::insert_number(double number) {
  INSERT_TO_SET_COLLECTION(number, this->num_collection);
}

void Consts::insert_string(const std::string& string) {
  INSERT_TO_SET_COLLECTION(string, this->str_collection);
}

void Consts::insert_lib_func_name(const std::string& lib_func_name) {
  INSERT_TO_SET_COLLECTION(lib_func_name, this->lib_func_name_collection);
}

void Consts::insert_user_func(const UserFunc& user_func) {
  INSERT_TO_SET_COLLECTION(user_func, this->user_func_collection);
}

double Consts::number_at(const Index& index) {
  return this->num_collection.at(index);
}

const std::string& Consts::string_at(const Index& index) {
  return this->str_collection.at(index);
}

const std::string& Consts::lib_func_name_at(const Index& index) {
  return this->lib_func_name_collection.at(index);
}

const UserFunc& Consts::user_func_at(const Index& index) {
  return this->user_func_collection.at(index);
}

}  // namespace alpha::vm::arch::mem::consts
