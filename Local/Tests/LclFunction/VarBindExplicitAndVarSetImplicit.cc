#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>
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

    WG_LCLFUNCTION
    (calculateVolume,
      varbind (type(int &) volume) (type(int const) pressure)
      varset (numerator, numMoles * R * temp) )
    {
      WG_TEST_ASSERT_ISNOTCONST(volume);
      WG_TEST_ASSERT_ISCONST(pressure);
      WG_TEST_ASSERT_ISNOTCONST(numerator);

      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, volume);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, pressure);

      volume = numerator / pressure;
    }
    WG_LCLFUNCTION_END;

    calculateVolume();

    EXPECT_EQ(volume, 30);
  }
  WG_GTEST_CATCH
}
