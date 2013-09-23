#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>
#include <utility>
#include <boost/typeof/typeof.hpp>
#include <WG/Local/Tests/TestHelper.hh>

namespace
{
template <typename T1, typename T3>
struct OkIf3ArgsOfVaryingMutabilityBound
{
  static void run()
  {
    T1 force = 0;
    int const mass = 10;
    T3 const velocity = 2;

    WG_LCLFUNCTION_TPL
    (calculateForce,
      varset (ref force, force) ((int const) mass, mass) (velocity, velocity) )
    {
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int &, BOOST_TYPEOF_TPL(force) &);
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int const, BOOST_TYPEOF_TPL(mass) const);
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int, BOOST_TYPEOF_TPL(velocity));

      force = mass * velocity;
    }
    WG_LCLFUNCTION_END;

    calculateForce();

    EXPECT_EQ(force, 20);
  }
};
}
TEST(wg_lclfunction_varsetexplicitandimplicit_tpl,
  OkIf3ArgsOfVaryingMutabilityBound)
{
  try
  {
    OkIf3ArgsOfVaryingMutabilityBound<int, int>::run();
  }
  WG_GTEST_CATCH
}
