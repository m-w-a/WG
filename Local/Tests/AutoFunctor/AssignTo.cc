#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>

TEST(wg_autofunctor_assignto, OkIfNonLocalExplicit)
{
  try
  {
    bool didAssign = 0;

    WG_AUTOFUNCTOR(assign, assignto ((bool) didAssign) )
    {
      return true;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_TRUE(didAssign);
  }
  WG_GTEST_CATCH
}

TEST(wg_autofunctor_assignto, OkIfNonLocalImplicit)
{
  try
  {
    bool didAssign = 0;

    WG_AUTOFUNCTOR(assign, assignto (didAssign) )
    {
      return true;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_TRUE(didAssign);
  }
  WG_GTEST_CATCH
}

TEST(wg_autofunctor_assignto, OkIfLocal)
{
  try
  {
    struct SomeLocalType
    {
      int value;
    } obj = {0};

    WG_AUTOFUNCTOR(assign, assignto (local(SomeLocalType) obj) )
    {
      SomeLocalType toRet = {1};

      return toRet;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(obj.value, 1);
  }
  WG_GTEST_CATCH
}

TEST(wg_autofunctor_assignto, OkIfLocalRef)
{
  try
  {
    struct SomeLocalType
    {
      int value;
    } obj = {0};

    WG_AUTOFUNCTOR(assign, assignto (local(SomeLocalType) ref obj) )
    {
      static SomeLocalType toRet = {1};

      return toRet;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(obj.value, 1);
  }
  WG_GTEST_CATCH
}
