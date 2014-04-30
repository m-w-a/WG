#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>
#include <boost/tuple/tuple.hpp>
#include <WG/Local/Tests/TestHelper.hh>

TEST(wg_lclfunction_varbindexplicit, EnsureTypeOfNotUsed)
{
  try
  {
    float value = 1.2f;

    WG_LCLFUNCTION(bindByDiffType, varbind (type(int const) value) )
    {
      WG_TESTHELPER_ASSERT_ISCONST(value);
      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, value);

      EXPECT_EQ(1, value);
    }WG_LCLFUNCTION_END;

    bindByDiffType();
  }
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_varbindexplicit, OkIf1VarBound)
{
  try
  {
    bool didBind = false;

    WG_LCLFUNCTION(check, varbind (type(bool &) didBind) )
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

TEST(wg_lclfunction_varbindexplicit, OkIfGloballyScoped1VarBound)
{
  try
  {
    ::boost::tuple<bool> didBind = ::boost::make_tuple(false);

    WG_LCLFUNCTION(check, varbind (type(::boost::tuple<bool> &) didBind) )
    {
      WG_TESTHELPER_ASSERT_ISNOTCONST(didBind);
      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
        ::boost::tuple<bool>, didBind);

      didBind.get<0>() = true;
    }WG_LCLFUNCTION_END;

    check();

    EXPECT_TRUE(didBind.get<0>());
  }
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_varbindexplicit, OkIf3VarsOfVaryingMutabilityBound)
{
  try
  {
    int force = 0;
    int const mass = 10;
    int const velocity = 2;

    WG_LCLFUNCTION
    (calculateForce,
      varbind (type(int &) force) (type(int const) mass) (type(int const) velocity) )
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

  void run()
  {
    didBindThis = false;

    WG_LCLFUNCTION
    (bindThisU, varbind (type(OkIfKeywordThisUBound * const) this_) )
    {
      WG_TESTHELPER_ASSERT_ISCONST(this_);
      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
        OkIfKeywordThisUBound *, this_);

      this_->didBindThis = true;
    }
    WG_LCLFUNCTION_END;

    bindThisU();

    EXPECT_TRUE(didBindThis);
  }
};
}
TEST(wg_lclfunction_varbindexplicit, OkIfKeywordThisUBound)
{
  try
  {
    OkIfKeywordThisUBound obj;
    obj.run();
  }
  WG_GTEST_CATCH
}
