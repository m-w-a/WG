#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/Tests/LclFunction/Utils/TestLclFunction.hh>
#include <WG/Local/Tests/Utils/Utils.hh>

TEST(wg_lclfunction_varbindimplicit, OkIf1VarBound)
{
  try
  {
    bool didBind = false;

    WG_TEST_LCLFUNCTION(check, varbind (ref didBind) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(check);

      WG_TEST_ASSERT_ISNOTCONST(didBind);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(bool, didBind);

      didBind = true;
    }WG_TEST_LCLFUNCTION_END;

    check();
    WG_TEST_LCLFUNCTION_VERIFYCALL(check);

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

    WG_TEST_LCLFUNCTION
    (calculateForce, varbind (ref force) (const mass) (const velocity) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(calculateForce);

      WG_TEST_ASSERT_ISNOTCONST(force);
      WG_TEST_ASSERT_ISCONST(mass);
      WG_TEST_ASSERT_ISCONST(velocity);

      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, force);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, mass);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, velocity);

      force = mass * velocity;
    }
    WG_TEST_LCLFUNCTION_END;

    calculateForce();
    WG_TEST_LCLFUNCTION_VERIFYCALL(calculateForce);

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
    WG_TEST_LCLFUNCTION(bindThisU, varbind (this_) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(bindThisU);

      WG_TEST_ASSERT_ISCONST(this_);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
        OkIfKeywordThisUBound *, this_);

      this_->didBindThis = true;
    }
    WG_TEST_LCLFUNCTION_END;

    bindThisU();
    WG_TEST_LCLFUNCTION_VERIFYCALL(bindThisU);
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

  WG_TEST_LCLFUNCTION(bindVar, varbind (ref didBind) )
  {
    WG_TEST_LCLFUNCTION_MARKCALL(bindVar);

    WG_TEST_ASSERT_ISNOTCONST(didBind);
    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(bool, didBind);

    didBind = true;
  }WG_TEST_LCLFUNCTION_END;

  WG_TEST_LCLFUNCTION(bindFunc, varbind (ref bindVar) )
  {
    WG_TEST_LCLFUNCTION_MARKCALL(bindFunc);

    bindVar();
  }WG_TEST_LCLFUNCTION_END;

  bindFunc();
  WG_TEST_LCLFUNCTION_VERIFYCALL(bindVar);
  WG_TEST_LCLFUNCTION_VERIFYCALL(bindFunc);

  EXPECT_TRUE(didBind);
}
