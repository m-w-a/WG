#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/Tests/TestHelper.hh>
#include <boost/typeof/typeof.hpp>

namespace
{
template <typename T>
struct EnsureTypeOfNotUsed
{
  static void run()
  {
    WG_AUTOFUNCTOR_TPL(setToDiffType, paramset ((T) value, 1.2f) )
    {
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int, BOOST_TYPEOF_TPL(value));
      EXPECT_EQ(1, value);
    }
    WG_AUTOFUNCTOR_END;
  }
};
}
TEST(wg_autofunctor_paramsetexplicittpl, EnsureTypeOfNotUsed)
{
  try
  {

  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T>
struct OkIf1ArgSet
{
  static void run()
  {
    struct
    {
      T didAssign;
    } proxy = {false};

    WG_AUTOFUNCTOR_TPL
    (oneArgAutoFunctor,
      paramset ((bool &) didAssign, proxy.didAssign) )
    {
      WG_PP_TESTHELPER_IS_SAME_TYPE(bool &, BOOST_TYPEOF_TPL(didAssign) &);
      didAssign = true;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_TRUE(proxy.didAssign);
  }
};
}
TEST(wg_autofunctor_paramsetexplicittpl, OkIf1ArgSet)
{
  try
  {
    OkIf1ArgSet<bool>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T1, typename T2, typename T3>
struct OkIf3ArgsOfVaryingMutabilitySet
{
  static void run()
  {
    struct
    {
      T1 radius;
      T2 height;
      T3 volume;
    } cylinder = {2, 10, -1};

    WG_AUTOFUNCTOR_TPL
    (calculateVolume,
      paramset ((int const) radius, cylinder.radius)
        ((int const) height, cylinder.height)
        ((int &) volume, cylinder.volume) )
    {
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int const, BOOST_TYPEOF_TPL(radius) const);
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int const, BOOST_TYPEOF_TPL(height) const);
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int &, BOOST_TYPEOF_TPL(volume) &);

      volume = radius * height;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(cylinder.radius * cylinder.height, cylinder.volume);
  }
};
}
TEST(wg_autofunctor_paramsetexplicittpl, OkIf3ArgsOfVaryingMutabilitySet)
{
  try
  {
    OkIf3ArgsOfVaryingMutabilitySet<int, int, int>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T>
struct OkIfLocalNoQualTypeSet
{
  static void run()
  {
    struct SomeLocalClass
    {
      T value;
    } localObj = {10};

    WG_AUTOFUNCTOR_TPL
    (useLocalKeyword, paramset (local(SomeLocalClass) obj, localObj) )
    {
      obj.value += 1;
      EXPECT_EQ(obj.value, 11);
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(localObj.value, 10);
  }
};
}
TEST(wg_autofunctor_paramsetexplicittpl, OkIfLocalNoQualTypeSet)
{
  try
  {
    OkIfLocalNoQualTypeSet<int>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T>
struct OkIfLocalRefTypeSet
{
  static void run()
  {
    struct SomeLocalClass
    {
      T value;
    } localObj = {0};

    WG_AUTOFUNCTOR_TPL
    (useLocalKeyword, paramset (local(SomeLocalClass) ref obj, localObj) )
    {
      obj.value = 10;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(localObj.value, 10);
  }
};
}
TEST(wg_autofunctor_paramsetexplicittpl, OkIfLocalRefTypeSet)
{
  try
  {
    OkIfLocalRefTypeSet<int>::run();
  }
  WG_GTEST_CATCH
}
