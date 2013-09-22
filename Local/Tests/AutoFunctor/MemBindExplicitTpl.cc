#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>
#include <utility>

namespace
{
typedef float ignored_type;
}

namespace
{
template <typename T>
struct EnsureTypeOfNotUsed
{
  static void run()
  {
    T value = 1.2f;
    WG_AUTOFUNCTOR_TPL(bindByDiffType, membind((int const) value))
    {
      EXPECT_EQ(1, this->value);
    }
    WG_AUTOFUNCTOR_END;
  }
};
}
TEST(wg_autofunctor_membindexplicittpl, EnsureTypeOfNotUsed)
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
    WG_AUTOFUNCTOR_TPL(oneArgAutoFunctor, membind ((bool &) didArgumentBind) )
    {
      this->didArgumentBind = true;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_TRUE(didArgumentBind);
  }
};
}
TEST(wg_autofunctor_membindexplicittpl, OkIf1ArgBound)
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
      membind (ppescape((std::pair<T1, T2> &)) didArgumentBind) )
    {
      this->didArgumentBind = std::make_pair(true, 1);
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_TRUE(didArgumentBind.first);
  }
};
}
TEST(wg_autofunctor_membindexplicittpl, OkIfPPEscaped1ArgBound)
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
      membind ((int &) force) ((int const) mass) ((int const) velocity) )
    {
      this->force = this->mass * this->velocity;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(force, 20);
  }
};
}
TEST(wg_autofunctor_membindexplicittpl, OkIf3ArgsOfVaryingMutabilityBound)
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
  void run()
  {
    didBindThis = false;
    WG_AUTOFUNCTOR_TPL
    (bindThisU,
      membind ((OkIfKeywordThisUBound * const) this_) )
    {
      this_->didBindThis = true;
    }
    WG_AUTOFUNCTOR_END;
    EXPECT_TRUE(didBindThis);
  }

private:
  T didBindThis;
};
}
TEST(wg_autofunctor_membindexplicittpl, OkIfKeywordThisUBound)
{
  try
  {
    OkIfKeywordThisUBound<bool> obj;
    obj.run();
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
      int value;
    } localObj = {10};

    WG_AUTOFUNCTOR_TPL(useLocalKeyword, membind (local(SomeLocalClass) localObj) )
    {
      this->localObj.value += 1;
      EXPECT_EQ(localObj.value, 11);
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(localObj.value, 10);
  }
};
}
TEST(wg_autofunctor_membindexplicittpl, OkIfLocalTypeNoQualBound)
{
  try
  {
    OkIfLocalTypeNoQualBound<ignored_type>::run();
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
      int value;
    } localObj = {0};

    WG_AUTOFUNCTOR_TPL
    (useLocalKeyword, membind (local(SomeLocalClass) ref localObj) )
    {
      this->localObj.value = 10;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(localObj.value, 10);
  }
};
}
TEST(wg_autofunctor_membindexplicittpl, OkIfLocalRefTypeBound)
{
  try
  {
    OkIfLocalRefTypeBound<ignored_type>::run();
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
      int value;
    } localObj = {10};

    WG_AUTOFUNCTOR_TPL
    (useLocalKeyword, membind (local(SomeLocalClass) const localObj) )
    {
      EXPECT_EQ(10, this->localObj.value);
    }
    WG_AUTOFUNCTOR_END;
  }
};
}
TEST(wg_autofunctor_membindexplicittpl, OkIfLocalConstTypeBound)
{
  try
  {
    OkIfLocalConstTypeBound<ignored_type>::run();
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
      int value;
    } localObj = {10};

    WG_AUTOFUNCTOR_TPL
    (useLocalKeyword, membind (local(SomeLocalClass) const ref localObj) )
    {
      EXPECT_EQ(10, this->localObj.value);
    }
    WG_AUTOFUNCTOR_END;
  }
};
}
TEST(wg_autofunctor_membindexplicittpl, OkIfLocalConstRefTypeBound)
{
  try
  {
    OkIfLocalConstRefTypeBound<ignored_type>::run();
  }
  WG_GTEST_CATCH
}
