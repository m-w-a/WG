#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/Tests/LclFunction/Utils/TestLclFunction.hh>
#include <boost/type_traits/is_same.hpp>
#include <WG/Local/Tests/Utils/Utils.hh>

//---------------
//VarBindExplicit
//---------------

TEST(wg_lclfunction_typeof, VarBindExplicitByValue)
{
  try
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
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_typeof, VarBindExplicitByRef)
{
  try
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
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_typeof, VarBindExplicitByConst)
{
  try
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
  WG_GTEST_CATCH
}

//---------------
//VarBindImplicit
//---------------

TEST(wg_lclfunction_typeof, VarBindImplicitByValue)
{
  try
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
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_typeof, VarBindImplicitByRef)
{
  try
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
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_typeof, VarBindImplicitByConst)
{
  try
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
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_typeof, VarBindImplicitByConstRef)
{
  try
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
  WG_GTEST_CATCH
}

//---------------
//VarSetExplicit
//---------------

TEST(wg_lclfunction_typeof, VarSetExplicitByValue)
{
  try
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
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_typeof, VarSetExplicitByRef)
{
  try
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
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_typeof, VarSetExplicitByConst)
{
  try
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
  WG_GTEST_CATCH
}

//--------------
//VarSetImplicit
//--------------

TEST(wg_lclfunction_typeof, VarSetImplicitByValue)
{
  try
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
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_typeof, VarSetImplicitByRef)
{
  try
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
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_typeof, VarSetImplicitByConst)
{
  try
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
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_typeof, VarSetImplicitByConstRef)
{
  try
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
  WG_GTEST_CATCH
}
