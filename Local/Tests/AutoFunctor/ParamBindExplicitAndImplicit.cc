#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>

TEST(wg_autofunctor_parambindexplicitandimplicit, \
  OkIf3ArgsOfVaryingMutabilityBound)
{
  try
  {
    int force = 0;
    int const mass = 10;
    int const velocity = 2;

    WG_AUTOFUNCTOR
    (calculateForce, parambind (ref force) ((int const) mass) (velocity) )
    {
      force = mass * velocity;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(force, 20);
  }
  WG_GTEST_CATCH
}

TEST(wg_autofunctor_parambindexplicitandimplicit, \
  OkIfLocalRefKeywordUsed)
{
  try
  {
    struct SomeLocalClass
    {
      int value;
    } localObj = {0};

    int const newValue = 10;

    WG_AUTOFUNCTOR
    (useLocalKeyword,
      parambind (localref(SomeLocalClass &) localObj) (newValue) )
    {
      localObj.value = newValue;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(localObj.value, 10);
  }
  WG_GTEST_CATCH
}
