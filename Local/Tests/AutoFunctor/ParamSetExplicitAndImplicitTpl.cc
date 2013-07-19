#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>
#include <boost/typeof/typeof.hpp>
#include <WG/Local/Tests/TestHelper.hh>

namespace
{
template <typename T1, typename T3>
struct OkIf3ArgsOfVaryingMutabilityBound
{
  static void run()
  {
    T1 force = 0;
    int const mass = 10;
    T3 const velocity = 2;

    WG_AUTOFUNCTOR_TPL
    (calculateForce,
      paramset (ref force, force) ((int const) mass, mass) (velocity, velocity) )
    {
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int &, BOOST_TYPEOF_TPL(force) &);
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int const, BOOST_TYPEOF_TPL(mass) const);
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int, BOOST_TYPEOF_TPL(velocity));

      force = mass * velocity;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(force, 20);
  }
};
}
TEST(wg_autofunctor_paramsetexplicitandimplicittpl,
  OkIf3ArgsOfVaryingMutabilityBound)
{
  try
  {
    OkIf3ArgsOfVaryingMutabilityBound<int, int>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T>
struct OkIfLocalRefTypeBound
{
  static void run()
  {
    struct SomeLocalClass
    {
      T value;
    } localObj = {0};

    int const newValue = 10;

    WG_AUTOFUNCTOR_TPL
    (useLocalKeyword,
      paramset (local(SomeLocalClass) ref localObj, localObj) (newValue, newValue) )
    {
      localObj.value = newValue;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(localObj.value, 10);
  }
};
}
TEST(wg_autofunctor_paramsetexplicitandimplicittpl,
  OkIfLocalRefTypeBound)
{
  try
  {
    OkIfLocalRefTypeBound<int>::run();
  }
  WG_GTEST_CATCH
}
