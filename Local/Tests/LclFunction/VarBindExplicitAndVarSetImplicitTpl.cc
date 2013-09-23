#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>
#include <utility>
#include <boost/typeof/typeof.hpp>
#include <WG/Local/Tests/TestHelper.hh>

namespace
{
template <typename T1, typename T2, typename T3, typename T4, typename T5>
struct OkIfUsing21Combo
{
  static void run()
  {
    T1 volume = -1;
    T2 const pressure = 2;
    T3 const numMoles = 3;
    T4 const R = 5;
    T5 const temp = 4;

    WG_LCLFUNCTION_TPL
    (calculateVolume,
      varbind ((int &) volume) ((int const) pressure)
      varset (numerator, numMoles * R * temp) )
    {
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int &, BOOST_TYPEOF_TPL(volume) &);
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int const, BOOST_TYPEOF_TPL(pressure) const);
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int const, BOOST_TYPEOF_TPL(numerator) const);

      volume = numerator / pressure;
    }
    WG_LCLFUNCTION_END;

    calculateVolume();

    EXPECT_EQ(volume, 30);
  }
};
}
TEST(wg_lclfunction_varbindexplicitandvarsetimplicit_tpl, OkIfUsing21Combo)
{
  try
  {
    OkIfUsing21Combo<int, int, int, int, int>::run();
  }
  WG_GTEST_CATCH
}
