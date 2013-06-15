#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>

TEST(wg_autofunctor_paramsetexplicit, OkIf1ArgSet)
{
  try
  {
    struct
    {
      bool didAssign;
    } proxy = {false};

    WG_AUTOFUNCTOR
    (oneArgAutoFunctor,
      paramset ((bool &) didAssign, proxy.didAssign) )
    {
      didAssign = true;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_TRUE(proxy.didAssign);
  }
  WG_GTEST_CATCH
}

TEST(wg_autofunctor_paramsetexplicit, OkIf3ArgsOfVaryingMutabilitySet)
{
  try
  {
    struct
    {
      int radius;
      int height;
      int volume;
    } cylinder = {2, 10, -1};

    WG_AUTOFUNCTOR
    (calculateVolume,
      paramset ((int const) radius, cylinder.radius)
        ((int const) height, cylinder.height)
        ((int &) volume, cylinder.volume) )
    {
      volume = radius * height;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(cylinder.radius * cylinder.height, cylinder.volume);
  }
  WG_GTEST_CATCH
}

TEST(wg_autofunctor_paramsetexplicit, OkIfLocalTypeSet)
{
  try
  {
    struct SomeLocalClass
    {
      int value;
    } localObj = {10};

    static int newValue = 0;
    WG_AUTOFUNCTOR
    (useLocalKeyword, paramset (local(SomeLocalClass) obj, localObj) )
    {
      obj.value += 1;
      newValue = obj.value;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(localObj.value, 10);
    EXPECT_EQ(newValue, 11);
  }
  WG_GTEST_CATCH
}

TEST(wg_autofunctor_paramsetexplicit, OkIfLocalRefTypeSet)
{
  try
  {
    struct SomeLocalClass
    {
      int value;
    } localObj = {0};

    WG_AUTOFUNCTOR
    (useLocalKeyword, paramset (local(SomeLocalClass) ref obj, localObj) )
    {
      obj.value = 10;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(localObj.value, 10);
  }
  WG_GTEST_CATCH
}
