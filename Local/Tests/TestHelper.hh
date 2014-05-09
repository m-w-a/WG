#ifndef WG_LOCAL_TESTS_TESTHELPER_HH_
#define WG_LOCAL_TESTS_TESTHELPER_HH_

#include <cstddef>
#include <utility>
#include <boost/type_traits/remove_all_extents.hpp>
#include <boost/range/algorithm/equal.hpp>
#include <boost/utility/addressof.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/typeof/typeof.hpp>

//###########
//Public APIs
//###########

//----------------
//LocalType Macros
//----------------

// Declares a local type with name "name".
#define WG_TESTHELPER_LOCALTYPE_DECLARE(name) \
  WG_TESTHELPER_LOCALTYPE_DECLARE_IMPL(name)

// obj:
//   An object or a reference to an object of some type that was declared using
//   the WG_TESTHELPER_LOCALTYPE_DECLARE macro.
#define WG_TESTHELPER_ASSERT_LOCALTYPE_ISCONST(obj) \
  WG_TESTHELPER_ASSERT_LOCALTYPE_ISCONST_IMPL(obj)

// See WG_TESTHELPER_ASSERT_LOCALTYPE_ISCONST.
#define WG_TESTHELPER_ASSERT_LOCALTYPE_ISCONST_TPL(obj) \
  WG_TESTHELPER_ASSERT_LOCALTYPE_ISCONST_TPL_IMPL(obj)

// See WG_TESTHELPER_ASSERT_LOCALTYPE_ISCONST.
#define WG_TESTHELPER_ASSERT_LOCALTYPE_ISNOTCONST(obj) \
  WG_TESTHELPER_ASSERT_LOCALTYPE_ISNOTCONST_IMPL(obj)

// See WG_TESTHELPER_ASSERT_LOCALTYPE_ISCONST.
#define WG_TESTHELPER_ASSERT_LOCALTYPE_ISNOTCONST_TPL(obj) \
  WG_TESTHELPER_ASSERT_LOCALTYPE_ISNOTCONST_TPL_IMPL(obj)

// Tests whether lvalue1 references lvalue2.
#define WG_TESTHELPER_ASSERT_LOCALTYPE_ISREFERENCE(lvalue1, lvalue2) \
  WG_TESTHELPER_ASSERT_ISREFERENCE(lvalue1, lvalue2)

// Tests whether lvalue1 references lvalue2.
#define WG_TESTHELPER_ASSERT_LOCALTYPE_ISNOTREFERENCE(lvalue1, lvalue2) \
  WG_TESTHELPER_ASSERT_ISNOTREFERENCE(lvalue1, lvalue2)

#define WG_TESTHELPER_ASSERT_LOCALTYPE_ISSAMETYPE_MODULOCONSTANDREF( \
  expectedtype, objtotest) \
    WG_TESTHELPER_ASSERT_LOCALTYPE_ISSAMETYPE_MODULOCONSTANDREF_IMPL( \
      expectedtype, objtotest)

//-------------------
//NonLocalType Macros
//-------------------

// Local types can't be used in template parameters in C++03, therefore lvalue1
// is deemed to be a reference if its address compares equal to lvalue2.
#define WG_TESTHELPER_ASSERT_ISREFERENCE(lvalue1, lvalue2) \
  EXPECT_TRUE( &(lvalue1) == &(lvalue2) )

// See WG_TESTHELPER_ASSERT_ISREFERENCE for rationale.
#define WG_TESTHELPER_ASSERT_ISNOTREFERENCE(lvalue1, lvalue2) \
  EXPECT_TRUE( &(lvalue1) != &(lvalue2) )

// identifier:
//   The type of identifier must not be a local one.
#define WG_TESTHELPER_ASSERT_ISCONST(identifier) \
  WG_TESTHELPER_ASSERT_CONST(identifier, 0, 0)

// See WG_TESTHELPER_ASSERT_ISCONST.
#define WG_TESTHELPER_ASSERT_ISCONST_TPL(identifier) \
  WG_TESTHELPER_ASSERT_CONST(identifier, 0, 1)

// identifier:
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

template <typename T, typename U, std::size_t N>
bool equal(T (&arr1)[N], U (&arr2)[N]);

}
}
}

//######
//Impls.
//######

#define WG_TESTHELPER_ASSERT_CONST(identifier, isnotflag, istpl) \
  EXPECT_TRUE(( \
    BOOST_PP_EXPR_IIF(isnotflag, ! ) \
    ::boost::is_const \
    < \
      BOOST_PP_EXPR_IIF(istpl, typename) ::boost::remove_pointer \
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

#define WG_TESTHELPER_ASSERT_LOCALTYPE_ISCONST_IMPL(obj) \
  WG_TESTHELPER_ASSERT_ISCONST( (obj).var )

#define WG_TESTHELPER_ASSERT_LOCALTYPE_ISCONST_TPL_IMPL(obj) \
  WG_TESTHELPER_ASSERT_ISCONST_TPL( (obj).var )

#define WG_TESTHELPER_ASSERT_LOCALTYPE_ISNOTCONST_IMPL(obj) \
  WG_TESTHELPER_ASSERT_ISNOTCONST( (obj).var )

#define WG_TESTHELPER_ASSERT_LOCALTYPE_ISNOTCONST_TPL_IMPL(obj) \
  WG_TESTHELPER_ASSERT_ISNOTCONST_TPL( (obj).var )

#define WG_TESTHELPER_ASSERT_LOCALTYPE_ISSAMETYPE_MODULOCONSTANDREF_IMPL( \
  expectedtype, objtotest) \
    { \
      expectedtype const * check = &(objtotest); \
      (void)check; \
    }

#define WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_IMPL( \
  expectedtype, objtotest, istpl) \
    EXPECT_TRUE(( \
      ::boost::is_same \
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

namespace detail
{

//-----------------
//flat_array_view_t
//-----------------

template <typename T>
struct flat_array_view_t
{
private:
  template <typename U>
  friend struct flat_array_view_t;

  enum { total_extent = 1 };

  static T * begin(T & first_elem)
  {
    return boost::addressof(first_elem);
  }
};

template <typename T, std::size_t N>
struct flat_array_view_t<T[N]>
{
  typedef typename boost::remove_all_extents<T>::type * iterator;
  typedef std::pair<iterator, iterator> result_type;
  static result_type range(T (&arr)[N])
  {
    iterator first_elem = flat_array_view_t::begin(arr);
    return flat_array_view_t::result_type(first_elem, first_elem + total_extent);
  }

private:
  template <typename U>
  friend struct flat_array_view_t;

  enum { total_extent = N * flat_array_view_t<T>::total_extent };

  static iterator begin(T (&arr)[N])
  {
    return flat_array_view_t<T>::begin(*arr);
  }
};

}

template <typename T, std::size_t N>
std::pair
<
  typename boost::remove_all_extents<T>::type *,
  typename boost::remove_all_extents<T>::type *
>
  flat_array_view(T (&arr)[N])
{
  return detail::flat_array_view_t<T[N]>::range(arr);
}

template <typename T, typename U, std::size_t N>
bool equal(T (&arr1)[N], U (&arr2)[N])
{
  return boost::equal(flat_array_view(arr1), flat_array_view(arr2));
}

}
}
}

#endif /* WG_LOCAL_TESTS_TESTHELPER_HH_ */
