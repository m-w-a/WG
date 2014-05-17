#include <gtest/gtest.h>
#include <WG/Local/Tests/LclFunction/Utils/TestLclFunction.hh>
#include <WG/Local/Tests/Utils/Utils.hh>

namespace
{
template <typename T>
struct VarBindImplicit
{
  static void run()
  {
    T type = false;

    WG_TEST_LCLFUNCTION_TPL(check, varbind (ref type) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(check);

      WG_TEST_ASSERT_ISNOTCONST_TPL(type);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T, type);

      type = true;
    }WG_TEST_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(
      WG_LCLFUNCTION_TYPENAME(check),
      check);

    check();
    WG_TEST_LCLFUNCTION_VERIFYCALL(check);

    EXPECT_TRUE(type);
  }
};
}
TEST(wg_lclfunction_macroparamnamesasvarnames_tpl, VarBindImplicit)
{
  VarBindImplicit<bool>::run();
}

namespace
{
template <typename T>
struct VarBindExplicit
{
  static void run()
  {
    T type = false;

    WG_TEST_LCLFUNCTION_TPL(check, varbind (type(T &) type) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(check);

      WG_TEST_ASSERT_ISNOTCONST_TPL(type);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T, type);

      type = true;
    }WG_TEST_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(
      WG_LCLFUNCTION_TYPENAME(check),
      check);

    check();
    WG_TEST_LCLFUNCTION_VERIFYCALL(check);

    EXPECT_TRUE(type);
  }
};
}
TEST(wg_lclfunction_macroparamnamesasvarnames_tpl, VarBindExplicit)
{
  VarBindExplicit<bool>::run();
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

    WG_TEST_LCLFUNCTION_TPL(check, varset (ref type, proxy.didAssign) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(check);

      WG_TEST_ASSERT_ISNOTCONST_TPL(type);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T, type);

      type = true;
    }WG_TEST_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(
      WG_LCLFUNCTION_TYPENAME(check),
      check);

    check();
    WG_TEST_LCLFUNCTION_VERIFYCALL(check);

    EXPECT_TRUE(proxy.didAssign);
  }
};
}
TEST(wg_lclfunction_macroparamnamesasvarnames_tpl, VarSetImplicit)
{
  VarSetImplicit<bool>::run();
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

    WG_TEST_LCLFUNCTION_TPL(check, varset (type(T &) type, proxy.didAssign) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(check);

      WG_TEST_ASSERT_ISNOTCONST_TPL(type);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T, type);

      type = true;
    }WG_TEST_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(
      WG_LCLFUNCTION_TYPENAME(check),
      check);

    check();
    WG_TEST_LCLFUNCTION_VERIFYCALL(check);

    EXPECT_TRUE(proxy.didAssign);
  }
};
}
TEST(wg_lclfunction_macroparamnamesasvarnames_tpl, VarSetExplicit)
{
  VarSetExplicit<bool>::run();
}
