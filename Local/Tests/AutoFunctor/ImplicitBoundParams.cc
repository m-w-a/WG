#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>

TEST(wg_autofunctor_boundparams_implicit, OkIf1ArgBound)
{
  try
  {
    bool didArgumentBind = false;

    WG_AUTOFUNCTOR(oneArgAutoFunctor,
      parambind (ref didArgumentBind) )
    {
      didArgumentBind = true;
    }WG_AUTOFUNCTOR_END;

    EXPECT_TRUE(didArgumentBind);
  }
  WG_GTEST_CATCH
}

TEST(wg_autofunctor_boundparams_implicit, OkIf3ArgsOfVaryingMutabilityBound)
{
  try
  {
    int force = 0;
    int const mass = 10;
    int const velocity = 2;

    WG_AUTOFUNCTOR(calculateForce,
      parambind (ref force) (mass) (velocity) )
    {
      force = mass * velocity;
    }WG_AUTOFUNCTOR_END;

    EXPECT_EQ(force, 20);
  }
  WG_GTEST_CATCH
}

namespace
{
struct SomeNonLocalClass
{
  bool didBindThis;

  SomeNonLocalClass()
  : didBindThis(false)
  {
    WG_AUTOFUNCTOR(bindThisU, parambind (this_) )
    {
      this_->didBindThis = true;
    }WG_AUTOFUNCTOR_END;
  }
};
}

TEST(wg_autofunctor_boundparams_implicit, OkIfKeywordThisUBound)
{
  try
  {
    SomeNonLocalClass someObj;
    EXPECT_TRUE(someObj.didBindThis);
  }
  WG_GTEST_CATCH
}
