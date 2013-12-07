#ifndef WG_LOCAL_TESTS_TESTHELPER_HH_
#define WG_LOCAL_TESTS_TESTHELPER_HH_

#include <cstddef>
#include <boost/type_traits/remove_all_extents.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/utility/addressof.hpp>

//###########
//Public APIs
//###########

//----------------
//LocalType Macros
//----------------

// Declares a type with name "name".
#define WG_TESTHELPER_LOCALTYPE_DECLARE(name) \
  WG_TESTHELPER_LOCALTYPE_DECLARE_IMPL(name)

// obj:
//   A variable identifier, not an expression!
//   An object of some type that was declared using the
//   WG_TESTHELPER_LOCALTYPE_DECLARE macro.
#define WG_TESTHELPER_LOCALTYPE_ISCONST(obj) \
  WG_TESTHELPER_LOCALTYPE_ISCONST_IMPL(obj)

// See WG_TESTHELPER_LOCALTYPE_ISCONST.
#define WG_TESTHELPER_LOCALTYPE_ISNOTCONST(obj) \
  WG_TESTHELPER_LOCALTYPE_ISNOTCONST_IMPL(obj)

#define WG_TESTHELPER_LOCALTYPE_ISREFERENCE(lvalue1, lvalue2) \
  WG_TESTHELPER_ASSERT_ISREFERENCE(lvalue1, lvalue2)

#define WG_TESTHELPER_LOCALTYPE_ISNOTREFERENCE(lvalue1, lvalue2) \
  WG_TESTHELPER_ASSERT_ISNOTREFERENCE(lvalue1, lvalue2)

#define WG_TESTHELPER_LOCALTYPE_ISSAMETYPE(expectedtype, objtotest) \
  WG_TESTHELPER_LOCALTYPE_ISSAMETYPE_IMPL(expectedtype, objtotest)

//-------------------
//NonLocalType Macros
//-------------------

#define WG_TESTHELPER_ASSERT_ISREFERENCE(lvalue1, lvalue2) \
  EXPECT_TRUE( &(lvalue1) == &(lvalue2) )

#define WG_TESTHELPER_ASSERT_ISNOTREFERENCE(lvalue1, lvalue2) \
  EXPECT_TRUE( &(lvalue1) != &(lvalue2) )

// identifier:
//   Must be a variable identifier, not an expression!.
//   The type of identifier must not be a local one.
#define WG_TESTHELPER_ASSERT_ISCONST(identifier) \
  WG_TESTHELPER_ASSERT_CONST(identifier, 0, 0)

// See WG_TESTHELPER_ASSERT_ISCONST.
#define WG_TESTHELPER_ASSERT_ISCONST_TPL(identifier) \
  WG_TESTHELPER_ASSERT_CONST(identifier, 0, 1)

// identifier:
//   Must be a variable identifier, not an expression!.
//   The type of identifier must not be a local one.
#define WG_TESTHELPER_ASSERT_ISNOTCONST(identifier) \
  WG_TESTHELPER_ASSERT_CONST(identifier, 1, 0)

// See WG_TESTHELPER_ASSERT_ISNOTCONST.
#define WG_TESTHELPER_ASSERT_ISNOTCONST_TPL(identifier) \
  WG_TESTHELPER_ASSERT_CONST(identifier, 1, 1)

#define WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF( \
  expectedtype, objtotest) \
    WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_IMPL( \
      expectedtype, objtotest, 0)

#define WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL( \
  expectedtype, objtotest) \
    WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_IMPL( \
      expectedtype, objtotest, 1)

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

#define WG_TESTHELPER_ASSERT_CONST(identifier, isnotflag, istpl) \
  EXPECT_TRUE(( \
    BOOST_PP_EXPR_IIF(isnotflag, ! ) \
    boost::is_const \
    < \
      BOOST_PP_EXPR_IIF(istpl, typename) boost::remove_pointer \
      < \
        BOOST_TYPEOF(&(identifier)) \
      >::type \
    >::value ))

#define WG_TESTHELPER_LOCALTYPE_DECLARE_IMPL(name) \
  struct name \
  { \
    /* This variable must not have const type! */ \
    int var; \
  };

#define WG_TESTHELPER_LOCALTYPE_ISCONST_IMPL(obj) \
  WG_TESTHELPER_ASSERT_ISCONST(obj.var)

#define WG_TESTHELPER_LOCALTYPE_ISNOTCONST_IMPL(obj) \
  WG_TESTHELPER_ASSERT_ISNOTCONST(obj.var)

#define WG_TESTHELPER_LOCALTYPE_ISSAMETYPE_IMPL(expectedtype, objtotest) \
  { \
    expectedtype const * check = &objtotest; \
  }

#define WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_IMPL( \
  expectedtype, objtotest, istpl) \
    EXPECT_TRUE(( \
      boost::is_same \
      < \
        expectedtype, \
        BOOST_PP_IIF(istpl, BOOST_TYPEOF_TPL, BOOST_TYPEOF) (objtotest) \
      >::value));

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

#endif /* WG_LOCAL_TESTS_TESTHELPER_HH_ */
