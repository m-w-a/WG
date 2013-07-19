#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>
#include <boost/typeof/typeof.hpp>
#include <WG/Local/Tests/TestHelper.hh>

TEST(wg_autofunctor_parambindexplicit, EnsureTypeOfNotUsed)
{
  try
  {
    float value = 1.2f;

    WG_AUTOFUNCTOR(bindByDiffType, parambind ((int const) value) )
    {
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int const, BOOST_TYPEOF(value) const);
      EXPECT_EQ(1, value);
    }
    WG_AUTOFUNCTOR_END;
  }
  WG_GTEST_CATCH
}

TEST(wg_autofunctor_parambindexplicit, OkIf1ArgBound)
{
  try
  {
    bool didArgumentBind = false;

    WG_AUTOFUNCTOR(oneArgAutoFunctor, parambind ((bool &) didArgumentBind) )
    {
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        bool &, BOOST_TYPEOF(didArgumentBind) &);

      didArgumentBind = true;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_TRUE(didArgumentBind);
  }
  WG_GTEST_CATCH
}

TEST(wg_autofunctor_parambindexplicit, OkIf3ArgsOfVaryingMutabilityBound)
{
  try
  {
    int force = 0;
    int const mass = 10;
    int const velocity = 2;

    WG_AUTOFUNCTOR
    (calculateForce,
      parambind ((int &) force) ((int const) mass) ((int const) velocity) )
    {
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int &, BOOST_TYPEOF(force) &);
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int const, BOOST_TYPEOF(mass) const);
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int const, BOOST_TYPEOF(velocity) const);

      force = mass * velocity;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(force, 20);
  }
  WG_GTEST_CATCH
}

TEST(wg_autofunctor_parambindexplicit, OkIfKeywordThisUBound)
{
  try
  {
    struct SomeLocalClass
    {
      bool didBindThis;

      SomeLocalClass()
      : didBindThis(false)
      {
        WG_AUTOFUNCTOR
        (bindThisU,
          parambind (local(SomeLocalClass *) const this_) )
        {
          this_->didBindThis = true;
        }
        WG_AUTOFUNCTOR_END;
      }
    } someLocalObj;

    EXPECT_TRUE(someLocalObj.didBindThis);
  }
  WG_GTEST_CATCH
}

TEST(wg_autofunctor_parambindexplicit, OkIfLocalTypeNoQualBound)
{
  try
  {
    struct SomeLocalClass
    {
      int value;
    } localObj = {10};

    static int newValue;
    newValue = 0;
    WG_AUTOFUNCTOR(useLocalKeyword, parambind (local(SomeLocalClass) localObj) )
    {
      localObj.value += 1;
      newValue = localObj.value;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(localObj.value, 10);
    EXPECT_EQ(newValue, 11);
  }
  WG_GTEST_CATCH
}

TEST(wg_autofunctor_parambindexplicit, OkIfLocalRefTypeBound)
{
  try
  {
    struct SomeLocalClass
    {
      int value;
    } localObj = {0};

    WG_AUTOFUNCTOR
    (useLocalKeyword, parambind (local(SomeLocalClass) ref localObj) )
    {
      localObj.value = 10;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(localObj.value, 10);
  }
  WG_GTEST_CATCH
}

TEST(wg_autofunctor_parambindexplicit, OkIfLocalConstTypeBound)
{
  try
  {
    struct SomeLocalClass
    {
      int value;
    } localObj = {10};

    static bool didLocalObjBind;
    didLocalObjBind = false;
    WG_AUTOFUNCTOR
    (useLocalKeyword, parambind (local(SomeLocalClass) const localObj) )
    {
      didLocalObjBind = (localObj.value == 10);
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_TRUE(didLocalObjBind);
  }
  WG_GTEST_CATCH
}

TEST(wg_autofunctor_parambindexplicit, OkIfLocalConstRefTypeBound)
{
  try
  {
    struct SomeLocalClass
    {
      int value;
    } localObj = {10};

    static bool didLocalObjBind;
    didLocalObjBind = false;
    WG_AUTOFUNCTOR
    (useLocalKeyword, parambind (local(SomeLocalClass) const ref localObj) )
    {
      didLocalObjBind = (localObj.value == 10);
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_TRUE(didLocalObjBind);
  }
  WG_GTEST_CATCH
}
