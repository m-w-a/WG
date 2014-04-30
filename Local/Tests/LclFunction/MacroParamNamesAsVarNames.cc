#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>
#include <WG/Local/Tests/TestHelper.hh>

TEST(wg_lclfunction_macroparamnamesasvarnames, VarBindImplicit)
{
  try
  {
    bool type = false;

    WG_LCLFUNCTION(check, varbind (ref type) )
    {
      WG_TESTHELPER_ASSERT_ISNOTCONST(type);
      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(bool, type);

      type = true;
    }WG_LCLFUNCTION_END;

    check();

    EXPECT_TRUE(type);
  }
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_macroparamnamesasvarnames, VarBindExplicit)
{
  try
  {
    bool type = false;

    WG_LCLFUNCTION(check, varbind (type(bool &) type) )
    {
      WG_TESTHELPER_ASSERT_ISNOTCONST(type);
      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(bool, type);

      type = true;
    }WG_LCLFUNCTION_END;

    check();

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

    WG_LCLFUNCTION(check, varset (ref type, proxy.didAssign) )
    {
      WG_TESTHELPER_ASSERT_ISNOTCONST_TPL(type);
      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(bool, type);

      type = true;
    }WG_LCLFUNCTION_END;

    check();

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

    WG_LCLFUNCTION(check, varset (type(bool &) type, proxy.didAssign) )
    {
      WG_TESTHELPER_ASSERT_ISNOTCONST_TPL(type);
      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(bool, type);

      type = true;
    }WG_LCLFUNCTION_END;

    check();

    EXPECT_TRUE(proxy.didAssign);
  }
  WG_GTEST_CATCH
}

