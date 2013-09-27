#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>
#include <utility>
#include <boost/typeof/typeof.hpp>
#include <WG/Local/Tests/TestHelper.hh>

TEST(wg_lclfunction_varbindimplicitandvarsetexplicit, OkIfUsing21Combo)
{
  try
  {
    int volume = -1;
    int const pressure = 2;
    int const numMoles = 3;
    int const R = 5;
    int const temp = 4;

    WG_LCLFUNCTION
    (calculateVolume,
      varbind (ref volume) (const pressure)
      varset ((int const) numerator, numMoles * R * temp) )
    {
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int &, BOOST_TYPEOF(volume) &);
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int const, BOOST_TYPEOF(pressure) const);
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int const, BOOST_TYPEOF(numerator) const);

      volume = numerator / pressure;
    }
    WG_LCLFUNCTION_END;

    calculateVolume();

    EXPECT_EQ(volume, 30);
  }
  WG_GTEST_CATCH
}
