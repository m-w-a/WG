#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/Tests/Utils/Utils.hh>
#include <WG/Local/LclClass.hh>
#include <string>

TEST(wg_lclclass_memextexplicit, 1Var)
{
  try
  {
    WG_LCLCLASS(Local, memext (type(int) value) )
      void init()
      {
        WG_TEST_ASSERT_ISNOTCONST(value);
        WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, value);
      }
    public:
      int getValue() const { return value; }
    WG_LCLCLASS_END;

    Local l(11);
    EXPECT_EQ(11, l.getValue());
  }
  WG_GTEST_CATCH
}

TEST(wg_lclclass_memextexplicit, 3Vars)
{
  try
  {
    short id = 987;
    int age = 111;
    std::string name("BigFoot");

    WG_LCLCLASS
    (MultiVar,
      memext (type(short) id) (type(int const) age) (type(std::string const &) name) )
      void init()
      {
        WG_TEST_ASSERT_ISNOTCONST(id);
        WG_TEST_ASSERT_ISCONST(age);
        WG_TEST_ASSERT_ISCONST(name);

        WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(short, id);
        WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, age);
        WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(std::string, name);
      }
    public:
      short const & getId() const { return id; }
      int const & getAge() const { return age; }
      std::string const & getName() { return name; }
    WG_LCLCLASS_END;

    MultiVar obj(id, age, name);

    WG_TEST_ASSERT_ISNOTREFERENCE(id, obj.getId());
    WG_TEST_ASSERT_ISNOTREFERENCE(age, obj.getAge());
    WG_TEST_ASSERT_ISREFERENCE(name, obj.getName());
  }
  WG_GTEST_CATCH
}

TEST(wg_lclclass_memextexplicit, LocalTypeNonQlfd)
{
  try
  {
    WG_TEST_LOCALTYPE_DECLARE(SomeLocalClass);
    SomeLocalClass localObj;

    WG_LCLCLASS(AnotherLocalClass, memext (lcltype(SomeLocalClass) value) )
      void init()
      {
        WG_TEST_ASSERT_LOCALTYPE_ISNOTCONST(value);
        WG_TEST_ASSERT_LOCALTYPE_ISSAMETYPE_MODULOCONSTANDREF(
          SomeLocalClass, value);
      }
    public:
      SomeLocalClass const & getValue() const { return value; }
    WG_LCLCLASS_END;

    AnotherLocalClass anotherLocalObj(localObj);

    WG_TEST_ASSERT_LOCALTYPE_ISNOTREFERENCE(
      localObj, anotherLocalObj.getValue());
  }
  WG_GTEST_CATCH
}

TEST(wg_lclclass_memextexplicit, LocalTypeConstQlfd)
{
  try
  {
    WG_TEST_LOCALTYPE_DECLARE(SomeLocalClass);
    SomeLocalClass localObj;

    WG_LCLCLASS(AnotherLocalClass, memext (lcltype(SomeLocalClass) const value) )
      void init()
      {
        WG_TEST_ASSERT_LOCALTYPE_ISCONST(value);
        WG_TEST_ASSERT_LOCALTYPE_ISSAMETYPE_MODULOCONSTANDREF(
          SomeLocalClass, value);
      }
    public:
      SomeLocalClass const & getValue() const { return value; }
    WG_LCLCLASS_END;

    AnotherLocalClass anotherLocalObj(localObj);

    WG_TEST_ASSERT_LOCALTYPE_ISNOTREFERENCE(
      localObj, anotherLocalObj.getValue());
  }
  WG_GTEST_CATCH
}

TEST(wg_lclclass_memextexplicit, LocalTypeRefQlfd)
{
  try
  {
    WG_TEST_LOCALTYPE_DECLARE(SomeLocalClass);
    SomeLocalClass localObj;

    WG_LCLCLASS(AnotherLocalClass, memext (lcltype(SomeLocalClass) ref value) )
      void init()
      {
        WG_TEST_ASSERT_LOCALTYPE_ISNOTCONST(value);
        WG_TEST_ASSERT_LOCALTYPE_ISSAMETYPE_MODULOCONSTANDREF(
          SomeLocalClass, value);
      }
    public:
      SomeLocalClass const & getValue() const { return value; }
    WG_LCLCLASS_END;

    AnotherLocalClass anotherLocalObj(localObj);

    WG_TEST_ASSERT_LOCALTYPE_ISREFERENCE(
      localObj, anotherLocalObj.getValue());
  }
  WG_GTEST_CATCH
}

TEST(wg_lclclass_memextexplicit, LocalTypeConstRefQlfd)
{
  try
  {
    WG_TEST_LOCALTYPE_DECLARE(SomeLocalClass);
    SomeLocalClass localObj;

    WG_LCLCLASS
    (AnotherLocalClass, memext (lcltype(SomeLocalClass) const ref value) )
      void init()
      {
        WG_TEST_ASSERT_LOCALTYPE_ISCONST(value);
        WG_TEST_ASSERT_LOCALTYPE_ISSAMETYPE_MODULOCONSTANDREF(
          SomeLocalClass, value);
      }
    public:
      SomeLocalClass const & getValue() const { return value; }
    WG_LCLCLASS_END;

    AnotherLocalClass anotherLocalObj(localObj);

    WG_TEST_ASSERT_LOCALTYPE_ISREFERENCE(
      localObj, anotherLocalObj.getValue());
  }
  WG_GTEST_CATCH
}
