#include <gtest/gtest.h>
#include <WG/Local/Tests/LclFunction/Utils/TestLclFunction.hh>
#include <WG/Local/Tests/Utils/Utils.hh>

TEST(wg_lclfunction_varbindvariadic, OkIf1VarBound)
{
  bool didBind = false;

  WG_TEST_LCLFUNCTION(check, varbind (ref didBind) )
  {
    WG_TEST_LCLFUNCTION_MARKCALL(check);

    WG_TEST_ASSERT_ISNOTCONST(didBind);
    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(bool, didBind);

    didBind = true;
  }WG_TEST_LCLFUNCTION_END;

  WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
    WG_LCLFUNCTION_TYPENAME(check),
    check);

  check();
  WG_TEST_LCLFUNCTION_VERIFYCALL(check);

  EXPECT_TRUE(didBind);
}

TEST(wg_lclfunction_varbindvariadic, OkIf3VarsBound)
{
  int force = 0;
  int const mass = 10;
  int const velocity = 2;

  WG_TEST_LCLFUNCTION
  (calculateForce, varbind (ref force, const mass, const velocity) )
  {
    WG_TEST_LCLFUNCTION_MARKCALL(calculateForce);

    WG_TEST_ASSERT_ISNOTCONST(force);
    WG_TEST_ASSERT_ISCONST(mass);
    WG_TEST_ASSERT_ISCONST(velocity);

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, force);
    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, mass);
    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, velocity);

    force = mass * velocity;
  }
  WG_TEST_LCLFUNCTION_END;

  WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
    WG_LCLFUNCTION_TYPENAME(calculateForce),
    calculateForce);

  calculateForce();
  WG_TEST_LCLFUNCTION_VERIFYCALL(calculateForce);

  EXPECT_EQ(force, 20);
}
