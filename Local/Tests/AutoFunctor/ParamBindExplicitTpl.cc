#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>
#include <boost/typeof/typeof.hpp>
#include <WG/Local/Tests/TestHelper.hh>
#include <utility>
#include <boost/utility/identity_type.hpp>

namespace
{
template <typename T>
struct EnsureTypeOfNotUsed
{
  static void run()
  {
    T value = 1.2f;
    WG_AUTOFUNCTOR_TPL(bindByDiffType, parambind ((int const) value) )
    {
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int const, BOOST_TYPEOF_TPL(value) const);
      EXPECT_EQ(1, value);
    }
    WG_AUTOFUNCTOR_END;
  }
};
}
TEST(wg_autofunctor_parambindexplicittpl, EnsureTypeOfNotUsed)
{
  try
  {
    EnsureTypeOfNotUsed<float>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T>
struct OkIf1ArgBound
{
  static void run()
  {
    T didArgumentBind = false;

    WG_AUTOFUNCTOR_TPL(oneArgAutoFunctor, parambind ((bool &) didArgumentBind) )
    {
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        bool &, BOOST_TYPEOF_TPL(didArgumentBind) &);

      didArgumentBind = true;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_TRUE(didArgumentBind);
  }
};
}
TEST(wg_autofunctor_parambindexplicittpl, OkIf1ArgBound)
{
  try
  {
    OkIf1ArgBound<bool>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T1, typename T2>
struct OkIfPPEscaped1ArgBound
{
  static void run()
  {
    std::pair<T1, T2> didArgumentBind = std::make_pair(false, 0);

    WG_AUTOFUNCTOR_TPL
    (oneArgAutoFunctor,
      parambind (ppescape((std::pair<bool, int> &)) didArgumentBind) )
    {
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        typename BOOST_IDENTITY_TYPE((std::pair<bool, int> &)),
        BOOST_TYPEOF_TPL(didArgumentBind) &);

      didArgumentBind.first = true;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_TRUE(didArgumentBind.first);
  }
};
}
TEST(wg_autofunctor_parambindexplicittpl, OkIfPPEscaped1ArgBound)
{
  try
  {
    OkIfPPEscaped1ArgBound<bool, int>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T1, typename T2, typename T3>
struct OkIf3ArgsOfVaryingMutabilityBound
{
  static void run()
  {
    T1 force = 0;
    T2 const mass = 10;
    T3 const velocity = 2;

    WG_AUTOFUNCTOR_TPL
    (calculateForce,
      parambind ((int &) force) ((int const) mass) ((int const) velocity) )
    {
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int &, BOOST_TYPEOF_TPL(force) &);
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int const, BOOST_TYPEOF_TPL(mass) const);
      WG_PP_TESTHELPER_IS_SAME_TYPE(
        int const, BOOST_TYPEOF_TPL(velocity) const);

      force = mass * velocity;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(force, 20);
  }
};
}
TEST(wg_autofunctor_parambindexplicittpl, OkIf3ArgsOfVaryingMutabilityBound)
{
  try
  {
    OkIf3ArgsOfVaryingMutabilityBound<int, int, int>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T>
struct OkIfKeywordThisUBound
{
  OkIfKeywordThisUBound()
  : didBindThis(false)
  {
    WG_AUTOFUNCTOR_TPL
    (bindThisU,
      parambind ((OkIfKeywordThisUBound * const) this_) )
    {
      this_->didBindThis = true;
    }
    WG_AUTOFUNCTOR_END;
  }

  T didBindThis;
};
}
TEST(wg_autofunctor_parambindexplicittpl, OkIfKeywordThisUBound)
{
  try
  {
    OkIfKeywordThisUBound<bool> obj;
    EXPECT_TRUE(obj.didBindThis);
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T>
struct OkIfLocalTypeNoQualBound
{
  static void run()
  {
    struct SomeLocalClass
    {
      T value;
    } localObj = {10};

    WG_AUTOFUNCTOR_TPL
    (useLocalKeyword, parambind (local(SomeLocalClass) localObj) )
    {
      localObj.value += 1;
      EXPECT_EQ(localObj.value, 11);
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(localObj.value, 10);
  }
};
}
TEST(wg_autofunctor_parambindexplicittpl, OkIfLocalTypeNoQualBound)
{
  try
  {
    OkIfLocalTypeNoQualBound<int>::run();
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

    WG_AUTOFUNCTOR_TPL
    (useLocalKeyword, parambind (local(SomeLocalClass) ref localObj) )
    {
      localObj.value = 10;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(localObj.value, 10);
  }
};
}
TEST(wg_autofunctor_parambindexplicittpl, OkIfLocalRefTypeBound)
{
  try
  {
    OkIfLocalRefTypeBound<int>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T>
struct OkIfLocalConstTypeBound
{
  static void run()
  {
    struct SomeLocalClass
    {
      T value;
    } localObj = {10};

    WG_AUTOFUNCTOR_TPL
    (useLocalKeyword, parambind (local(SomeLocalClass) const localObj) )
    {
      EXPECT_EQ(10, localObj.value);
    }
    WG_AUTOFUNCTOR_END;
  }
};
}
TEST(wg_autofunctor_parambindexplicittpl, OkIfLocalConstTypeBound)
{
  try
  {
    OkIfLocalConstTypeBound<int>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T>
struct OkIfLocalConstRefTypeBound
{
  static void run()
  {
    struct SomeLocalClass
    {
      T value;
    } localObj = {10};

    WG_AUTOFUNCTOR_TPL
    (useLocalKeyword, parambind (local(SomeLocalClass) const ref localObj) )
    {
      EXPECT_EQ(10, localObj.value);
    }
    WG_AUTOFUNCTOR_END;
  }
};
}
TEST(wg_autofunctor_parambindexplicittpl, OkIfLocalConstRefTypeBound)
{
  try
  {
    OkIfLocalConstRefTypeBound<int>::run();
  }
  WG_GTEST_CATCH
}
