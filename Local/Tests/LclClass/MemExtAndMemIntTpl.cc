#include <gtest/gtest.h>
#include <WG/Local/Tests/Utils/Utils.hh>
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
        WG_TEST_ASSERT_ISNOTCONST_TPL(id);
        WG_TEST_ASSERT_ISCONST_TPL(name);

        WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T1, id);
        WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T2, name);

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
  ExplictAndExplicit<short, std::string>::run();
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
        WG_TEST_ASSERT_ISNOTCONST_TPL(id);
        WG_TEST_ASSERT_ISCONST_TPL(name);

        WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T1, id);
        WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T2, name);

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
  ExplicitAndImplicit<short, std::string>::run();
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
        WG_TEST_ASSERT_ISNOTCONST_TPL(id);
        WG_TEST_ASSERT_ISCONST_TPL(name);

        WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T1, id);
        WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T2, name);

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
  ImplicitAndExplicit<short, std::string>::run();
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
        WG_TEST_ASSERT_ISNOTCONST_TPL(id);
        WG_TEST_ASSERT_ISCONST_TPL(name);

        WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T1, id);
        WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T2, name);

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
  ImplicitAndExplicit<short, std::string>::run();
}
