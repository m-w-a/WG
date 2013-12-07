#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>
#include <WG/Local/Tests/TestHelper.hh>

TEST(wg_lclfunction_varbindimplicit, OkIf1VarBound)
{
  try
  {
    bool didBind = false;

    WG_LCLFUNCTION(check, varbind (ref didBind) )
    {
      WG_TESTHELPER_ASSERT_ISNOTCONST(didBind);
      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(bool, didBind);

      didBind = true;
    }WG_LCLFUNCTION_END;

    check();

    EXPECT_TRUE(didBind);
  }
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_varbindimplicit, OkIf3VarsOfVaryingMutabilityBound)
{
  try
  {
    int force = 0;
    int const mass = 10;
    int const velocity = 2;

    WG_LCLFUNCTION
    (calculateForce, varbind (ref force) (const mass) (const velocity) )
    {
      WG_TESTHELPER_ASSERT_ISNOTCONST(force);
      WG_TESTHELPER_ASSERT_ISCONST(mass);
      WG_TESTHELPER_ASSERT_ISCONST(velocity);

      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, force);
      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, mass);
      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, velocity);

      force = mass * velocity;
    }
    WG_LCLFUNCTION_END;

    calculateForce();

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
    WG_LCLFUNCTION(bindThisU, varbind (this_) )
    {
      WG_TESTHELPER_ASSERT_ISCONST(this_);
      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
        OkIfKeywordThisUBound *, this_);

      this_->didBindThis = true;
    }
    WG_LCLFUNCTION_END;

    bindThisU();
  }
};
}
TEST(wg_lclfunction_varbindimplicit, OkIfKeywordThisUBound)
{
  try
  {
    OkIfKeywordThisUBound obj;
    EXPECT_TRUE(obj.didBindThis);
  }
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_varbindimplicit, OkIfLocalFunctionBound)
{
  bool didBind = false;

  WG_LCLFUNCTION(bindVar, varbind (ref didBind) )
  {
    WG_TESTHELPER_ASSERT_ISNOTCONST(didBind);
    WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(bool, didBind);

    didBind = true;
  }WG_LCLFUNCTION_END;

  WG_LCLFUNCTION(bindFunc, varbind (ref bindVar) )
  {
    bindVar();
  }WG_LCLFUNCTION_END;

  bindFunc();

  EXPECT_TRUE(didBind);
}
