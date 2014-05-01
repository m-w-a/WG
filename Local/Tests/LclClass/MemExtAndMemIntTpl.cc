#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/Tests/TestHelper.hh>
#include <WG/Local/LclClass.hh>
#include <string>

namespace
{
template <typename T1, typename T2>
struct ExplictAndExplicit
{
  static void run()
  {
    T1 id = 987;

    WG_LCLCLASS_TPL
    (MultiVar,
      memext (type(T1) id)
      memint (type(T2 const &) name, "BigFoot") )
      void init()
      {
        WG_TESTHELPER_ASSERT_ISNOTCONST_TPL(id);
        WG_TESTHELPER_ASSERT_ISCONST_TPL(name);

        WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T1, id);
        WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T2, name);

        EXPECT_EQ(id, 987);
        EXPECT_EQ("BigFoot", name);
      }
    WG_LCLCLASS_END;

    MultiVar obj(id);
  }
};
}
TEST(wg_lclclass_memextandmemint_tpl, ExplictAndExplicit)
{
  try
  {
    ExplictAndExplicit<short, std::string>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T1, typename T2>
struct ExplicitAndImplicit
{
  static void run()
  {
    T1 id = 987;

    WG_LCLCLASS_TPL
    (MultiVar,
      memext (type(T1) id)
      memint (const ref name, T2("BigFoot")) )
      void init()
      {
        WG_TESTHELPER_ASSERT_ISNOTCONST_TPL(id);
        WG_TESTHELPER_ASSERT_ISCONST_TPL(name);

        WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T1, id);
        WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T2, name);

        EXPECT_EQ(id, 987);
        EXPECT_EQ("BigFoot", name);
      }
    WG_LCLCLASS_END;

    MultiVar obj(id);
  }
};
}
TEST(wg_lclclass_memextandmemint_tpl, ExplicitAndImplicit)
{
  try
  {
    ExplicitAndImplicit<short, std::string>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T1, typename T2>
struct ImplicitAndExplicit
{
  static void run()
  {
    T1 id = 987;

    WG_LCLCLASS_TPL
    (MultiVar,
      memext (id)
      memint (type(T2 const &) name, "BigFoot") )
      void init()
      {
        WG_TESTHELPER_ASSERT_ISNOTCONST_TPL(id);
        WG_TESTHELPER_ASSERT_ISCONST_TPL(name);

        WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T1, id);
        WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T2, name);

        EXPECT_EQ(id, 987);
        EXPECT_EQ("BigFoot", name);
      }
    WG_LCLCLASS_END;

    MultiVar obj(id);
  }
};
}
TEST(wg_lclclass_memextandmemint_tpl, ImplicitAndExplicit)
{
  try
  {
    ImplicitAndExplicit<short, std::string>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T1, typename T2>
struct ImplicitAndImplicit
{
  static void run()
  {
    T1 id = 987;

    WG_LCLCLASS_TPL
    (MultiVar,
      memext (id)
      memint (const ref name, T2("BigFoot")) )
      void init()
      {
        WG_TESTHELPER_ASSERT_ISNOTCONST_TPL(id);
        WG_TESTHELPER_ASSERT_ISCONST_TPL(name);

        WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T1, id);
        WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T2, name);

        EXPECT_EQ(id, 987);
        EXPECT_EQ("BigFoot", name);
      }
    WG_LCLCLASS_END;

    MultiVar obj(id);
  }
};
}
TEST(wg_lclclass_memextandmemint_tpl, ImplicitAndImplicit)
{
  try
  {
    ImplicitAndExplicit<short, std::string>::run();
  }
  WG_GTEST_CATCH
}
