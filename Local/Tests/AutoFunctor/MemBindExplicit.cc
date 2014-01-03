#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>
#include <boost/tuple/tuple.hpp>

TEST(wg_autofunctor_membindexplicit, EnsureTypeOfNotUsed)
{
  try
  {
    float value = 1.2f;

    WG_AUTOFUNCTOR(bindByDiffType, membind((int const) value))
    {
      EXPECT_EQ(1, this->value);
    }
    WG_AUTOFUNCTOR_END;
  }
  WG_GTEST_CATCH
}

TEST(wg_autofunctor_membindexplicit, OkIf1ArgBound)
{
  try
  {
    bool didArgumentBind = false;

    WG_AUTOFUNCTOR(oneArgAutoFunctor, membind ((bool &) didArgumentBind) )
    {
      this->didArgumentBind = true;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_TRUE(didArgumentBind);
  }
  WG_GTEST_CATCH
}

TEST(wg_autofunctor_membindexplicit, OkIfGloballyScoped1ArgBound)
{
  try
  {
    ::boost::tuple<bool> didArgumentBind = ::boost::make_tuple(false);

    WG_AUTOFUNCTOR
    (oneArgAutoFunctor,
      membind ((::boost::tuple<bool> &) didArgumentBind) )
    {
      this->didArgumentBind = ::boost::make_tuple(true);
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_TRUE(didArgumentBind.get<0>());
  }
  WG_GTEST_CATCH
}

TEST(wg_autofunctor_membindexplicit, OkIf3ArgsOfVaryingMutabilityBound)
{
  try
  {
    int force = 0;
    int const mass = 10;
    int const velocity = 2;

    WG_AUTOFUNCTOR
    (calculateForce,
      membind ((int &) force) ((int const) mass) ((int const) velocity) )
    {
      this->force = this->mass * this->velocity;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(force, 20);
  }
  WG_GTEST_CATCH
}

TEST(wg_autofunctor_membindexplicit, OkIfKeywordThisUBound)
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
          membind (local(SomeLocalClass *) const this_) )
        {
          this->this_->didBindThis = true;
        }
        WG_AUTOFUNCTOR_END;
      }
    } someLocalObj;

    EXPECT_TRUE(someLocalObj.didBindThis);
  }
  WG_GTEST_CATCH
}

TEST(wg_autofunctor_membindexplicit, OkIfLocalTypeNoQualBound)
{
  try
  {
    struct SomeLocalClass
    {
      int value;
    } localObj = {10};

    static int newValue;
    newValue = 0;
    WG_AUTOFUNCTOR(useLocalKeyword, membind (local(SomeLocalClass) localObj) )
    {
      this->localObj.value += 1;
      newValue = localObj.value;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(localObj.value, 10);
    EXPECT_EQ(newValue, 11);
  }
  WG_GTEST_CATCH
}

TEST(wg_autofunctor_membindexplicit, OkIfLocalRefTypeBound)
{
  try
  {
    struct SomeLocalClass
    {
      int value;
    } localObj = {0};

    WG_AUTOFUNCTOR
    (useLocalKeyword, membind (local(SomeLocalClass) ref localObj) )
    {
      this->localObj.value = 10;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(localObj.value, 10);
  }
  WG_GTEST_CATCH
}

TEST(wg_autofunctor_membindexplicit, OkIfLocalConstTypeBound)
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
    (useLocalKeyword, membind (local(SomeLocalClass) const localObj) )
    {
      didLocalObjBind = (this->localObj.value == 10);
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_TRUE(didLocalObjBind);
  }
  WG_GTEST_CATCH
}

TEST(wg_autofunctor_membindexplicit, OkIfLocalConstRefTypeBound)
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
    (useLocalKeyword, membind (local(SomeLocalClass) const ref localObj) )
    {
      didLocalObjBind = (this->localObj.value == 10);
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_TRUE(didLocalObjBind);
  }
  WG_GTEST_CATCH
}
