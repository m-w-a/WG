#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>

TEST(wg_autofunctor_paramsetimplicit, OkIf1ArgSet)
{
  try
  {
    struct
    {
      bool didAssign;
    } proxy = {false};

    WG_AUTOFUNCTOR
    (oneArgAutoFunctor,
      paramset (ref didAssign, proxy.didAssign) )
    {
      didAssign = true;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_TRUE(proxy.didAssign);
  }
  WG_GTEST_CATCH
}

TEST(wg_autofunctor_paramsetimplicit, OkIf3ArgsOfVaryingMutabilitySet)
{
  try
  {
    struct
    {
      int radius;
      int height;
      int volume;
    } cylinder = {2, 10, -1};

    WG_AUTOFUNCTOR
    (calculateVolume,
      paramset (const radius, cylinder.radius)
        (const height, cylinder.height)
        (ref volume, cylinder.volume) )
    {
      volume = radius * height;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(cylinder.radius * cylinder.height, cylinder.volume);
  }
  WG_GTEST_CATCH
}
