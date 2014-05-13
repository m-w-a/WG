#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/Tests/LclFunction/Utils/TestLclFunction.hh>
#include <WG/Local/Tests/Utils/Utils.hh>

TEST(wg_lclfunction_varbindexplicitandvarsetimplicit, OkIfUsing21Combo)
{
  try
  {
    int volume = -1;
    int const pressure = 2;
    int const numMoles = 3;
    int const R = 5;
    int const temp = 4;

    WG_TEST_LCLFUNCTION
    (calculateVolume,
      varbind (type(int &) volume) (type(int const) pressure)
      varset (numerator, numMoles * R * temp) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(calculateVolume);

      WG_TEST_ASSERT_ISNOTCONST(volume);
      WG_TEST_ASSERT_ISCONST(pressure);
      WG_TEST_ASSERT_ISNOTCONST(numerator);

      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, volume);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, pressure);

      volume = numerator / pressure;
    }
    WG_TEST_LCLFUNCTION_END;

    calculateVolume();
    WG_TEST_LCLFUNCTION_VERIFYCALL(calculateVolume);

    EXPECT_EQ(volume, 30);
  }
  WG_GTEST_CATCH
}
