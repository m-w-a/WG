#include <gtest/gtest.h>
#include <WG/Local/Tests/LclFunction/Utils/TestLclFunction.hh>
#include <WG/Local/Tests/Utils/Utils.hh>

TEST(wg_lclfunction_varbindimplicitandvarsetimplicit, OkIfUsing21Combo)
{
  int volume = -1;
  int const pressure = 2;
  int const numMoles = 3;
  int const R = 5;
  int const temp = 4;

  WG_TEST_LCLFUNCTION
  (calculateVolume,
    varbind (ref volume) (const pressure)
    varset (const numerator, numMoles * R * temp) )
  {
    WG_TEST_LCLFUNCTION_MARKCALL(calculateVolume);

    WG_TEST_ASSERT_ISNOTCONST(volume);
    WG_TEST_ASSERT_ISCONST(pressure);
    WG_TEST_ASSERT_ISCONST(numerator);

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, volume);
    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, pressure);

    volume = numerator / pressure;
  }
  WG_TEST_LCLFUNCTION_END;

  WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
    WG_LCLFUNCTION_TYPENAME(calculateVolume),
    calculateVolume);

  calculateVolume();
  WG_TEST_LCLFUNCTION_VERIFYCALL(calculateVolume);

  EXPECT_EQ(volume, 30);
}
