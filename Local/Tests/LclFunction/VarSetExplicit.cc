#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>
#include <boost/tuple/tuple.hpp>
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

TEST(wg_lclfunction_varsetexplicit, OkIfGloballyScoped1VarSet)
{
  try
  {
    ::boost::tuple<bool> didAssign = ::boost::make_tuple(false);

    WG_LCLFUNCTION
    (check,
      varset ((::boost::tuple<bool> &) assigner, didAssign) )
    {
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        ::boost::tuple<bool> &,
        BOOST_TYPEOF(assigner) &);
      assigner.get<0>() = true;
    }WG_LCLFUNCTION_END;

    check();

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
