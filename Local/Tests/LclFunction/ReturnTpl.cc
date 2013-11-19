#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>
#include <boost/tuple/tuple.hpp>

namespace
{
template <typename T>
struct OkIfReturnSpecified
{
  static void run()
  {
    T retval = false;

    WG_LCLFUNCTION_TPL
    (rettest, return (typename boost::add_const<T>::type) )
    {
      return true;
    }
    WG_LCLFUNCTION_END;

    retval = rettest();

    EXPECT_TRUE(retval);
  }
};
}
TEST(wg_lclfunction_returntpl, OkIfReturnSpecified)
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
struct OkIfGloballyScopedReturn
{
  static void run()
  {
    ::boost::tuple<T1> retval = ::boost::make_tuple(false);

    WG_LCLFUNCTION_TPL
    (rettest, return (::boost::tuple<T1> const) )
    {
      return ::boost::make_tuple(true);
    }
    WG_LCLFUNCTION_END;

    retval = rettest();

    EXPECT_TRUE(retval.template get<0>());
  }
};
}
TEST(wg_lclfunction_returntpl, OkIfGloballyScopedReturn)
{
  try
  {
    OkIfGloballyScopedReturn<bool>::run();
  }
  WG_GTEST_CATCH
}

