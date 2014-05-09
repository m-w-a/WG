#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>
#include <WG/Local/Tests/Utils/Utils.hh>

namespace
{
template <typename T>
struct VarBindImplicit
{
  static void run()
  {
    T type = false;

    WG_LCLFUNCTION_TPL(check, varbind (ref type) )
    {
      WG_TEST_ASSERT_ISNOTCONST_TPL(type);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T, type);

      type = true;
    }WG_LCLFUNCTION_END;

    check();

    EXPECT_TRUE(type);
  }
};
}
TEST(wg_lclfunction_macroparamnamesasvarnames_tpl, VarBindImplicit)
{
  try
  {
    VarBindImplicit<bool>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T>
struct VarBindExplicit
{
  static void run()
  {
    T type = false;

    WG_LCLFUNCTION_TPL(check, varbind (type(T &) type) )
    {
      WG_TEST_ASSERT_ISNOTCONST_TPL(type);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T, type);

      type = true;
    }WG_LCLFUNCTION_END;

    check();

    EXPECT_TRUE(type);
  }
};
}
TEST(wg_lclfunction_macroparamnamesasvarnames_tpl, VarBindExplicit)
{
  try
  {
    VarBindExplicit<bool>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T>
struct VarSetImplicit
{
  static void run()
  {
    struct
    {
      T didAssign;
    } proxy = {false};

    WG_LCLFUNCTION_TPL(check, varset (ref type, proxy.didAssign) )
    {
      WG_TEST_ASSERT_ISNOTCONST_TPL(type);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T, type);

      type = true;
    }WG_LCLFUNCTION_END;

    check();

    EXPECT_TRUE(proxy.didAssign);
  }
};
}
TEST(wg_lclfunction_macroparamnamesasvarnames_tpl, VarSetImplicit)
{
  try
  {
    VarSetImplicit<bool>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T>
struct VarSetExplicit
{
  static void run()
  {
    struct
    {
      T didAssign;
    } proxy = {false};

    WG_LCLFUNCTION_TPL(check, varset (type(T &) type, proxy.didAssign) )
    {
      WG_TEST_ASSERT_ISNOTCONST_TPL(type);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T, type);

      type = true;
    }WG_LCLFUNCTION_END;

    check();

    EXPECT_TRUE(proxy.didAssign);
  }
};
}
TEST(wg_lclfunction_macroparamnamesasvarnames_tpl, VarSetExplicit)
{
  try
  {
    VarSetExplicit<bool>::run();
  }
  WG_GTEST_CATCH
}
