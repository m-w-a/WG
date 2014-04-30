#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>
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
      varset (type(int const) numerator, numMoles * R * temp) )
    {
      WG_TESTHELPER_ASSERT_ISNOTCONST(volume);
      WG_TESTHELPER_ASSERT_ISCONST(pressure);
      WG_TESTHELPER_ASSERT_ISCONST(numerator);

      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, volume);
      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, pressure);
      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, numerator);

      volume = numerator / pressure;
    }
    WG_LCLFUNCTION_END;

    calculateVolume();

    EXPECT_EQ(volume, 30);
  }
  WG_GTEST_CATCH
}
