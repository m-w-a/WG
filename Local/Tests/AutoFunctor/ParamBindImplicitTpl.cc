#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>
#include <boost/typeof/typeof.hpp>
#include <WG/Local/Tests/TestHelper.hh>

namespace
{
template <typename T>
struct OkIf1ArgBound
{
  static void run()
  {
    T didArgumentBind = false;

    WG_AUTOFUNCTOR_TPL(oneArgAutoFunctor, parambind (ref didArgumentBind) )
    {
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        bool &, BOOST_TYPEOF_TPL(didArgumentBind) &);

      didArgumentBind = true;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_TRUE(didArgumentBind);
  }
};
}
TEST(wg_autofunctor_parambindimplicittpl, OkIf1ArgBound)
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
    (calculateForce, parambind (ref force) (const mass) (const velocity) )
    {
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int &, BOOST_TYPEOF_TPL(force) &);
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int const, BOOST_TYPEOF_TPL(mass) const);
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int const, BOOST_TYPEOF_TPL(velocity) const);

      force = mass * velocity;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(force, 20);
  }
};
}
TEST(wg_autofunctor_parambindimplicittpl, OkIf3ArgsOfVaryingMutabilityBound)
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
    WG_AUTOFUNCTOR_TPL(bindThisU, parambind (this_) )
    {
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        OkIfKeywordThisUBound * const, BOOST_TYPEOF_TPL(this_) const);

      this_->didBindThis = true;
    }
    WG_AUTOFUNCTOR_END;
  }
};
}
TEST(wg_autofunctor_parambindimplicittpl, OkIfKeywordThisUBound)
{
  try
  {
    OkIfKeywordThisUBound<bool> someObj;
    EXPECT_TRUE(someObj.didBindThis);
  }
  WG_GTEST_CATCH
}
