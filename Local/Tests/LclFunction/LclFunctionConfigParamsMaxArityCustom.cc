#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/is_base_of.hpp>

#define WG_PP_LCLFUNCTION_CONFIG_PARAMS_MAX_ARITY 5
#include <WG/Local/LclFunction.hh>

#ifndef BOOST_NO_CXX11_VARIADIC_TEMPLATES
  namespace detail = wg::lclfunction::detail::cpp11;
#else
  namespace detail = wg::lclfunction::detail;
#endif

TEST(wg_lclfunction_configparamsmaxaritycustom, OkIfLessThanDefault)
{
  try
  {
#ifndef BOOST_NO_CXX11_VARIADIC_TEMPLATES
    struct local_functor_type;
#endif

    typedef void (less_than_default_arity)();
    typedef
      detail::global_functor_type
      <
#ifndef BOOST_NO_CXX11_VARIADIC_TEMPLATES
        local_functor_type,
#endif
        less_than_default_arity,
        boost::tuple<>
      > global_functor_type;

    EXPECT_TRUE((
      boost::is_base_of
      <
        wg::lclfunction::detail::global_functor_base_type,
        global_functor_type
      >::value ));
  }
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_configparamsmaxaritycustom, OkIfEqualToDefault)
{
  try
  {
#ifndef BOOST_NO_CXX11_VARIADIC_TEMPLATES
    struct local_functor_type;
#endif

    typedef
      void equal_to_default_arity(int p1, int p2, int p3, int p4, int p5);
    typedef
      detail::global_functor_type
      <
#ifndef BOOST_NO_CXX11_VARIADIC_TEMPLATES
        local_functor_type,
#endif
        equal_to_default_arity,
        boost::tuple<>
      > global_functor_type;

    EXPECT_TRUE((
      boost::is_base_of
      <
        wg::lclfunction::detail::global_functor_base_type,
        global_functor_type
      >::value ));
  }
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_configparamsmaxaritycustom, NotOkIfGreaterThanDefault)
{
  try
  {
#ifndef BOOST_NO_CXX11_VARIADIC_TEMPLATES
    struct local_functor_type;
#endif

    typedef
      void greater_than_default_arity(
        int p1, int p2, int p3, int p4, int p5,
        int p6);
    typedef
      detail::global_functor_type
      <
#ifndef BOOST_NO_CXX11_VARIADIC_TEMPLATES
        local_functor_type,
#endif
        greater_than_default_arity,
        boost::tuple<>
      > global_functor_type;

    EXPECT_FALSE((
      boost::is_base_of
      <
        wg::lclfunction::detail::global_functor_base_type,
        global_functor_type
      >::value ));
  }
  WG_GTEST_CATCH
}
