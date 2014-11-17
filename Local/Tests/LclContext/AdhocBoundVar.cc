#include <gtest/gtest.h>
#include <boost/config.hpp>
#include <WG/Local/LclContext.hh>
#include <WG/Local/Tests/Utils/Utils.hh>

TEST(wg_lclcontext_adhoc, BindVarByValue)
{
  bool var = false;

  WG_LCLCONTEXT( with_adhoc (var) on_exit(var = true;) )
  {
  }
  WG_LCLCONTEXT_END1

  EXPECT_FALSE(var);
}

TEST(wg_lclcontext_adhoc, BindVarByConstValue)
{
  bool var = false;

  WG_LCLCONTEXT(
    with_adhoc (const var)
      on_exit(WG_TEST_ASSERT_ISCONST(var);) )
  {
  }
  WG_LCLCONTEXT_END1
}

TEST(wg_lclcontext_adhoc, BindVarByRef)
{
  bool var = false;

  WG_LCLCONTEXT( with_adhoc (ref var) on_exit(var = true;) )
  {
  }
  WG_LCLCONTEXT_END1

  EXPECT_TRUE(var);
}

TEST(wg_lclcontext_adhoc, BindVarByConstRef)
{
  bool var = false;
  void const * boundVarAddress = 0;

  WG_LCLCONTEXT(
    with_adhoc (const ref var) (ref boundVarAddress)
      on_enter(boundVarAddress = &var)
      on_exit(WG_TEST_ASSERT_ISCONST(var);) )
  {
    EXPECT_EQ(&var, boundVarAddress);
  }
  WG_LCLCONTEXT_END1
}

namespace
{

template <typename T>
struct BindVarInTemplate
{
  static void run()
  {
    T var = false;
    void const * boundVarAddress = 0;

    WG_LCLCONTEXT_TPL(
      with_adhoc (const ref var) (ref boundVarAddress)
        on_enter(boundVarAddress = &var)
        on_exit(WG_TEST_ASSERT_ISCONST_TPL(var);) )
    {
      EXPECT_EQ(&var, boundVarAddress);
    }
    WG_LCLCONTEXT_END1
  }
};

}
TEST(wg_lclcontext_adhoc, BindVarInTemplate)
{
  BindVarInTemplate<bool>::run();
}
