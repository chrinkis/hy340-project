#include <alpha/lang/tcode/abc/consts/consts.h>

#include <algorithm>

#define ITERATOR_TYPE(collection) decltype(collection)::iterator

#define FIND_ELEMENT(collection, element) \
  (std::find((collection).begin(), (collection).end(), (element)))

#define INDEX(collection, iterator) \
  (std::distance((collection).begin(), (iterator)))

#define RETURN_INDEX_OF(element, collection)                              \
  {                                                                       \
    ITERATOR_TYPE(collection) it = FIND_ELEMENT((collection), (element)); \
    Consts::Index index = INDEX((collection), it);                        \
                                                                          \
    if (index == (collection).size()) {                                   \
      (collection).push_back(element);                                    \
    }                                                                     \
                                                                          \
    return index;                                                         \
  }

namespace alpha::tcode::abc::consts {

Consts::Index Consts::number(double number) {
  RETURN_INDEX_OF(number, this->num_collection);
}

Consts::Index Consts::string(const std::string& string) {
  RETURN_INDEX_OF(string, this->str_collection);
}

Consts::Index Consts::lib_func_name(const std::string& lib_func_name) {
  RETURN_INDEX_OF(lib_func_name, this->lib_func_name_collection);
}

Consts::Index Consts::user_func(const UserFunc& user_func) {
  RETURN_INDEX_OF(user_func, this->user_func_collection);
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
