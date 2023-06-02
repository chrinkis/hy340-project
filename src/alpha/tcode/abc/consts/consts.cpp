#include <alpha/tcode/abc/consts/consts.h>

#include <utils/warnings.h>
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
  WARN_EMPTY_FUNC_IMPL(0);
}

Consts::Index Consts::string(const std::string& string) {
  WARN_EMPTY_FUNC_IMPL(0);
}

Consts::Index Consts::lib_func_name(const std::string& lib_func_name) {
  WARN_EMPTY_FUNC_IMPL(0);
}

Consts::Index Consts::user_func(const UserFunc& user_func) {
  WARN_EMPTY_FUNC_IMPL(0);
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
