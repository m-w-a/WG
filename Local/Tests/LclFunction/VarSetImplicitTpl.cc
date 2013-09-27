#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>

namespace
{
template <typename T>
struct OkIf1VarSet
{
  static void run()
  {
    struct
    {
      T didAssign;
    } proxy = {false};

    WG_LCLFUNCTION_TPL(check, varset (ref didAssign, proxy.didAssign) )
    {
      didAssign = true;
    }WG_LCLFUNCTION_END;

    check();

    EXPECT_TRUE(proxy.didAssign);
  }
};
}
TEST(wg_lclfunction_varsetimplicit_tpl, OkIf1VarSet)
{
  try
  {
    OkIf1VarSet<bool>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T1, typename T2, typename T3>
struct OkIf3VarOfVaryingMutabilitySet
{
  static void run()
  {
    struct
    {
      T1 radius;
      T2 height;
      T3 volume;
    } cylinder = {2, 10, -1};

    WG_LCLFUNCTION_TPL
    (calculateVolume,
      varset (const radius, cylinder.radius)
        (const height, cylinder.height)
        (ref volume, cylinder.volume) )
    {
      volume = radius * height;
    }
    WG_LCLFUNCTION_END;

    calculateVolume();

    EXPECT_EQ(cylinder.radius * cylinder.height, cylinder.volume);
  }
};
}
TEST(wg_lclfunction_varsetimplicit_tpl, OkIf3VarOfVaryingMutabilitySet)
{
  try
  {
    OkIf3VarOfVaryingMutabilitySet<int, int, int>::run();
  }
  WG_GTEST_CATCH
}
