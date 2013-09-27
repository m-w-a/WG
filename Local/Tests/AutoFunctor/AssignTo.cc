#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>
#include <utility>

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

TEST(wg_autofunctor_assignto, OkIfNonLocalExplicitPPEscaped)
{
  try
  {
    std::pair<bool, int> didAssign = std::make_pair(false, 0);

    WG_AUTOFUNCTOR
    (assign,
      assignto (ppescape((std::pair<bool, int>)) didAssign) )
    {
      return std::make_pair(true, 1);
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_TRUE(didAssign.first);
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

// TODO.
// Should result in a compiler error.
//TEST(wg_autofunctor_assignto, notOkIfLocalConst)
//{
//  try
//  {
//    struct SomeLocalType
//    {
//      int value;
//    } obj = {0};
//
//    WG_AUTOFUNCTOR(assign, assignto (local(SomeLocalType) const obj) )
//    {
//      static SomeLocalType toRet = {1};
//
//      return toRet;
//    }
//    WG_AUTOFUNCTOR_END;
//
//    EXPECT_EQ(obj.value, 1);
//  }
//  WG_GTEST_CATCH
//}

// TODO.
// Should result in a compiler error.
//TEST(wg_autofunctor_assignto, notOkIfLocalConstRef)
//{
//  try
//  {
//    struct SomeLocalType
//    {
//      int value;
//    } obj = {0};
//
//    WG_AUTOFUNCTOR(assign, assignto (local(SomeLocalType) const ref obj) )
//    {
//      static SomeLocalType toRet = {1};
//
//      return toRet;
//    }
//    WG_AUTOFUNCTOR_END;
//
//    EXPECT_EQ(obj.value, 1);
//  }
//  WG_GTEST_CATCH
//}
