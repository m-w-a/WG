#include <gtest/gtest.h>
#include <boost/config.hpp>
#include <WG/Local/LclContext.hh>
#include <WG/Local/Tests/Utils/Utils.hh>

namespace
{

struct BindThisU
{
  void run()
  {
    Id = 10;
    WG_LCLCONTEXT(
      with_adhoc (this_)
        on_enter(this_->Id = 11)
        on_exit(this_->Id = 12) )
    {
      EXPECT_EQ(11, Id);
    }
    WG_LCLCONTEXT_END1

    EXPECT_EQ(12, Id);
  }

private:
  int Id;
};

}

TEST(wg_lclcontext_adhoc_varbindimplicit, BindThisU)
{
  BindThisU b;
  b.run();
}

namespace
{

struct BindConstThisU
{
  void run()
  {
    WG_LCLCONTEXT(
      with_adhoc (const this_)
      on_enter(WG_TEST_ASSERT_ISCONST(*this_)) )
    {
    }
    WG_LCLCONTEXT_END1
  }
};

}
TEST(wg_lclcontext_adhoc_varbindimplicit, BindConstThisU)
{
  BindConstThisU b;
  b.run();
}

TEST(wg_lclcontext_adhoc_varbindimplicit, BindByValue)
{
  bool var = false;

  WG_LCLCONTEXT( with_adhoc (var) on_exit(var = true;) )
  {
  }
  WG_LCLCONTEXT_END1

  EXPECT_FALSE(var);
}

TEST(wg_lclcontext_adhoc_varbindimplicit, BindByConstValue)
{
  bool var = false;

  WG_LCLCONTEXT(
    with_adhoc (const var)
      on_exit(WG_TEST_ASSERT_ISCONST(var);) )
  {
  }
  WG_LCLCONTEXT_END1
}

TEST(wg_lclcontext_adhoc_varbindimplicit, BindByRef)
{
  bool var = false;

  WG_LCLCONTEXT( with_adhoc (ref var) on_exit(var = true;) )
  {
  }
  WG_LCLCONTEXT_END1

  EXPECT_TRUE(var);
}

TEST(wg_lclcontext_adhoc_varbindimplicit, BindByConstRef)
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
struct InTemplate
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
TEST(wg_lclcontext_adhoc_varbindimplicit, InTemplate)
{
  InTemplate<bool>::run();
}
