#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/Tests/LclFunction/Utils/TestLclFunction.hh>
#include <WG/Local/Tests/Utils/Utils.hh>

TEST(wg_lclfunction_varbindexplicitandimplicit,
  OkIf3VarsOfVaryingMutabilityBound)
{
  try
  {
    int force = 0;
    int const mass = 10;
    int const velocity = 2;

    WG_TEST_LCLFUNCTION
    (calculateForce, varbind (ref force) (type(int const) mass) (velocity) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(calculateForce);

      WG_TEST_ASSERT_ISNOTCONST(force);
      WG_TEST_ASSERT_ISCONST(mass);
      WG_TEST_ASSERT_ISNOTCONST(velocity);

      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(int, force);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(int, mass);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(int, velocity);

      force = mass * velocity;
    }
    WG_TEST_LCLFUNCTION_END;

    calculateForce();
    WG_TEST_LCLFUNCTION_VERIFYCALL(calculateForce);

    EXPECT_EQ(force, 20);
  }
  WG_GTEST_CATCH
}
