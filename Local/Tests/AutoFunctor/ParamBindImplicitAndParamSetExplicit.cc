#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>
#include <boost/typeof/typeof.hpp>
#include <WG/Local/Tests/TestHelper.hh>

TEST(wg_autofunctor_parambindimplicitandparamsetexplicit, OkIfUsing21Combo)
{
  try
  {
    int volume = -1;
    int const pressure = 2;
    int const numMoles = 3;
    int const R = 5;
    int const temp = 4;

    WG_AUTOFUNCTOR
    (calculateVolume,
      parambind (ref volume) (const pressure)
      paramset ((int const) numerator, numMoles * R * temp) )
    {
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int &, BOOST_TYPEOF(volume) &);
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int const, BOOST_TYPEOF(pressure) const);
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int const, BOOST_TYPEOF(numerator) const);

      volume = numerator / pressure;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(volume, 30);
  }
  WG_GTEST_CATCH
}
