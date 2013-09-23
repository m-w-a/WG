#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>
#include <utility>
#include <boost/typeof/typeof.hpp>
#include <WG/Local/Tests/TestHelper.hh>

namespace
{
template <typename T>
struct EnsureTypeOfNotUsed
{
  static void run()
  {
    float value = 1.2f;

    WG_LCLFUNCTION_TPL(bindByDiffType, varbind ((T const) value) )
    {
//      WG_PP_TESTHELPER_IS_SAME_TYPE(
//        T const, BOOST_TYPEOF_TPL(value) const);
        EXPECT_EQ(1, value);
    }WG_LCLFUNCTION_END;

    bindByDiffType();
  }
};
}
TEST(wg_lclfunction_varbindexplicit_tpl, EnsureTypeOfNotUsed)
{
  try
  {
    EnsureTypeOfNotUsed<int>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T>
struct OkIf1VarBound
{
  static void run()
  {
    T didBind = false;

    WG_LCLFUNCTION_TPL(check, varbind ((bool &) didBind) )
    {
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        bool &, BOOST_TYPEOF_TPL(didBind) &);

      didBind = true;
    }WG_LCLFUNCTION_END;

    check();

    EXPECT_TRUE(didBind);
  }
};
}
TEST(wg_lclfunction_varbindexplicit_tpl, OkIf1VarBound)
{
  try
  {
    OkIf1VarBound<bool>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T1, typename T2>
struct OkIfPPEscaped1VarBound
{
  static void run()
  {
    std::pair<T1, T2> didBind = std::make_pair(false, 0);

    WG_LCLFUNCTION_TPL
    (check,
      varbind (ppescape((std::pair<T1, T2> &)) didBind) )
    {
      didBind.first = true;
    }WG_LCLFUNCTION_END;

    check();

    EXPECT_TRUE(didBind.first);
  }
};
}
TEST(wg_lclfunction_varbindexplicit_tpl, OkIfPPEscaped1VarBound)
{
  try
  {
    OkIfPPEscaped1VarBound<bool, int>::run();
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
      varbind ((T1 &) force) ((T2 const) mass) ((T3 const) velocity) )
    {
      force = mass * velocity;
    }
    WG_LCLFUNCTION_END;

    calculateForce();

    EXPECT_EQ(force, 20);
  }
};
}
TEST(wg_lclfunction_varbindexplicit_tpl, OkIf3VarsOfVaryingMutabilityBound)
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
TEST(wg_lclfunction_varbindexplicit_tpl, OkIfKeywordThisUBound)
{
  try
  {
    OkIfKeywordThisUBound<bool> obj;
    obj.run();
  }
  WG_GTEST_CATCH
}
