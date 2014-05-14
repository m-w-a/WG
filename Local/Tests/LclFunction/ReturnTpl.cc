#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/Tests/LclFunction/Utils/TestLclFunction.hh>
#include <boost/tuple/tuple.hpp>
#include <WG/Local/Tests/Utils/Utils.hh>

namespace
{
template <typename T>
struct OkIfReturnSpecified
{
  static void run()
  {
    T retval = false;

    WG_TEST_LCLFUNCTION_TPL(rettest, return (typename ::boost::add_const<T>::type) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(rettest);
      return true;
    }
    WG_TEST_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T, rettest());

    retval = rettest();
    WG_TEST_LCLFUNCTION_VERIFYCALL(rettest);

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

    WG_TEST_LCLFUNCTION_TPL(rettest, return (::boost::tuple<T1> const) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(rettest);
      return ::boost::make_tuple(true);
    }
    WG_TEST_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(
      ::boost::tuple<T1>, rettest());

    retval = rettest();
    WG_TEST_LCLFUNCTION_VERIFYCALL(rettest);

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

