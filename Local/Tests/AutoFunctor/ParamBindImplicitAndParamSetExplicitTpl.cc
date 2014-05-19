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
      parambind (ref volume) (const pressure)
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
TEST(wg_autofunctor_parambindimplicitandparamsetexplicittpl, OkIfUsing21Combo)
{
  try
  {
    OkIfUsing21Combo<int, int, int, int, int>::run();
  }
  WG_GTEST_CATCH
}
