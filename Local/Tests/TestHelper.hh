#ifndef WG_LOCAL_TESTS_TESTHELPER_HH_
#define WG_LOCAL_TESTS_TESTHELPER_HH_

//###########
//Public APIs
//###########

// Needed in order to compare local types.
// Will produce a compiler error if false.
#define WG_PP_TESTHELPER_IS_SAME_TYPE(expected, actual) \
  WG_PP_TESTHELPER_IS_SAME_TYPE_IMPL(expected, actual)

// Will produce a compiler error if false.
#define WG_PP_TESTHELPER_IS_SAME_OBJ_NAME(expected, actual) \
  WG_PP_TESTHELPER_IS_SAME_OBJ_NAME_IMPL(expected, actual) \

// Will produce a compiler error if false.
#define WG_PP_TESTHELPER_MACROEXPANDSTOID(macrotoexpand, expectedid) \
  WG_PP_TESTHELPER_IS_SAME_OBJ_NAME(expectedid, macrotoexpand)

//###########
//Impl Macros
//###########

#define WG_PP_TESTHELPER_IS_SAME_TYPE_IMPL(expected, actual) \
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

#define WG_PP_TESTHELPER_IS_SAME_OBJ_NAME_IMPL(expected, actual) \
  struct BOOST_PP_CAT(test_obj_did_bind, __LINE__) \
  { \
    int expected; \
    void operator()() \
    { \
      (void)actual; \
    } \
  };

#endif /* WG_LOCAL_TESTS_TESTHELPER_HH_ */
