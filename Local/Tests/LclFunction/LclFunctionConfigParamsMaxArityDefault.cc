#include <gtest/gtest.h>
#include <WG/Local/LclFunction.hh>
#include <boost/config.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/is_base_of.hpp>

#ifndef BOOST_NO_CXX11_VARIADIC_TEMPLATES
  namespace detail = wg::lclfunction::detail::cpp11;
#else
  namespace detail = wg::lclfunction::detail::cpp03;
#endif

TEST(wg_lclfunction_configparamsmaxaritydefault, OkIfLessThanDefault)
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

TEST(wg_lclfunction_configparamsmaxaritydefault, OkIfEqualToDefault)
{
#ifndef BOOST_NO_CXX11_VARIADIC_TEMPLATES
  struct local_functor_type;
#endif

  typedef
    void equal_to_default_arity(
      int p1, int p2, int p3, int p4, int p5,
      int p6, int p7, int p8, int p9, int p10,
      int p11, int p12, int p13, int p14, int p15);
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

TEST(wg_lclfunction_configparamsmaxaritydefault, NotOkIfGreaterThanDefault)
{
#ifndef BOOST_NO_CXX11_VARIADIC_TEMPLATES
  struct local_functor_type;
#endif

  typedef
    void greater_than_default_arity(
      int p1, int p2, int p3, int p4, int p5,
      int p6, int p7, int p8, int p9, int p10,
      int p11, int p12, int p13, int p14, int p15,
      int p16);
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
