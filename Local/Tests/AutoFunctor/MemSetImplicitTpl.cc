#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>

namespace
{
template <typename T>
struct OkIf1ArgSet
{
  static void run()
  {
    struct
    {
      T didAssign;
    } proxy = {false};

    WG_AUTOFUNCTOR_TPL
    (oneArgAutoFunctor,
      memset (ref didAssign, proxy.didAssign) )
    {
      this->didAssign = true;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_TRUE(proxy.didAssign);
  }
};
}
TEST(wg_autofunctor_memsetimplicittpl, OkIf1ArgSet)
{
  try
  {
    OkIf1ArgSet<bool>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T1, typename T2, typename T3>
struct OkIf3ArgsOfVaryingMutabilitySet
{
  static void run()
  {
    struct
    {
      T1 radius;
      T2 height;
      T3 volume;
    } cylinder = {2, 10, -1};

    WG_AUTOFUNCTOR_TPL
    (calculateVolume,
      memset (const radius, cylinder.radius)
        (const height, cylinder.height)
        (ref volume, cylinder.volume) )
    {
      this->volume = this->radius * this->height;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(cylinder.radius * cylinder.height, cylinder.volume);
  }
};
}
TEST(wg_autofunctor_memsetimplicittpl, OkIf3ArgsOfVaryingMutabilitySet)
{
  try
  {
    OkIf3ArgsOfVaryingMutabilitySet<int, int, int>::run();
  }
  WG_GTEST_CATCH
}
