#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>
#include <boost/tuple/tuple.hpp>
#include <WG/Local/Tests/TestHelper.hh>

namespace
{
template <typename T>
struct OkIf1ArgPassedByValue
{
  static void run()
  {
    T value = 10;

    WG_LCLFUNCTION_TPL(checkValue, params (T value) )
    {
      WG_TESTHELPER_ASSERT_ISNOTCONST_TPL(value);
      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T, value);

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
    WG_LCLFUNCTION_TPL(checkValue, params (T & value) )
    {
      WG_TESTHELPER_ASSERT_ISNOTCONST_TPL(value);
      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T, value);

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
      params (T const & value) )
    {
      WG_TESTHELPER_ASSERT_ISCONST_TPL(value);
      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T, value);

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
template <typename T1>
struct OkIfGloballyScoped1ArgUsed
{
  static void run()
  {
    ::boost::tuple<T1> wasCalled = ::boost::make_tuple(false);

    WG_LCLFUNCTION_TPL
    (checkValue,
      params (::boost::tuple<T1> wasCalled) )
    {
      WG_TESTHELPER_ASSERT_ISNOTCONST_TPL(wasCalled);
      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(
        ::boost::tuple<T1>, wasCalled);

      EXPECT_FALSE(wasCalled.template get<0>());
    }WG_LCLFUNCTION_END;

    checkValue(wasCalled);
  }
};
}
TEST(wg_lclfunction_params_tpl, OkIfGloballyScoped1ArgUsed)
{
  try
  {
    OkIfGloballyScoped1ArgUsed<bool>::run();
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
      params (T1 & force) (T2 const mass) (T3 const velocity) )
    {
      WG_TESTHELPER_ASSERT_ISNOTCONST_TPL(force);
      WG_TESTHELPER_ASSERT_ISCONST_TPL(mass);
      WG_TESTHELPER_ASSERT_ISCONST_TPL(velocity);

      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T1, force);
      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T2, mass);
      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T3, velocity);

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
