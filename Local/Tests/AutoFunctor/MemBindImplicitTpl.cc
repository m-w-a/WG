#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>

namespace
{
template <typename T>
struct OkIf1ArgBound
{
  static void run()
  {
    T didArgumentBind = false;

    WG_AUTOFUNCTOR_TPL(oneArgAutoFunctor, membind (ref didArgumentBind) )
    {
      this->didArgumentBind = true;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_TRUE(didArgumentBind);
  }
};
}
TEST(wg_autofunctor_membindimplicittpl, OkIf1ArgBound)
{
  try
  {
    OkIf1ArgBound<bool>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T1, typename T2, typename T3>
struct OkIf3ArgsOfVaryingMutabilityBound
{
  static void run()
  {
    T1 force = 0;
    T2 const mass = 10;
    T3 const velocity = 2;

    WG_AUTOFUNCTOR_TPL
    (calculateForce, membind (ref force) (const mass) (const velocity) )
    {
      this->force = this->mass * this->velocity;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(force, 20);
  }
};
}
TEST(wg_autofunctor_membindimplicittpl, OkIf3ArgsOfVaryingMutabilityBound)
{
  try
  {
    OkIf3ArgsOfVaryingMutabilityBound<int, int, int>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T>
struct OkIfKeywordThisUBound
{
  T didBindThis;

  OkIfKeywordThisUBound()
  : didBindThis(false)
  {
    WG_AUTOFUNCTOR_TPL(bindThisU, membind (this_) )
    {
      this->this_->didBindThis = true;
    }
    WG_AUTOFUNCTOR_END;
  }
};
}
TEST(wg_autofunctor_membindimplicittpl, OkIfKeywordThisUBound)
{
  try
  {
    OkIfKeywordThisUBound<bool> someObj;
    EXPECT_TRUE(someObj.didBindThis);
  }
  WG_GTEST_CATCH
}
