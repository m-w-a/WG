#include <gtest/gtest.h>
#include <WG/Local/Tests/LclFunction/Utils/TestLclFunction.hh>
#include <utility>
#include <WG/Local/Tests/Utils/Utils.hh>

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

    WG_TEST_LCLFUNCTION_TPL
    (calculateForce,
      varset (ref force, force) (type(int const) mass, mass) (velocity, velocity) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(calculateForce);

      WG_TEST_ASSERT_ISNOTCONST_TPL(force);
      WG_TEST_ASSERT_ISCONST_TPL(mass);
      WG_TEST_ASSERT_ISNOTCONST_TPL(velocity);

      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T1, force);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(int, mass);
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
TEST(wg_lclfunction_varsetexplicitandimplicit_tpl,
  OkIf3ArgsOfVaryingMutabilityBound)
{
  OkIf3ArgsOfVaryingMutabilityBound<int, int>::run();
}
