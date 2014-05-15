#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/Tests/LclFunction/Utils/TestLclFunction.hh>
#include <boost/tuple/tuple.hpp>
#include <WG/Local/Tests/Utils/Utils.hh>

TEST(wg_lclfunction_varsetexplicit, EnsureTypeOfNotUsed)
{
  try
  {
    float val = 1.2f;

    WG_TEST_LCLFUNCTION(setToDiffType, varset (type(int) value, val) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(setToDiffType);

      WG_TEST_ASSERT_ISNOTCONST(value);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, value);

      EXPECT_EQ(1, value);
    }WG_TEST_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
      WG_LCLFUNCTION_TYPENAME(setToDiffType),
      setToDiffType);

    setToDiffType();
    WG_TEST_LCLFUNCTION_VERIFYCALL(setToDiffType);
  }
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_varsetexplicit, OkIf1VarSet)
{
  try
  {
    struct
    {
      bool didAssign;
    } proxy = {false};

    WG_TEST_LCLFUNCTION
    (check,
      varset (type(bool &) didAssign, proxy.didAssign) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(check);

      WG_TEST_ASSERT_ISNOTCONST(didAssign);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(bool, didAssign);

      didAssign = true;
    }WG_TEST_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
      WG_LCLFUNCTION_TYPENAME(check),
      check);

    check();
    WG_TEST_LCLFUNCTION_VERIFYCALL(check);

    EXPECT_TRUE(proxy.didAssign);
  }
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_varsetexplicit, OkIfGloballyScoped1VarSet)
{
  try
  {
    ::boost::tuple<bool> didAssign = ::boost::make_tuple(false);

    WG_TEST_LCLFUNCTION
    (check,
      varset (type(::boost::tuple<bool> &) assigner, didAssign) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(check);

      WG_TEST_ASSERT_ISNOTCONST(assigner);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
        ::boost::tuple<bool>, assigner);

      assigner.get<0>() = true;
    }WG_TEST_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
      WG_LCLFUNCTION_TYPENAME(check),
      check);

    check();
    WG_TEST_LCLFUNCTION_VERIFYCALL(check);

    EXPECT_TRUE(didAssign.get<0>());
  }
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_varsetexplicit, OkIf3VarOfVaryingMutabilitySet)
{
  try
  {
    struct
    {
      int radius;
      int height;
      int volume;
    } cylinder = {2, 10, -1};

    WG_TEST_LCLFUNCTION
    (calculateVolume,
      varset (type(int const) radius, cylinder.radius)
        (type(int const) height, cylinder.height)
        (type(int &) volume, cylinder.volume) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(calculateVolume);

      WG_TEST_ASSERT_ISCONST(radius);
      WG_TEST_ASSERT_ISCONST(height);
      WG_TEST_ASSERT_ISNOTCONST(volume);

      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, radius);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, height);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, volume);

      volume = radius * height;
    }
    WG_TEST_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
      WG_LCLFUNCTION_TYPENAME(calculateVolume),
      calculateVolume);

    calculateVolume();
    WG_TEST_LCLFUNCTION_VERIFYCALL(calculateVolume);

    EXPECT_EQ(cylinder.radius * cylinder.height, cylinder.volume);
  }
  WG_GTEST_CATCH
}
