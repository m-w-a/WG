#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>
#include <boost/typeof/typeof.hpp>
#include <WG/Local/Tests/TestHelper.hh>

TEST(wg_autofunctor_parambindimplicit, OkIf1ArgBound)
{
  try
  {
    bool didArgumentBind = false;

    WG_AUTOFUNCTOR(oneArgAutoFunctor, parambind (ref didArgumentBind) )
    {
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        bool &, BOOST_TYPEOF(didArgumentBind) &);

      didArgumentBind = true;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_TRUE(didArgumentBind);
  }
  WG_GTEST_CATCH
}

TEST(wg_autofunctor_parambindimplicit, OkIf3ArgsOfVaryingMutabilityBound)
{
  try
  {
    int force = 0;
    int const mass = 10;
    int const velocity = 2;

    WG_AUTOFUNCTOR
    (calculateForce, parambind (ref force) (const mass) (const velocity) )
    {
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int &, BOOST_TYPEOF(force) &);
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int const, BOOST_TYPEOF(mass) const);
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int const, BOOST_TYPEOF(velocity) const);

      force = mass * velocity;
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
    WG_AUTOFUNCTOR(bindThisU, parambind (this_) )
    {
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        OkIfKeywordThisUBound * const, BOOST_TYPEOF(this_) const);

      this_->didBindThis = true;
    }
    WG_AUTOFUNCTOR_END;
  }
};
}
TEST(wg_autofunctor_parambindimplicit, OkIfKeywordThisUBound)
{
  try
  {
    OkIfKeywordThisUBound someObj;
    EXPECT_TRUE(someObj.didBindThis);
  }
  WG_GTEST_CATCH
}
