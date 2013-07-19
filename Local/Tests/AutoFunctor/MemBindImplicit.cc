#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>

TEST(wg_autofunctor_membindimplicit, OkIf1ArgBound)
{
  try
  {
    bool didArgumentBind = false;

    WG_AUTOFUNCTOR(oneArgAutoFunctor, membind (ref didArgumentBind) )
    {
      this->didArgumentBind = true;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_TRUE(didArgumentBind);
  }
  WG_GTEST_CATCH
}

TEST(wg_autofunctor_membindimplicit, OkIf3ArgsOfVaryingMutabilityBound)
{
  try
  {
    int force = 0;
    int const mass = 10;
    int const velocity = 2;

    WG_AUTOFUNCTOR
    (calculateForce, membind (ref force) (const mass) (const velocity) )
    {
      this->force = this->mass * this->velocity;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(force, 20);
  }
  WG_GTEST_CATCH
}

namespace
{
struct OkIfKeywordThisUBound
{
  bool didBindThis;

  OkIfKeywordThisUBound()
  : didBindThis(false)
  {
    WG_AUTOFUNCTOR(bindThisU, membind (this_) )
    {
      this->this_->didBindThis = true;
    }
    WG_AUTOFUNCTOR_END;
  }
};
}
TEST(wg_autofunctor_membindimplicit, OkIfKeywordThisUBound)
{
  try
  {
    OkIfKeywordThisUBound someObj;
    EXPECT_TRUE(someObj.didBindThis);
  }
  WG_GTEST_CATCH
}
