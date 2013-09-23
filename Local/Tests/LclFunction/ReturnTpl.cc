#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>
#include <utility>

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
template <typename T1, typename T2>
struct OkIfReturnPPEscaped
{
  static void run()
  {
    std::pair<T1, T2> retval = std::make_pair(false, 0);

    WG_LCLFUNCTION_TPL
    (rettest, return (ppescape((std::pair<T1, T2>)) const) )
    {
      return std::make_pair(true, 1);
    }
    WG_LCLFUNCTION_END;

    retval = rettest();

    EXPECT_TRUE(retval.first);
  }
};
}
TEST(wg_lclfunction_returntpl, OkIfReturnPPEscaped)
{
  try
  {
    OkIfReturnPPEscaped<bool, int>::run();
  }
  WG_GTEST_CATCH
}

