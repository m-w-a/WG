#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>
#include <boost/typeof/typeof.hpp>
#include <WG/Local/Tests/TestHelper.hh>

TEST(wg_autofunctor_paramsetexplicitandimplicit,
  OkIf3ArgsOfVaryingMutabilityBound)
{
  try
  {
    int force = 0;
    int const mass = 10;
    int const velocity = 2;

    WG_AUTOFUNCTOR
    (calculateForce,
      paramset (ref force, force) ((int const) mass, mass) (velocity, velocity) )
    {
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int &, BOOST_TYPEOF(force) &);
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int const, BOOST_TYPEOF(mass) const);
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int, BOOST_TYPEOF(velocity));

      force = mass * velocity;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(force, 20);
  }
  WG_GTEST_CATCH
}

TEST(wg_autofunctor_paramsetexplicitandimplicit,
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
      paramset (local(SomeLocalClass) ref localObj, localObj) (newValue, newValue) )
    {
      localObj.value = newValue;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(localObj.value, 10);
  }
  WG_GTEST_CATCH
}
