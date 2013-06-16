#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>

TEST(wg_autofunctor_parambindexplicit, OkIf1ArgBound)
{
  try
  {
    bool didArgumentBind = false;

    WG_AUTOFUNCTOR(oneArgAutoFunctor, parambind ((bool &)didArgumentBind) )
    {
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

TEST(wg_autofunctor_parambindexplicit, OkIfLocalTypeBound)
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
