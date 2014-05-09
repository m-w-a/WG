#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/Tests/Utils/Utils.hh>
#include <WG/Local/LclClass.hh>
#include <string>

namespace
{
struct ignore;
}

namespace
{
template <typename T>
struct OneVar
{
  static void run()
  {
    WG_LCLCLASS_TPL(Local, memext (type(int) value) )
      void init()
      {
        WG_TEST_ASSERT_ISNOTCONST_TPL(value);
        WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T, value);
      }
    public:
      T getValue() const { return value; }
    WG_LCLCLASS_END;

    Local l(11);
    EXPECT_EQ(11, l.getValue());
  }
};
}
TEST(wg_lclclass_memextexplicit_tpl, 1Var)
{
  try
  {
    OneVar<int>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T1, typename T2, typename T3>
struct ThreeVars
{
  static void run()
  {
    T1 id = 987;
    T2 age = 111;
    T3 name("BigFoot");

    WG_LCLCLASS_TPL
    (MultiVar,
      memext (type(T1) id) (type(T2 const) age) (type(T3 const &) name) )
      void init()
      {
        WG_TEST_ASSERT_ISNOTCONST_TPL(id);
        WG_TEST_ASSERT_ISCONST_TPL(age);
        WG_TEST_ASSERT_ISCONST_TPL(name);

        WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T1, id);
        WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T2, age);
        WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T3, name);
      }
    public:
      T1 const & getId() const { return id; }
      T2 const & getAge() const { return age; }
      T3 const & getName() { return name; }
    WG_LCLCLASS_END;

    MultiVar obj(id, age, name);

    WG_TEST_ASSERT_ISNOTREFERENCE(id, obj.getId());
    WG_TEST_ASSERT_ISNOTREFERENCE(age, obj.getAge());
    WG_TEST_ASSERT_ISREFERENCE(name, obj.getName());
  }
};
}
TEST(wg_lclclass_memextexplicit_tpl, 3Vars)
{
  try
  {
    ThreeVars<short, int, std::string>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename IGNORED>
struct LocalTypeNonQlfd
{
  static void run()
  {
    WG_TEST_LOCALTYPE_DECLARE(SomeLocalClass);
    SomeLocalClass localObj;

    WG_LCLCLASS_TPL(AnotherLocalClass, memext (lcltype(SomeLocalClass) value) )
      void init()
      {
        WG_TEST_ASSERT_LOCALTYPE_ISNOTCONST_TPL(value);
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
};
}
TEST(wg_lclclass_memextexplicit_tpl, LocalTypeNonQlfd)
{
  try
  {
    LocalTypeNonQlfd<ignore>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename IGNORED>
struct LocalTypeConstQlfd
{
  static void run()
  {
    WG_TEST_LOCALTYPE_DECLARE(SomeLocalClass);
    SomeLocalClass localObj;

    WG_LCLCLASS_TPL
    (AnotherLocalClass, memext (lcltype(SomeLocalClass) const value) )
      void init()
      {
        WG_TEST_ASSERT_LOCALTYPE_ISCONST_TPL(value);
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
};
}
TEST(wg_lclclass_memextexplicit_tpl, LocalTypeConstQlfd)
{
  try
  {
    LocalTypeConstQlfd<ignore>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename IGNORED>
struct LocalTypeRefQlfd
{
  static void run()
  {
    WG_TEST_LOCALTYPE_DECLARE(SomeLocalClass);
    SomeLocalClass localObj;

    WG_LCLCLASS_TPL
    (AnotherLocalClass, memext (lcltype(SomeLocalClass) ref value) )
      void init()
      {
        WG_TEST_ASSERT_LOCALTYPE_ISNOTCONST_TPL(value);
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
};
}
TEST(wg_lclclass_memextexplicit_tpl, LocalTypeRefQlfd)
{
  try
  {
    LocalTypeRefQlfd<ignore>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename IGNORED>
struct LocalTypeConstRefQlfd
{
  static void run()
  {
    WG_TEST_LOCALTYPE_DECLARE(SomeLocalClass);
    SomeLocalClass localObj;

    WG_LCLCLASS_TPL
    (AnotherLocalClass, memext (lcltype(SomeLocalClass) const ref value) )
      void init()
      {
        WG_TEST_ASSERT_LOCALTYPE_ISCONST_TPL(value);
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
};
}
TEST(wg_lclclass_memextexplicit_tpl, LocalTypeConstRefQlfd)
{
  try
  {
    LocalTypeConstRefQlfd<ignore>::run();
  }
  WG_GTEST_CATCH
}
