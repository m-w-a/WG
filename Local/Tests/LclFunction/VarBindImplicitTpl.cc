#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/Tests/LclFunction/Utils/TestLclFunction.hh>
#include <boost/typeof/typeof.hpp>
#include <WG/Local/Tests/Utils/Utils.hh>

namespace
{
template <typename T>
struct OkIf1VarBound
{
  static void run()
  {
    T didBind = false;

    WG_TEST_LCLFUNCTION_TPL(check, varbind (ref didBind) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(check);

      WG_TEST_ASSERT_ISNOTCONST_TPL(didBind);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T, didBind);

      didBind = true;
    }WG_TEST_LCLFUNCTION_END;

    check();
    WG_TEST_LCLFUNCTION_VERIFYCALL(check);

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

    WG_TEST_LCLFUNCTION_TPL
    (calculateForce,
      varbind (ref force) (const mass) (const velocity) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(calculateForce);

      WG_TEST_ASSERT_ISNOTCONST_TPL(force);
      WG_TEST_ASSERT_ISCONST_TPL(mass);
      WG_TEST_ASSERT_ISCONST_TPL(velocity);

      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T1, force);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T2, mass);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T3, velocity);

      force = mass * velocity;
    }
    WG_TEST_LCLFUNCTION_END;

    calculateForce();
    WG_TEST_LCLFUNCTION_VERIFYCALL(calculateForce);

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

    WG_TEST_LCLFUNCTION_TPL
    (bindThisU, varbind (this_) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(bindThisU);

      WG_TEST_ASSERT_ISCONST_TPL(this_);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(
        OkIfKeywordThisUBound<T> *, this_);

      this_->didBindThis = true;
    }
    WG_TEST_LCLFUNCTION_END;

    bindThisU();
    WG_TEST_LCLFUNCTION_VERIFYCALL(bindThisU);

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

    WG_TEST_LCLFUNCTION_TPL(bindVar, varbind (ref didBind) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(bindVar);

      WG_TEST_ASSERT_ISNOTCONST_TPL(didBind);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T, didBind);

      didBind = true;
    }WG_TEST_LCLFUNCTION_END;

    WG_TEST_LCLFUNCTION_TPL(bindFunc, varbind (ref bindVar) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(bindFunc);

      bindVar();
    }WG_TEST_LCLFUNCTION_END;

    bindFunc();
    WG_TEST_LCLFUNCTION_VERIFYCALL(bindVar);
    WG_TEST_LCLFUNCTION_VERIFYCALL(bindFunc);

    EXPECT_TRUE(didBind);
  }
};
}
TEST(wg_lclfunction_varbindimplicit_tpl, OkIfLocalFunctionBound)
{
  try
  {
    OkIfLocalFunctionBound<bool>::run();
  }
  WG_GTEST_CATCH
}
