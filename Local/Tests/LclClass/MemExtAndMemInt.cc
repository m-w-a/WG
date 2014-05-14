#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/Tests/Utils/Utils.hh>
#include <WG/Local/LclClass.hh>
#include <string>

TEST(wg_lclclass_memextandmemint, ExplicitAndExplicit)
{
  try
  {
    short id = 987;

    WG_LCLCLASS
    (MultiVar,
      memext (type(short) id)
      memint (type(std::string const &) name, "BigFoot") )
      void init()
      {
        WG_TEST_ASSERT_ISNOTCONST(id);
        WG_TEST_ASSERT_ISCONST(name);

        WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(short, id);
        WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(std::string, name);

        EXPECT_EQ(id, 987);
        EXPECT_EQ("BigFoot", name);
      }
    WG_LCLCLASS_END;

    MultiVar obj(id);
  }
  WG_GTEST_CATCH
}

TEST(wg_lclclass_memextandmemint, ExplicitAndImplicit)
{
  try
  {
    short id = 987;

    WG_LCLCLASS
    (MultiVar,
      memext (type(short) id)
      memint (const name, std::string("BigFoot")) )
      void init()
      {
        WG_TEST_ASSERT_ISNOTCONST(id);
        WG_TEST_ASSERT_ISCONST(name);

        WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(short, id);
        WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(std::string, name);

        EXPECT_EQ(id, 987);
        EXPECT_EQ("BigFoot", name);
      }
    WG_LCLCLASS_END;

    MultiVar obj(id);
  }
  WG_GTEST_CATCH
}

TEST(wg_lclclass_memextandmemint, ImplicitAndExplicit)
{
  try
  {
    short id = 987;

    WG_LCLCLASS
    (MultiVar,
      memext (id)
      memint (type(std::string const &) name, "BigFoot") )
      void init()
      {
        WG_TEST_ASSERT_ISNOTCONST(id);
        WG_TEST_ASSERT_ISCONST(name);

        WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(short, id);
        WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(std::string, name);

        EXPECT_EQ(id, 987);
        EXPECT_EQ("BigFoot", name);
      }
    WG_LCLCLASS_END;

    MultiVar obj(id);
  }
  WG_GTEST_CATCH
}

TEST(wg_lclclass_memextandmemint, ImplicitAndImplicit)
{
  try
  {
    short id = 987;

    WG_LCLCLASS
    (MultiVar,
      memext (id)
      memint (const name, std::string("BigFoot")) )
      void init()
      {
        WG_TEST_ASSERT_ISNOTCONST(id);
        WG_TEST_ASSERT_ISCONST(name);

        WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(short, id);
        WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(std::string, name);

        EXPECT_EQ(id, 987);
        EXPECT_EQ("BigFoot", name);
      }
    WG_LCLCLASS_END;

    MultiVar obj(id);
  }
  WG_GTEST_CATCH
}
