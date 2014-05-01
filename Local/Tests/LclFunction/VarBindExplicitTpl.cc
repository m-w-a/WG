#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>
#include <boost/tuple/tuple.hpp>
#include <WG/Local/Tests/TestHelper.hh>

namespace
{
template <typename T>
struct EnsureTypeOfNotUsed
{
  static void run()
  {
    float value = 1.2f;

    WG_LCLFUNCTION_TPL(bindByDiffType, varbind (type(T const) value) )
    {
      WG_TESTHELPER_ASSERT_ISCONST_TPL(value);
      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T, value);

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

    WG_LCLFUNCTION_TPL(check, varbind (type(bool &) didBind) )
    {
      WG_TESTHELPER_ASSERT_ISNOTCONST_TPL(didBind);
      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(bool, didBind);

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
template <typename T1>
struct OkIfGloballyScoped1VarBound
{
  static void run()
  {
    ::boost::tuple<T1> didBind = ::boost::make_tuple(false);

    WG_LCLFUNCTION_TPL
    (check,
      varbind (type(::boost::tuple<T1> &) didBind) )
    {
      WG_TESTHELPER_ASSERT_ISNOTCONST_TPL(didBind);
      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(
        ::boost::tuple<T1>, didBind);

      didBind.template get<0>() = true;
    }WG_LCLFUNCTION_END;

    check();

    EXPECT_TRUE(didBind.template get<0>());
  }
};
}
TEST(wg_lclfunction_varbindexplicit_tpl, OkIfGloballyScoped1VarBound)
{
  try
  {
    OkIfGloballyScoped1VarBound<bool>::run();
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
      varbind (type(T1 &) force) (type(T2 const) mass) (type(T3 const) velocity) )
    {
      WG_TESTHELPER_ASSERT_ISNOTCONST_TPL(force);
      WG_TESTHELPER_ASSERT_ISCONST_TPL(mass);
      WG_TESTHELPER_ASSERT_ISCONST_TPL(velocity);

      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T1, force);
      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T2, mass);
      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T3, velocity);

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
    (bindThisU, varbind (type(OkIfKeywordThisUBound * const) this_) )
    {
      WG_TESTHELPER_ASSERT_ISCONST_TPL(this_);
      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(
        OkIfKeywordThisUBound *, this_);

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
