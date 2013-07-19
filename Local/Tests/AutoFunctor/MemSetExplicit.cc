#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>

TEST(wg_autofunctor_memsetexplicit, EnsureTypeOfNotUsed)
{
  try
  {
    WG_AUTOFUNCTOR(setToDiffType, memset ((int) value, 1.2f) )
    {
      EXPECT_EQ(1, this->value);
    }
    WG_AUTOFUNCTOR_END;
  }
  WG_GTEST_CATCH
}

TEST(wg_autofunctor_memsetexplicit, OkIf1ArgSet)
{
  try
  {
    struct
    {
      bool didAssign;
    } proxy = {false};

    WG_AUTOFUNCTOR
    (oneArgAutoFunctor,
      memset ((bool &) didAssign, proxy.didAssign) )
    {
      this->didAssign = true;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_TRUE(proxy.didAssign);
  }
  WG_GTEST_CATCH
}

TEST(wg_autofunctor_memsetexplicit, OkIf3ArgsOfVaryingMutabilitySet)
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
      memset ((int const) radius, cylinder.radius)
        ((int const) height, cylinder.height)
        ((int &) volume, cylinder.volume) )
    {
      this->volume = this->radius * this->height;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(cylinder.radius * cylinder.height, cylinder.volume);
  }
  WG_GTEST_CATCH
}

TEST(wg_autofunctor_memsetexplicit, OkIfLocalNoQualTypeSet)
{
  try
  {
    struct SomeLocalClass
    {
      int value;
    } localObj = {10};

    static int newValue = 0;
    WG_AUTOFUNCTOR
    (useLocalKeyword, memset (local(SomeLocalClass) obj, localObj) )
    {
      this->obj.value += 1;
      newValue = this->obj.value;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(localObj.value, 10);
    EXPECT_EQ(newValue, 11);
  }
  WG_GTEST_CATCH
}

TEST(wg_autofunctor_memsetexplicit, OkIfLocalRefTypeSet)
{
  try
  {
    struct SomeLocalClass
    {
      int value;
    } localObj = {0};

    WG_AUTOFUNCTOR
    (useLocalKeyword, memset (local(SomeLocalClass) ref obj, localObj) )
    {
      this->obj.value = 10;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(localObj.value, 10);
  }
  WG_GTEST_CATCH
}
