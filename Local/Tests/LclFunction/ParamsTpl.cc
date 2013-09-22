#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>
#include <utility>

namespace
{
template <typename T>
struct OkIf1ArgPassedByValue
{
  static void run()
  {
    T value = 10;

    WG_LCLFUNCTION_TPL(checkValue, params ((int) value) )
    {
      ++value;
      EXPECT_EQ(11, value);
    }WG_LCLFUNCTION_END;

    checkValue(value);

    EXPECT_EQ(10, value);
  }
};
}
TEST(wg_lclfunction_params_tpl, OkIf1ArgPassedByValue)
{
  try
  {
    OkIf1ArgPassedByValue<int>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T>
struct OkIf1ArgPassedByRef
{
  static void run()
  {
    T value = 10;
    WG_LCLFUNCTION_TPL(checkValue, params ((T &) value) )
    {
      ++value;
      EXPECT_EQ(11, value);
    }WG_LCLFUNCTION_END;

    checkValue(value);

    EXPECT_EQ(11, value);
  }
};
}
TEST(wg_lclfunction_params_tpl, OkIf1ArgPassedByRef)
{
  try
  {
    OkIf1ArgPassedByRef<int>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T>
struct OkIf1ArgPassedByConstRef
{
  static void run()
  {
    T value = 10;
    WG_LCLFUNCTION_TPL
    (checkValue,
      params ((T const &) value) )
    {
      EXPECT_EQ(10, value);
    }WG_LCLFUNCTION_END;

    checkValue(value);
  }
};
}
TEST(wg_lclfunction_params_tpl, OkIf1ArgPassedByConstRef)
{
  try
  {
    OkIf1ArgPassedByConstRef<int>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T1, typename T2>
struct OkIfPPEscaped1ArgUsed
{
  static void run()
  {
    std::pair<T1, T2> wasCalled = std::make_pair(false, 0);

    WG_LCLFUNCTION_TPL
    (checkValue,
      params (ppescape((std::pair<T1,T2>)) wasCalled) )
    {
      EXPECT_FALSE(wasCalled.first);
      EXPECT_EQ(0, wasCalled.second);
    }WG_LCLFUNCTION_END;

    checkValue(wasCalled);
  }
};
}
TEST(wg_lclfunction_params_tpl, OkIfPPEscaped1ArgUsed)
{
  try
  {
    OkIfPPEscaped1ArgUsed<bool, int>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T1, typename T2, typename T3>
struct OkIf3ArgsUsed
{
  static void run()
  {
    T1 force = 0;
    T2 const mass = 10;
    T3 const velocity = 2;

    WG_LCLFUNCTION_TPL
    (calculateForce,
      params ((T1 &) force) ((T2 const) mass) ((T3 const) velocity) )
    {
      force = mass * velocity;
    }WG_LCLFUNCTION_END;

    calculateForce(force, mass, velocity);

    EXPECT_EQ(20, force);
  }
};
}
TEST(wg_lclfunction_params_tpl, OkIf3ArgsUsed)
{
  try
  {
    OkIf3ArgsUsed<int, int, int>::run();
  }
  WG_GTEST_CATCH
}
