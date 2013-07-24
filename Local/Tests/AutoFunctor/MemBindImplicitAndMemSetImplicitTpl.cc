#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>

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

    WG_AUTOFUNCTOR_TPL
    (calculateVolume,
      membind (ref volume) (const pressure)
      memset (const numerator, numMoles * R * temp) )
    {
      this->volume = this->numerator / this->pressure;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(volume, 30);
  }
};
}
TEST(wg_autofunctor_membindimplicitandmemsetimplicittpl, OkIfUsing21Combo)
{
  try
  {
    OkIfUsing21Combo<int, int, int, int, int>::run();
  }
  WG_GTEST_CATCH
}
