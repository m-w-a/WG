#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>

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
    (calculateForce, membind (ref force) ((int const) mass) (velocity) )
    {
      this->force = this->mass * this->velocity;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(force, 20);
  }
};
}
TEST(wg_autofunctor_membindexplicitandimplicittpl,
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
      membind (local(SomeLocalClass) ref localObj) (newValue) )
    {
      this->localObj.value = this->newValue;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(localObj.value, 10);
  }
};
}
TEST(wg_autofunctor_membindexplicitandimplicittpl,
  OkIfLocalRefTypeBound)
{
  try
  {
    OkIfLocalRefTypeBound<int>::run();
  }
  WG_GTEST_CATCH
}
