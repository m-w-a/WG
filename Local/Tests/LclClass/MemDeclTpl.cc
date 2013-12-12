#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/Tests/TestHelper.hh>
#include <WG/Local/LclClass.hh>
#include <string>

namespace
{
template <typename T>
struct OneVar
{
  static void run()
  {
    WG_LCLCLASS_TPL(Local, memdecl ((int) value) )
      void init()
      {
        WG_TESTHELPER_ASSERT_ISNOTCONST_TPL(value);
        WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T, value);
      }
    public:
      T getValue() const { return value; }
    WG_LCLCLASS_END;

    Local l(11);
    EXPECT_EQ(11, l.getValue());
  }
};
}
TEST(wg_lclclass_memdecl_tpl, 1Var)
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
      memdecl ((T1) id) ((T2 const) age) ((T3 const &) name) )
      void init()
      {
        WG_TESTHELPER_ASSERT_ISNOTCONST_TPL(id);
        WG_TESTHELPER_ASSERT_ISCONST_TPL(age);
        WG_TESTHELPER_ASSERT_ISCONST_TPL(name);

        WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T1, id);
        WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T2, age);
        WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T3, name);
      }
    public:
      T1 const & getId() const { return id; }
      T2 const & getAge() const { return age; }
      T3 const & getName() { return name; }
    WG_LCLCLASS_END;

    MultiVar obj(id, age, name);

    WG_TESTHELPER_ASSERT_ISNOTREFERENCE(id, obj.getId());
    WG_TESTHELPER_ASSERT_ISNOTREFERENCE(age, obj.getAge());
    WG_TESTHELPER_ASSERT_ISREFERENCE(name, obj.getName());
  }
};
}
TEST(wg_lclclass_memdecl_tpl, 3Vars)
{
  try
  {
    ThreeVars<short, int, std::string>::run();
  }
  WG_GTEST_CATCH
}

