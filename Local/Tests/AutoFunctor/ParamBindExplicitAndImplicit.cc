#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>
#include <boost/typeof/typeof.hpp>
#include <WG/Local/Tests/Utils/Utils.hh>

TEST(wg_autofunctor_parambindexplicitandimplicit,
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
      WG_PP_TEST_IS_SAME_TYPE(
        int &, BOOST_TYPEOF(force) &);
      WG_PP_TEST_IS_SAME_TYPE(
        int const, BOOST_TYPEOF(mass) const);
      WG_PP_TEST_IS_SAME_TYPE(
        int, BOOST_TYPEOF(velocity));

      force = mass * velocity;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(force, 20);
  }
  WG_GTEST_CATCH
}

TEST(wg_autofunctor_parambindexplicitandimplicit,
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
      parambind (local(SomeLocalClass) ref localObj) (newValue) )
    {
      localObj.value = newValue;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(localObj.value, 10);
  }
  WG_GTEST_CATCH
}
