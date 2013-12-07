#ifndef WG_PP_LOCAL_DETAIL_PP_TESTS_UTIL_HH_
#define WG_PP_LOCAL_DETAIL_PP_TESTS_UTIL_HH_

#include <boost/preprocessor/cat.hpp>

//###########
//Public APIs
//###########

// Needed in order to compare local types.
// Will produce a compiler error if false.
// expected:
// actual:
//   Some token that expands to a type.
#define WG_PP_TESTS_UTIL_ISSAMETYPE(expected, actual) \
  WG_PP_TESTS_UTIL_ISSAMETYPE_IMPL(expected, actual)

// Will produce a compiler error if false.
// expected:
// actual:
//   Some token that expands to a variable identifier.
#define WG_PP_TESTS_UTIL_ISSAMEOBJNAME(expected, actual) \
  WG_PP_TESTS_UTIL_ISSAMEOBJNAME_IMPL(expected, actual) \

// Will produce a compiler error if false.
#define WG_PP_TESTS_UTIL_MACROEXPANDSTOID(macrotoexpand, expectedid) \
  WG_PP_TESTS_UTIL_ISSAMEOBJNAME(expectedid, macrotoexpand)

//######
//Impls.
//######

#define WG_PP_TESTS_UTIL_ISSAMETYPE_IMPL(expected, actual) \
  struct BOOST_PP_CAT(test_type_did_bind, __LINE__) \
  { \
    void test() \
    { \
      typedef void (*expected_fptr_type)(expected param1); \
      typedef void (*actual_fptr_type)(actual param1); \
      expected_fptr_type expected_fptr = 0; \
      actual_fptr_type actual_fptr = 0; \
      expected_fptr = actual_fptr; \
      (void)expected_fptr; \
    } \
  };

#define WG_PP_TESTS_UTIL_ISSAMEOBJNAME_IMPL(expected, actual) \
  struct BOOST_PP_CAT(test_obj_did_bind, __LINE__) \
  { \
    int expected; \
    void operator()() \
    { \
      (void)actual; \
    } \
  };

#endif /* WG_PP_LOCAL_DETAIL_PP_TESTS_UTIL_HH_ */
