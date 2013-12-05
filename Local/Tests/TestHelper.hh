#ifndef WG_LOCAL_TESTS_TESTHELPER_HH_
#define WG_LOCAL_TESTS_TESTHELPER_HH_

#include <boost/type_traits/remove_all_extents.hpp>
#include <boost/utility.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>

//###########
//Public APIs
//###########

// Needed in order to compare local types.
// Will produce a compiler error if false.
// expected:
// actual:
//   Some token that expands to a type.
#define WG_PP_TESTHELPER_IS_SAME_TYPE(expected, actual) \
  WG_PP_TESTHELPER_IS_SAME_TYPE_IMPL(expected, actual)

// Will produce a compiler error if false.
// expected:
// actual:
//   Some token that expands to a variable identifier.
#define WG_PP_TESTHELPER_IS_SAME_OBJ_NAME(expected, actual) \
  WG_PP_TESTHELPER_IS_SAME_OBJ_NAME_IMPL(expected, actual) \

// Will produce a compiler error if false.
#define WG_PP_TESTHELPER_MACROEXPANDSTOID(macrotoexpand, expectedid) \
  WG_PP_TESTHELPER_IS_SAME_OBJ_NAME(expectedid, macrotoexpand)

#define WG_TESTHELPER_ASSERT_ISREFERENCE(lvalue1, lvalue2) \
  EXPECT_TRUE( &(lvalue1) == &(lvalue2) )

#define WG_TESTHELPER_ASSERT_ISNOTREFERENCE(lvalue1, lvalue2) \
  EXPECT_TRUE( &(lvalue1) != &(lvalue2) )

#define WG_PP_TESTHELPER_ASSERT_ISSAMETYPE(expected, actual) \
  EXPECT_TRUE(boost::is_same<expected, actual>::value);

// identifier:
//   Must be a variable identifier, not an expression!.
//   The type of identifier must not be a local one.
#define WG_PP_TESTHELPER_ASSERT_ISCONST(identifier) \
  WG_PP_TESTHELPER_ASSERT_CONST(identifier, 0, 0)

// See WG_PP_TESTHELPER_ASSERT_ISCONST.
#define WG_PP_TESTHELPER_ASSERT_ISCONST_TPL(identifier) \
  WG_PP_TESTHELPER_ASSERT_CONST(identifier, 0, 1)

// identifier:
//   Must be a variable identifier, not an expression!.
//   The type of identifier must not be a local one.
#define WG_PP_TESTHELPER_ASSERT_ISNOTCONST(identifier) \
  WG_PP_TESTHELPER_ASSERT_CONST(identifier, 1, 0)

// See WG_PP_TESTHELPER_ASSERT_ISNOTCONST.
#define WG_PP_TESTHELPER_ASSERT_ISNOTCONST_TPL(identifier) \
  WG_PP_TESTHELPER_ASSERT_CONST(identifier, 1, 1)

namespace wg
{
namespace local
{
namespace tests
{

template <typename T>
struct first_nonarray_elem;

template <typename T, std::size_t N>
typename boost::remove_all_extents<T>::type *
  address_of_first_nonarray_elem(T (&arr)[N])
{
  return first_nonarray_elem<T[N]>::address_of(arr);
}

}
}
}

//######
//Impls.
//######

#define WG_PP_TESTHELPER_ASSERT_CONST(identifier, isnotflag, istpl) \
  EXPECT_TRUE( \
    BOOST_PP_EXPR_IIF(isnotflag, ! ) \
    boost::is_const \
    < \
      BOOST_PP_EXPR_IIF(istpl, typename) boost::remove_pointer \
      < \
        &BOOST_TYPEOF(identifier) \
      >::type \
    >::value )

namespace wg
{
namespace local
{
namespace tests
{

template <typename T>
struct first_nonarray_elem
{
  static T * address_of(T & first_elem)
  {
    return boost::addressof(first_elem);
  }
};

template <typename T, std::size_t N>
struct first_nonarray_elem<T[N]>
{
  static typename boost::remove_all_extents<T>::type * address_of(T (&arr)[N])
  {
    return first_nonarray_elem<T>::address_of(*arr);
  }
};

}
}
}

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
