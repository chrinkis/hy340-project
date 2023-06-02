#include <alpha/tcode/abc/consts/consts.h>

#include <algorithm>

#define ITERATOR(collection) decltype(collection)::iterator

#define INDEX(iterator, collection, element)                         \
  (((iterator) = std::find((collection).begin(), (collection).end(), \
                           (element))) != (collection).end()         \
       ? std::distance((collection).begin(), (iterator))             \
       : (collection).size());

#define RETURN_INDEX_OF(collection, element)                  \
  {                                                           \
    ITERATOR(collection) it;                                  \
    Consts::Index index = INDEX(it, (collection), (element)); \
                                                              \
    if (index == (collection).size()) {                       \
      (collection).push_back(element);                        \
    }                                                         \
                                                              \
    return index;                                             \
  }

namespace alpha::tcode::abc::consts {

Consts::Index Consts::number(double number) {
  RETURN_INDEX_OF(this->num_collection, number);
}

Consts::Index Consts::string(const std::string& string) {
  RETURN_INDEX_OF(this->str_collection, string);
}

Consts::Index Consts::lib_func_name(const std::string& lib_func_name) {
  RETURN_INDEX_OF(this->lib_func_name_collection, lib_func_name);
}

Consts::Index Consts::user_func(const UserFunc& user_func) {
  RETURN_INDEX_OF(this->user_func_collection, user_func);
}

const Consts::NumCollection& Consts::get_numbers() const {
  return this->num_collection;
}

const Consts::StrCollection& Consts::get_strings() const {
  return this->str_collection;
}

const Consts::LibFuncNameCollection& Consts::get_lib_func_names() const {
  return this->lib_func_name_collection;
}

const Consts::UserFuncCollection& Consts::get_user_funcs() const {
  return this->user_func_collection;
}

}  // namespace alpha::tcode::abc::consts
