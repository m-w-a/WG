#include <gtest/gtest.h>
#include <WG/Local/Tests/Utils/Utils.hh>
#include <WG/Local/LclContext.hh>

TEST(wg_lclcontext_adhoc_variadic, NoBinds)
{
  WG_LCLCONTEXT(
    with_adhoc
    on_enter(int x = 10;) )
  {
  }
  WG_LCLCONTEXT_END1
}

namespace
{

struct Cntr
{
  bool flag;
};

}

TEST(wg_lclcontext_adhoc_variadic, ExplicitBind)
{
  Cntr obj = { false };
  void const * boundVarAddress = 0;

  WG_LCLCONTEXT(
    with_adhoc (type(Cntr const &) obj, type(void const * &) boundVarAddress)
    on_enter(boundVarAddress = &obj)
    on_exit(WG_TEST_ASSERT_ISCONST(obj)) )
  {
    EXPECT_EQ(&obj, boundVarAddress);
  }
  WG_LCLCONTEXT_END1
}

TEST(wg_lclcontext_adhoc_variadic, ImplicitBind)
{
  Cntr obj = { false };
  void const * boundVarAddress = 0;

  WG_LCLCONTEXT(
    with_adhoc (const ref obj, ref boundVarAddress)
    on_enter(boundVarAddress = &obj)
    on_exit(WG_TEST_ASSERT_ISCONST(obj)) )
  {
    EXPECT_EQ(&obj, boundVarAddress);
  }
  WG_LCLCONTEXT_END1
}
