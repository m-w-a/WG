#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>
#include <boost/typeof/typeof.hpp>
#include <WG/Local/Tests/TestHelper.hh>

namespace
{
template <typename T>
struct OkIf1VarBound
{
  static void run()
  {
    T didBind = false;

    WG_LCLFUNCTION_TPL(check, varbind (ref didBind) )
    {
      didBind = true;
    }WG_LCLFUNCTION_END;

    check();

    EXPECT_TRUE(didBind);
  }
};
}
TEST(wg_lclfunction_varbindimplicit_tpl, OkIf1VarBound)
{
  try
  {
    OkIf1VarBound<bool>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T1, typename T2, typename T3>
struct OkIf3VarsOfVaryingMutabilityBound
{
  static void run()
  {
    T1 force = 0;
    T2 const mass = 10;
    T3 const velocity = 2;

    WG_LCLFUNCTION_TPL
    (calculateForce,
      varbind (ref force) (const mass) (const velocity) )
    {
      force = mass * velocity;
    }
    WG_LCLFUNCTION_END;

    calculateForce();

    EXPECT_EQ(force, 20);
  }
};
}
TEST(wg_lclfunction_varbindimplicit_tpl, OkIf3VarsOfVaryingMutabilityBound)
{
  try
  {
    OkIf3VarsOfVaryingMutabilityBound<int, int, int>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T>
struct OkIfKeywordThisUBound
{
  T didBindThis;

  void run()
  {
    didBindThis = false;

    WG_LCLFUNCTION_TPL
    (bindThisU, varbind (this_) )
    {
      this_->didBindThis = true;
    }
    WG_LCLFUNCTION_END;

    bindThisU();

    EXPECT_TRUE(didBindThis);
  }
};
}
TEST(wg_lclfunction_varbindimplicit_tpl, OkIfKeywordThisUBound)
{
  try
  {
    OkIfKeywordThisUBound<bool> obj;
    obj.run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T>
struct OkIfLocalFunctionBound
{
  static void run()
  {
    T didBind = false;

    WG_LCLFUNCTION(bindVar, varbind (ref didBind) )
    {
      didBind = true;
    }WG_LCLFUNCTION_END;

    WG_LCLFUNCTION(bindFunc, varbind (ref bindVar) )
    {
      bindVar();
    }WG_LCLFUNCTION_END;

    bindFunc();

    EXPECT_TRUE(didBind);
  }
};
}
TEST(wg_lclfunction_varbindimplicit, OkIfLocalFunctionBound)
{
  try
  {
    OkIfLocalFunctionBound<bool>::run();
  }
  WG_GTEST_CATCH
}
