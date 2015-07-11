#include <gtest/gtest.h>
#include <WG/Local/Tests/LclFunction/Utils/TestLclFunction.hh>
#include <boost/tuple/tuple.hpp>
#include <WG/Local/Tests/Utils/Utils.hh>

namespace
{
template <typename T>
struct EnsureTypeOfNotUsed
{
  static void run()
  {
    float value = 1.2f;

    WG_TEST_LCLFUNCTION_TPL(bindByDiffType, varbind (type(T const) value) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(bindByDiffType);

      WG_TEST_ASSERT_ISCONST_TPL(value);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T, value);

      EXPECT_EQ(1, value);
    }WG_TEST_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(
      WG_LCLFUNCTION_TYPENAME(bindByDiffType),
      bindByDiffType);

    bindByDiffType();
    WG_TEST_LCLFUNCTION_VERIFYCALL(bindByDiffType);
  }
};
}
TEST(wg_lclfunction_varbindexplicit_tpl, EnsureTypeOfNotUsed)
{
  EnsureTypeOfNotUsed<int>::run();
}

namespace
{
template <typename T>
struct OkIf1VarBound
{
  static void run()
  {
    T didBind = false;

    WG_TEST_LCLFUNCTION_TPL(check, varbind (type(bool &) didBind) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(check);

      WG_TEST_ASSERT_ISNOTCONST_TPL(didBind);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(bool, didBind);

      didBind = true;
    }WG_TEST_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(
      WG_LCLFUNCTION_TYPENAME(check),
      check);

    check();
    WG_TEST_LCLFUNCTION_VERIFYCALL(check);

    EXPECT_TRUE(didBind);
  }
};
}
TEST(wg_lclfunction_varbindexplicit_tpl, OkIf1VarBound)
{
  OkIf1VarBound<bool>::run();
}

namespace
{
template <typename T1>
struct OkIfGloballyScoped1VarBound
{
  static void run()
  {
    ::boost::tuple<T1> didBind = ::boost::make_tuple(false);

    WG_TEST_LCLFUNCTION_TPL
    (check,
      varbind (type(::boost::tuple<T1> &) didBind) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(check);

      WG_TEST_ASSERT_ISNOTCONST_TPL(didBind);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(
        ::boost::tuple<T1>, didBind);

      didBind.template get<0>() = true;
    }WG_TEST_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(
      WG_LCLFUNCTION_TYPENAME(check),
      check);

    check();
    WG_TEST_LCLFUNCTION_VERIFYCALL(check);

    EXPECT_TRUE(didBind.template get<0>());
  }
};
}
TEST(wg_lclfunction_varbindexplicit_tpl, OkIfGloballyScoped1VarBound)
{
  OkIfGloballyScoped1VarBound<bool>::run();
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
      varbind (type(T1 &) force) (type(T2 const) mass) (type(T3 const) velocity) )
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

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(
      WG_LCLFUNCTION_TYPENAME(calculateForce),
      calculateForce);

    calculateForce();
    WG_TEST_LCLFUNCTION_VERIFYCALL(calculateForce);

    EXPECT_EQ(force, 20);
  }
};
}
TEST(wg_lclfunction_varbindexplicit_tpl, OkIf3VarsOfVaryingMutabilityBound)
{
  OkIf3VarsOfVaryingMutabilityBound<int, int, int>::run();
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
    (bindThisU, varbind (type(OkIfKeywordThisUBound * const) this_) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(bindThisU);

      WG_TEST_ASSERT_ISCONST_TPL(this_);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(
        OkIfKeywordThisUBound *, this_);

      this_->didBindThis = true;
    }
    WG_TEST_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(
      WG_LCLFUNCTION_TYPENAME(bindThisU),
      bindThisU);

    bindThisU();
    WG_TEST_LCLFUNCTION_VERIFYCALL(bindThisU);

    EXPECT_TRUE(didBindThis);
  }
};
}
TEST(wg_lclfunction_varbindexplicit_tpl, OkIfKeywordThisUBound)
{
  OkIfKeywordThisUBound<bool> obj;
  obj.run();
}
