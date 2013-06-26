#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>
#include <boost/typeof/typeof.hpp>
#include <WG/Local/Tests/TestHelper.hh>

TEST(wg_autofunctor_parambindexplicitandparamsetimplicit, OkIfUsing21Combo)
{
  try
  {
    int volume = -1;
    int const pressure = 2;
    int const numMoles = 3;
    int const R = 5;
    int const temp = 4;

    WG_AUTOFUNCTOR
    (calculateVolume,
      parambind ((int &) volume) ((int const) pressure)
      paramset (numerator, numMoles * R * temp) )
    {
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int &, BOOST_TYPEOF(volume) &);
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int const, BOOST_TYPEOF(pressure) const);
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int const, BOOST_TYPEOF(numerator) const);

      volume = numerator / pressure;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(volume, 30);
  }
  WG_GTEST_CATCH
}

TEST(wg_autofunctor_parambindexplicitandparamsetimplicit, OkIfLocalTypeBound)
{
  try
  {
    struct Input
    {
      int const pressure;
      int const numMoles;
      int const R;
      int const temp;
    } data = {2, 3, 5, 4};

    int volume = -1;
    WG_AUTOFUNCTOR
    (calculateVolume,
      parambind (local(Input) data) paramset (ref result, volume) )
    {
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int &, BOOST_TYPEOF(result) &);

      result = (data.numMoles * data.R * data.temp) / data.pressure;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(volume, 30);
  }
  WG_GTEST_CATCH
}
