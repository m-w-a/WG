#include <gtest/gtest.h>
#include <boost/config.hpp>
#include <WG/Local/LclContext.hh>
#include <WG/Local/Tests/Utils/Utils.hh>

namespace
{

struct Cntr
{
  bool flag;
};

}

TEST(wg_lclcontext_adhoc_varbindexplicit, BindByValue)
{
  Cntr obj = { false };

  WG_LCLCONTEXT(
    with_adhoc (type(Cntr) obj)
    on_enter( obj.flag = true; ) )
  {
  }
  WG_LCLCONTEXT_END1

  EXPECT_FALSE(obj.flag);
}

TEST(wg_lclcontext_adhoc_varbindexplicit, BindByConstValue)
{
  Cntr obj = { false };

  WG_LCLCONTEXT(
    with_adhoc (type(Cntr const) obj)
    on_enter(WG_TEST_ASSERT_ISCONST(obj);) )
  {
  }
  WG_LCLCONTEXT_END1
}

TEST(wg_lclcontext_adhoc_varbindexplicit, BindByRef)
{
  Cntr obj = { false };

  WG_LCLCONTEXT(
    with_adhoc (type(Cntr &) obj)
    on_enter( obj.flag = true; ) )
  {
  }
  WG_LCLCONTEXT_END1;

  EXPECT_TRUE(obj.flag);
}

TEST(wg_lclcontext_adhoc_varbindexplicit, BindByConstRef)
{
  Cntr obj = { false };
  void const * boundVarAddress = 0;

  WG_LCLCONTEXT(
    with_adhoc (type(Cntr const &) obj) (type(void const * &) boundVarAddress)
    on_enter(boundVarAddress = &obj)
    on_exit(WG_TEST_ASSERT_ISCONST(obj)) )
  {
    EXPECT_EQ(&obj, boundVarAddress);
  }
  WG_LCLCONTEXT_END1
}

namespace
{

template <typename T>
struct InTemplate
{
  static void run()
  {
    T obj = { false };
    void const * boundVarAddress = 0;

    WG_LCLCONTEXT_TPL(
      with_adhoc (type(T &) obj) (type(void const * &) boundVarAddress)
      on_enter(boundVarAddress = &obj)
      on_exit(obj.flag = true;) )
    {
      EXPECT_EQ(&obj, boundVarAddress);
    }
    WG_LCLCONTEXT_END1

    EXPECT_TRUE(obj.flag);
  }
};

}
TEST(wg_lclcontext_adhoc_varbindexplicit, InTemplate)
{
  InTemplate<Cntr>::run();
}
