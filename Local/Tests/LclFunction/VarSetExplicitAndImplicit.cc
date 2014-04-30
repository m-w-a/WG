#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>
#include <WG/Local/Tests/TestHelper.hh>

TEST(wg_lclfunction_varsetexplicitandimplicit,
  OkIf3ArgsOfVaryingMutabilityBound)
{
  try
  {
    int force = 0;
    int const mass = 10;
    int const velocity = 2;

    WG_LCLFUNCTION
    (calculateForce,
      varset (ref force, force) (type(int const) mass, mass) (velocity, velocity) )
    {
      WG_TESTHELPER_ASSERT_ISNOTCONST(force);
      WG_TESTHELPER_ASSERT_ISCONST(mass);
      WG_TESTHELPER_ASSERT_ISNOTCONST(velocity);

      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, force);
      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, mass);
      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, velocity);

      force = mass * velocity;
    }
    WG_LCLFUNCTION_END;

    calculateForce();

    EXPECT_EQ(force, 20);
  }
  WG_GTEST_CATCH
}
