#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/add_const.hpp>

namespace
{
template <typename T>
struct OkIfReturnSpecified
{
  static void run()
  {
    T didAssign = false;

    WG_AUTOFUNCTOR_TPL
    (ret,
      assignto (didAssign)
      return (typename ::boost::add_const<T>::type) )
    {
      return true;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_TRUE(didAssign);
  }
};
}
TEST(wg_autofunctor_returntpl, OkIfReturnSpecified)
{
  try
  {
    OkIfReturnSpecified<bool>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T1>
struct OkIfReturnGloballyScoped
{
  static void run()
  {
    ::boost::tuple<T1> didAssign = ::boost::make_tuple(false);

    WG_AUTOFUNCTOR_TPL
    (ret,
      assignto (didAssign)
      return (::boost::tuple<T1> const) )
    {
      return ::boost::make_tuple(true);
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_TRUE(didAssign.template get<0>());
  }
};
}
TEST(wg_autofunctor_returntpl, OkIfReturnGloballyScoped)
{
  try
  {
    OkIfReturnGloballyScoped<bool>::run();
  }
  WG_GTEST_CATCH
}
