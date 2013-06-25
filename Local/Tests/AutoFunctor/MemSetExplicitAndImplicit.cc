#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>
#include <boost/typeof/typeof.hpp>
#include <WG/Local/Tests/TestHelper.hh>

TEST(wg_autofunctor_memsetexplicitandimplicit,
  OkIf3ArgsOfVaryingMutabilityBound)
{
  try
  {
    int force = 0;
    int const mass = 10;
    int const velocity = 2;

    WG_AUTOFUNCTOR
    (calculateForce,
      memset (ref force, force) ((int const) mass, mass) (velocity, velocity) )
    {
      force = mass * velocity;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(force, 20);
  }
  WG_GTEST_CATCH
}

TEST(wg_autofunctor_memsetexplicitandimplicit,
  OkIfLocalRefTypeBound)
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
      memset (local(SomeLocalClass) ref localObj, localObj) (newValue, newValue) )
    {
      localObj.value = newValue;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(localObj.value, 10);
  }
  WG_GTEST_CATCH
}
