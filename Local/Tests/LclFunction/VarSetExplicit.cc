#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>
#include <utility>
#include <boost/typeof/typeof.hpp>
#include <WG/Local/Tests/TestHelper.hh>

TEST(wg_lclfunction_varsetexplicit, EnsureTypeOfNotUsed)
{
  try
  {
    float val = 1.2f;

    WG_LCLFUNCTION(setToDiffType, varset ((int) value, val) )
    {
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int, BOOST_TYPEOF(value));
      EXPECT_EQ(1, value);
    }WG_LCLFUNCTION_END;

    setToDiffType();
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

    WG_LCLFUNCTION
    (check,
      varset ((bool &) didAssign, proxy.didAssign) )
    {
      WG_PP_TESTHELPER_IS_SAME_TYPE(bool &, BOOST_TYPEOF(didAssign) &);
            didAssign = true;
    }WG_LCLFUNCTION_END;

    check();

    EXPECT_TRUE(proxy.didAssign);
  }
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_varsetexplicit, OkIfPPEscaped1VarSet)
{
  try
  {
    std::pair<bool, int> didAssign = std::make_pair(false, 0);

    WG_LCLFUNCTION
    (check,
      varset (ppescape((std::pair<bool, int> &)) assigner, didAssign) )
    {
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        BOOST_IDENTITY_TYPE((std::pair<bool, int> &)),
        BOOST_TYPEOF(assigner) &);
      assigner.first = true;
    }WG_LCLFUNCTION_END;

    check();

    EXPECT_TRUE(didAssign.first);
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

    WG_LCLFUNCTION
    (calculateVolume,
      varset ((int const) radius, cylinder.radius)
        ((int const) height, cylinder.height)
        ((int &) volume, cylinder.volume) )
    {
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int const, BOOST_TYPEOF(radius) const);
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int const, BOOST_TYPEOF(height) const);
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int &, BOOST_TYPEOF(volume) &);

      volume = radius * height;
    }
    WG_LCLFUNCTION_END;

    calculateVolume();

    EXPECT_EQ(cylinder.radius * cylinder.height, cylinder.volume);
  }
  WG_GTEST_CATCH
}
