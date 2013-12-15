#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>
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
      varbind (ref volume) (const pressure)
      varset ((int const) numerator, numMoles * R * temp) )
    {
      WG_TESTHELPER_ASSERT_ISNOTCONST_TPL(volume);
      WG_TESTHELPER_ASSERT_ISCONST_TPL(pressure);
      WG_TESTHELPER_ASSERT_ISCONST_TPL(numerator);

      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T1, volume);
      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T2, pressure);
      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(int, numerator);

      volume = numerator / pressure;
    }
    WG_LCLFUNCTION_END;

    calculateVolume();

    EXPECT_EQ(volume, 30);
  }
};
}
TEST(wg_lclfunction_varbindimplicitandvarsetexplicit_tpl, OkIfUsing21Combo)
{
  try
  {
    OkIfUsing21Combo<int, int, int, int, int>::run();
  }
  WG_GTEST_CATCH
}
