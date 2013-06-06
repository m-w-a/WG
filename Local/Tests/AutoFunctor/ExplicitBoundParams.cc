#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>

TEST(wg_autofunctor_explicitboundparams, OkIf1ArgBound)
{
  try
  {
    bool didArgumentBind = false;

    WG_AUTOFUNCTOR(oneArgAutoFunctor,
      parambind ((bool &)didArgumentBind) )
    {
      didArgumentBind = true;
    }WG_AUTOFUNCTOR_END;

    EXPECT_TRUE(didArgumentBind);
  }
  WG_GTEST_CATCH
}

TEST(wg_autofunctor_explicitboundparams, OkIf3ArgsOfVaryingMutabilityBound)
{
  try
  {
    int force = 0;
    int const mass = 10;
    int const velocity = 2;

    WG_AUTOFUNCTOR(calculateForce,
      parambind ((int &) force) ((int const) mass) ((int const) velocity) )
    {
      force = mass * velocity;
    }WG_AUTOFUNCTOR_END;

    EXPECT_EQ(force, 20);
  }
  WG_GTEST_CATCH
}

TEST(wg_autofunctor_explicitboundparams, OkIfKeywordThisUBound)
{
  try
  {
    struct SomeLocalClass
    {
      bool didBindThis;

      SomeLocalClass()
      : didBindThis(false)
      {
        WG_AUTOFUNCTOR(bindThisU,
          parambind (local(SomeLocalClass * const) this_) )
        {
          this_->didBindThis = true;
        }WG_AUTOFUNCTOR_END;
      }
    } someLocalObj;

    EXPECT_TRUE(someLocalObj.didBindThis);
  }
  WG_GTEST_CATCH
}
