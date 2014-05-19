#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>
#include <boost/typeof/typeof.hpp>
#include <WG/Local/Tests/Utils/Utils.hh>

namespace
{
template <typename T1, typename T2, typename T3, typename T4, typename T5>
struct OkIfUsing21Combo
{
  static void run()
  {
    T1 volume = -1;
    T2 const pressure = 2;
    T3 const numMoles = 3;
    T4 const R = 5;
    T5 const temp = 4;

    WG_AUTOFUNCTOR_TPL
    (calculateVolume,
      parambind ((int &) volume) ((int const) pressure)
      paramset ((int const) numerator, numMoles * R * temp) )
    {
      WG_PP_TEST_IS_SAME_TYPE(
        int &, BOOST_TYPEOF_TPL(volume) &);
      WG_PP_TEST_IS_SAME_TYPE(
        int const, BOOST_TYPEOF_TPL(pressure) const);
      WG_PP_TEST_IS_SAME_TYPE(
        int const, BOOST_TYPEOF_TPL(numerator) const);

      volume = numerator / pressure;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(volume, 30);
  }
};
}
TEST(wg_autofunctor_parambindexplicitandparamsetexplicittpl, OkIfUsing21Combo)
{
  try
  {
    OkIfUsing21Combo<int, int, int, int, int>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T1, typename T2, typename T3, typename T4, typename T5>
struct OkIfLocalTypeBound
{
  static void run()
  {
    struct Input
    {
      T1 const pressure;
      T2 const numMoles;
      T3 const R;
      T4 const temp;
    } data = {2, 3, 5, 4};

    T5 volume = -1;
    WG_AUTOFUNCTOR_TPL
    (calculateVolume,
      parambind (local(Input) data) paramset ((int &) result, volume) )
    {
      WG_PP_TEST_IS_SAME_TYPE(
        int &, BOOST_TYPEOF_TPL(result) &);

      result = (data.numMoles * data.R * data.temp) / data.pressure;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(volume, 30);
  }
};
}
TEST(wg_autofunctor_parambindexplicitandparamsetexplicittpl, OkIfLocalTypeBound)
{
  try
  {
    OkIfLocalTypeBound<int, int, int, int, int>::run();
  }
  WG_GTEST_CATCH
}
