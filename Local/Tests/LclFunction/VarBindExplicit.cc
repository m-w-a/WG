#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>
#include <boost/tuple/tuple.hpp>
#include <boost/typeof/typeof.hpp>
#include <WG/Local/Tests/TestHelper.hh>

TEST(wg_lclfunction_varbindexplicit, EnsureTypeOfNotUsed)
{
  try
  {
    float value = 1.2f;

    WG_LCLFUNCTION(bindByDiffType, varbind ((int const) value) )
    {
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int const, BOOST_TYPEOF(value) const);
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

    WG_LCLFUNCTION(check, varbind ((bool &) didBind) )
    {
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        bool &, BOOST_TYPEOF(didBind) &);

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

    WG_LCLFUNCTION(check, varbind ((::boost::tuple<bool> &) didBind) )
    {
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        ::boost::tuple<bool> &,
        BOOST_TYPEOF(didBind) &);

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
      varbind ((int &) force) ((int const) mass) ((int const) velocity) )
    {
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int &, BOOST_TYPEOF(force) &);
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int const, BOOST_TYPEOF(mass) const);
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int const, BOOST_TYPEOF(velocity) const);

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
    (bindThisU, varbind ((OkIfKeywordThisUBound * const) this_) )
    {
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
