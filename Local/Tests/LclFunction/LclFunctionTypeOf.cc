#include <gtest/gtest.h>
#include <WG/Local/Tests/LclFunction/Utils/TestLclFunction.hh>
#include <boost/type_traits/is_same.hpp>
#include <WG/Local/Tests/Utils/Utils.hh>

//---------------
//VarBindExplicit
//---------------

TEST(wg_lclfunction_typeof, VarBindExplicitByValue)
{
  int var = 11;

  WG_TEST_LCLFUNCTION(noop, varbind (type(int) var) )
  {
    WG_TEST_LCLFUNCTION_MARKCALL(noop);

    (void)var;
    EXPECT_TRUE(( boost::is_same<WG_LCLFUNCTION_VAR_TYPEOF(var), int>::value ));
  }
  WG_TEST_LCLFUNCTION_END;

  WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
    WG_LCLFUNCTION_TYPENAME(noop),
    noop);

  noop();
  WG_TEST_LCLFUNCTION_VERIFYCALL(noop);
}

TEST(wg_lclfunction_typeof, VarBindExplicitByRef)
{
  int var = 11;

  WG_TEST_LCLFUNCTION(noop, varbind (type(int &) var) )
  {
    WG_TEST_LCLFUNCTION_MARKCALL(noop);

    (void)var;
    EXPECT_TRUE(( boost::is_same<WG_LCLFUNCTION_VAR_TYPEOF(var), int &>::value ));
  }
  WG_TEST_LCLFUNCTION_END;

  WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
    WG_LCLFUNCTION_TYPENAME(noop),
    noop);

  noop();
  WG_TEST_LCLFUNCTION_VERIFYCALL(noop);
}

TEST(wg_lclfunction_typeof, VarBindExplicitByConst)
{
  int var = 11;

  WG_TEST_LCLFUNCTION(noop, varbind (type(int const) var) )
  {
    WG_TEST_LCLFUNCTION_MARKCALL(noop);

    (void)var;
    EXPECT_TRUE(( boost::is_same<WG_LCLFUNCTION_VAR_TYPEOF(var), int const>::value ));
  }
  WG_TEST_LCLFUNCTION_END;

  WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
    WG_LCLFUNCTION_TYPENAME(noop),
    noop);

  noop();
  WG_TEST_LCLFUNCTION_VERIFYCALL(noop);
}

//---------------
//VarBindImplicit
//---------------

TEST(wg_lclfunction_typeof, VarBindImplicitByValue)
{
  int var = 11;

  WG_TEST_LCLFUNCTION(noop, varbind (var) )
  {
    WG_TEST_LCLFUNCTION_MARKCALL(noop);

    (void)var;
    EXPECT_TRUE((
      boost::is_same<WG_LCLFUNCTION_VAR_TYPEOF(var), BOOST_TYPEOF(var)>::value ));
  }
  WG_TEST_LCLFUNCTION_END;

  WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
    WG_LCLFUNCTION_TYPENAME(noop),
    noop);

  noop();
  WG_TEST_LCLFUNCTION_VERIFYCALL(noop);
}

TEST(wg_lclfunction_typeof, VarBindImplicitByRef)
{
  int var = 11;

  WG_TEST_LCLFUNCTION(noop, varbind (ref var) )
  {
    WG_TEST_LCLFUNCTION_MARKCALL(noop);

    (void)var;
    EXPECT_TRUE((
      boost::is_same<WG_LCLFUNCTION_VAR_TYPEOF(var), BOOST_TYPEOF(var) &>::value ));
  }
  WG_TEST_LCLFUNCTION_END;

  WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
    WG_LCLFUNCTION_TYPENAME(noop),
    noop);

  noop();
  WG_TEST_LCLFUNCTION_VERIFYCALL(noop);
}

TEST(wg_lclfunction_typeof, VarBindImplicitByConst)
{
  int var = 11;

  WG_TEST_LCLFUNCTION(noop, varbind (const var) )
  {
    WG_TEST_LCLFUNCTION_MARKCALL(noop);

    (void)var;
    EXPECT_TRUE((
      boost::is_same
      <
        WG_LCLFUNCTION_VAR_TYPEOF(var),
        BOOST_TYPEOF(var) const
      >::value ));
  }
  WG_TEST_LCLFUNCTION_END;

  WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
    WG_LCLFUNCTION_TYPENAME(noop),
    noop);

  noop();
  WG_TEST_LCLFUNCTION_VERIFYCALL(noop);
}

TEST(wg_lclfunction_typeof, VarBindImplicitByConstRef)
{
  int var = 11;

  WG_TEST_LCLFUNCTION(noop, varbind (const ref var) )
  {
    WG_TEST_LCLFUNCTION_MARKCALL(noop);

    (void)var;
    EXPECT_TRUE((
      boost::is_same
      <
        WG_LCLFUNCTION_VAR_TYPEOF(var),
        BOOST_TYPEOF(var) const &
      >::value ));
  }
  WG_TEST_LCLFUNCTION_END;

  WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
    WG_LCLFUNCTION_TYPENAME(noop),
    noop);

  noop();
  WG_TEST_LCLFUNCTION_VERIFYCALL(noop);
}

