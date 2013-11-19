#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>
#include <boost/tuple/tuple.hpp>

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

TEST(wg_autofunctor_assignto, OkIfNonLocalExplicitAndGloballyScoped)
{
  try
  {
    ::boost::tuple<bool> didAssign = boost::make_tuple(false);

    WG_AUTOFUNCTOR
    (assign,
      assignto ((::boost::tuple<bool>) didAssign) )
    {
      return boost::make_tuple(true);
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_TRUE(didAssign.get<0>());
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
