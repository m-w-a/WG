#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/Tests/LclFunction/Utils/TestLclFunction.hh>
#include <WG/Local/Tests/Utils/Utils.hh>

TEST(wg_lclfunction_macroparamnamesasvarnames, VarBindImplicit)
{
  try
  {
    bool type = false;

    WG_TEST_LCLFUNCTION(check, varbind (ref type) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(check);

      WG_TEST_ASSERT_ISNOTCONST(type);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(bool, type);

      type = true;
    }WG_TEST_LCLFUNCTION_END;

    check();
    WG_TEST_LCLFUNCTION_VERIFYCALL(check);

    EXPECT_TRUE(type);
  }
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_macroparamnamesasvarnames, VarBindExplicit)
{
  try
  {
    bool type = false;

    WG_TEST_LCLFUNCTION(check, varbind (type(bool &) type) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(check);

      WG_TEST_ASSERT_ISNOTCONST(type);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(bool, type);

      type = true;
    }WG_TEST_LCLFUNCTION_END;

    check();
    WG_TEST_LCLFUNCTION_VERIFYCALL(check);

    EXPECT_TRUE(type);
  }
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_macroparamnamesasvarnames, VarSetImplicit)
{
  try
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

    check();
    WG_TEST_LCLFUNCTION_VERIFYCALL(check);

    EXPECT_TRUE(proxy.didAssign);
  }
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_macroparamnamesasvarnames, VarSetExplicit)
{
  try
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

    check();
    WG_TEST_LCLFUNCTION_VERIFYCALL(check);

    EXPECT_TRUE(proxy.didAssign);
  }
  WG_GTEST_CATCH
}

