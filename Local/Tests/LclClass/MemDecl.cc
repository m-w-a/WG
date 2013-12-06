//#include <gtest/gtest.h>
//#include <WG/GTest/Exceptions.hh>
#include <WG/Local/Tests/TestHelper.hh>
#include <WG/Local/LclClass.hh>

TEST(wg_lclclass_memdecl, 1Var)
{
  try
  {
    WG_LCLCLASS(Local, memdecl ((int) value) )
      void init()
      {
        WG_PP_TESTHELPER_ASSERT_ISNOTCONST(value);
        WG_PP_TESTHELPER_ASSERT_ISSAMETYPE(int, BOOST_TYPEOF(value));
      }
      int getValue() const { return value; }
    WG_LCLCLASS_END;

    Local l(11);
    EXPECT_EQ(11, l.getValue());
  }
  WG_GTEST_CATCH
}

TEST(wg_lclclass_memdecl, LocalTypeNonQlfd)
{
  try
  {
    WG_TESTHELPER_LOCALTYPE_DECLARE(SomeLocalClass);
    SomeLocalClass localObj;

    WG_LCLCLASS(AnotherLocalClass, memdecl (local(SomeLocalClass) value) )
      void init()
      {
        WG_TESTHELPER_LOCALTYPE_ISNOTCONST(value);
        WG_TESTHELPER_LOCALTYPE_ISSAMETYPE(SomeLocalClass, value);
      }
      SomeLocalClass const & getValue() const { return value; }
    WG_LCLCLASS_END;

    AnotherLocalClass anotherLocalObj(localObj);

    WG_TESTHELPER_ASSERT_ISNOTREFERENCE(localObj, anotherLocalObj.value);
  }
  WG_GTEST_CATCH
}

TEST(wg_lclclass_memdecl, LocalTypeConstQlfd)
{
  try
  {
    WG_TESTHELPER_LOCALTYPE_DECLARE(SomeLocalClass);
    SomeLocalClass localObj;

    WG_LCLCLASS(AnotherLocalClass, memdecl (local(SomeLocalClass) const value) )
      void init()
      {
        WG_TESTHELPER_LOCALTYPE_ISCONST(value);
        WG_TESTHELPER_LOCALTYPE_ISSAMETYPE(SomeLocalClass, value);
      }
      SomeLocalClass const & getValue() const { return value; }
    WG_LCLCLASS_END;

    AnotherLocalClass anotherLocalObj(localObj);

    WG_TESTHELPER_ASSERT_ISNOTREFERENCE(localObj, anotherLocalObj.value);
  }
  WG_GTEST_CATCH
}

TEST(wg_lclclass_memdecl, LocalTypeRefQlfd)
{
  try
  {
    WG_TESTHELPER_LOCALTYPE_DECLARE(SomeLocalClass);
    SomeLocalClass localObj;

    WG_LCLCLASS(AnotherLocalClass, memdecl (local(SomeLocalClass) ref value) )
      void init()
      {
        WG_TESTHELPER_LOCALTYPE_ISNOTCONST(value);
        WG_TESTHELPER_LOCALTYPE_ISSAMETYPE(SomeLocalClass, value);
      }
      SomeLocalClass const & getValue() const { return value; }
    WG_LCLCLASS_END;

    AnotherLocalClass anotherLocalObj(localObj);

    WG_TESTHELPER_ASSERT_ISREFERENCE(localObj, anotherLocalObj.value);
  }
  WG_GTEST_CATCH
}

TEST(wg_lclclass_memdecl, LocalTypeConstRefQlfd)
{
  try
  {
    WG_TESTHELPER_LOCALTYPE_DECLARE(SomeLocalClass);
    SomeLocalClass localObj;

    WG_LCLCLASS
    (AnotherLocalClass, memdecl (local(SomeLocalClass) const ref value) )
      void init()
      {
        WG_TESTHELPER_LOCALTYPE_ISCONST(value);
        WG_TESTHELPER_LOCALTYPE_ISSAMETYPE(SomeLocalType, value);
      }
      SomeLocalClass const & getValue() const { return value; }
    WG_LCLCLASS_END;

    AnotherLocalClass anotherLocalObj(localObj);

    WG_TESTHELPER_ASSERT_ISREFERENCE(localObj, anotherLocalObj.value);
  }
  WG_GTEST_CATCH
}