//---------------
//VarSetExplicit
//---------------

TEST(wg_lclfunction_typeof, VarSetExplicitByValue)
{
  WG_TEST_LCLFUNCTION(noop, varset (type(int) var, 5) )
  {
    WG_TEST_LCLFUNCTION_MARKCALL(noop);

    (void)var;
    EXPECT_TRUE(( boost::is_same<WG_LCLFUNCTION_VAR_TYPEOF(var), int>::value ));
  }
  WG_TEST_LCLFUNCTION_END;

  WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
    WG_LCLFUNCTION_TYPENAME(noop),
    noop);

  noop();
  WG_TEST_LCLFUNCTION_VERIFYCALL(noop);
}

TEST(wg_lclfunction_typeof, VarSetExplicitByRef)
{
  int var = 11;

  WG_TEST_LCLFUNCTION(noop, varset (type(int &) var, var) )
  {
    WG_TEST_LCLFUNCTION_MARKCALL(noop);

    (void)var;
    EXPECT_TRUE(( boost::is_same<WG_LCLFUNCTION_VAR_TYPEOF(var), int &>::value ));
  }
  WG_TEST_LCLFUNCTION_END;

  WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
    WG_LCLFUNCTION_TYPENAME(noop),
    noop);

  noop();
  WG_TEST_LCLFUNCTION_VERIFYCALL(noop);
}

TEST(wg_lclfunction_typeof, VarSetExplicitByConst)
{
  WG_TEST_LCLFUNCTION(noop, varset (type(int const) var, 5) )
  {
    WG_TEST_LCLFUNCTION_MARKCALL(noop);

    (void)var;
    EXPECT_TRUE(( boost::is_same<WG_LCLFUNCTION_VAR_TYPEOF(var), int const>::value ));
  }
  WG_TEST_LCLFUNCTION_END;

  WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
    WG_LCLFUNCTION_TYPENAME(noop),
    noop);

  noop();
  WG_TEST_LCLFUNCTION_VERIFYCALL(noop);
}

//--------------
//VarSetImplicit
//--------------

TEST(wg_lclfunction_typeof, VarSetImplicitByValue)
{
  WG_TEST_LCLFUNCTION(noop, varset (var, 11) )
  {
    WG_TEST_LCLFUNCTION_MARKCALL(noop);

    (void)var;
    EXPECT_TRUE((
      boost::is_same<WG_LCLFUNCTION_VAR_TYPEOF(var), BOOST_TYPEOF(var)>::value ));
  }
  WG_TEST_LCLFUNCTION_END;

  WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
    WG_LCLFUNCTION_TYPENAME(noop),
    noop);

  noop();
  WG_TEST_LCLFUNCTION_VERIFYCALL(noop);
}

TEST(wg_lclfunction_typeof, VarSetImplicitByRef)
{
  int var = 11;

  WG_TEST_LCLFUNCTION(noop, varset (ref var, var) )
  {
    WG_TEST_LCLFUNCTION_MARKCALL(noop);

    (void)var;
    EXPECT_TRUE((
      boost::is_same<WG_LCLFUNCTION_VAR_TYPEOF(var), BOOST_TYPEOF(var) &>::value ));
  }
  WG_TEST_LCLFUNCTION_END;

  WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
    WG_LCLFUNCTION_TYPENAME(noop),
    noop);

  noop();
  WG_TEST_LCLFUNCTION_VERIFYCALL(noop);
}

TEST(wg_lclfunction_typeof, VarSetImplicitByConst)
{
  WG_TEST_LCLFUNCTION(noop, varset (const var, 11) )
  {
    WG_TEST_LCLFUNCTION_MARKCALL(noop);

    (void)var;
    EXPECT_TRUE((
      boost::is_same
      <
        WG_LCLFUNCTION_VAR_TYPEOF(var),
        BOOST_TYPEOF(var) const
      >::value ));
  }
  WG_TEST_LCLFUNCTION_END;

  WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
    WG_LCLFUNCTION_TYPENAME(noop),
    noop);

  noop();
  WG_TEST_LCLFUNCTION_VERIFYCALL(noop);
}

TEST(wg_lclfunction_typeof, VarSetImplicitByConstRef)
{
  int var = 11;

  WG_TEST_LCLFUNCTION(noop, varset (const ref var, var) )
  {
    WG_TEST_LCLFUNCTION_MARKCALL(noop);

    (void)var;
    EXPECT_TRUE((
      boost::is_same
      <
        WG_LCLFUNCTION_VAR_TYPEOF(var),
        BOOST_TYPEOF(var) const &
      >::value ));
  }
  WG_TEST_LCLFUNCTION_END;

  WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
    WG_LCLFUNCTION_TYPENAME(noop),
    noop);

  noop();
  WG_TEST_LCLFUNCTION_VERIFYCALL(noop);
}
