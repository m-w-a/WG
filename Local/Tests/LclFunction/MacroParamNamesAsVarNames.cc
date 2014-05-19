#include <gtest/gtest.h>
#include <WG/Local/Tests/LclFunction/Utils/TestLclFunction.hh>
#include <WG/Local/Tests/Utils/Utils.hh>

TEST(wg_lclfunction_macroparamnamesasvarnames, VarBindImplicit)
{
  bool type = false;

  WG_TEST_LCLFUNCTION(check, varbind (ref type) )
  {
    WG_TEST_LCLFUNCTION_MARKCALL(check);

    WG_TEST_ASSERT_ISNOTCONST(type);
    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(bool, type);

    type = true;
  }WG_TEST_LCLFUNCTION_END;

  WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
    WG_LCLFUNCTION_TYPENAME(check),
    check);

  check();
  WG_TEST_LCLFUNCTION_VERIFYCALL(check);

  EXPECT_TRUE(type);
}

TEST(wg_lclfunction_macroparamnamesasvarnames, VarBindExplicit)
{
  bool type = false;

  WG_TEST_LCLFUNCTION(check, varbind (type(bool &) type) )
  {
    WG_TEST_LCLFUNCTION_MARKCALL(check);

    WG_TEST_ASSERT_ISNOTCONST(type);
    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(bool, type);

    type = true;
  }WG_TEST_LCLFUNCTION_END;

  WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
    WG_LCLFUNCTION_TYPENAME(check),
    check);

  check();
  WG_TEST_LCLFUNCTION_VERIFYCALL(check);

  EXPECT_TRUE(type);
}

TEST(wg_lclfunction_macroparamnamesasvarnames, VarSetImplicit)
{
  struct
  {
    bool didAssign;
  } proxy = {false};

  WG_TEST_LCLFUNCTION(check, varset (ref type, proxy.didAssign) )
  {
    WG_TEST_LCLFUNCTION_MARKCALL(check);

    WG_TEST_ASSERT_ISNOTCONST(type);
    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(bool, type);

    type = true;
  }WG_TEST_LCLFUNCTION_END;

  WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
    WG_LCLFUNCTION_TYPENAME(check),
    check);

  check();
  WG_TEST_LCLFUNCTION_VERIFYCALL(check);

  EXPECT_TRUE(proxy.didAssign);
}

TEST(wg_lclfunction_macroparamnamesasvarnames, VarSetExplicit)
{
  struct
  {
    bool didAssign;
  } proxy = {false};

  WG_TEST_LCLFUNCTION(check, varset (type(bool &) type, proxy.didAssign) )
  {
    WG_TEST_LCLFUNCTION_MARKCALL(check);

    WG_TEST_ASSERT_ISNOTCONST(type);
    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(bool, type);

    type = true;
  }WG_TEST_LCLFUNCTION_END;

  WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
    WG_LCLFUNCTION_TYPENAME(check),
    check);

  check();
  WG_TEST_LCLFUNCTION_VERIFYCALL(check);

  EXPECT_TRUE(proxy.didAssign);
}

