#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>
#include <boost/tuple/tuple.hpp>

namespace
{
template <typename T>
struct EnsureTypeOfNotUsed
{
  static void run()
  {
    WG_AUTOFUNCTOR_TPL(setToDiffType, memset ((T) value, 1.2f) )
    {
      EXPECT_EQ(1, this->value);
    }
    WG_AUTOFUNCTOR_END;
  }
};
}
TEST(wg_autofunctor_memsetexplicittpl, EnsureTypeOfNotUsed)
{
  try
  {
    EnsureTypeOfNotUsed<int>::run();
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
      memset ((T &) didAssign, proxy.didAssign) )
    {
      this->didAssign = true;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_TRUE(proxy.didAssign);
  }
};
}
TEST(wg_autofunctor_memsetexplicittpl, OkIf1ArgSet)
{
  try
  {
    OkIf1ArgSet<bool>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T1>
struct OkIfGloballyScoped1ArgSet
{
  static void run()
  {
    ::boost::tuple<T1> didAssign = ::boost::make_tuple(false);

    WG_AUTOFUNCTOR_TPL
    (oneArgAutoFunctor,
      memset ((::boost::tuple<bool> &) assigner, didAssign) )
    {
      this->assigner.template get<0>() = true;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_TRUE(didAssign.template get<0>());
  }
};
}
TEST(wg_autofunctor_memsetexplicittpl, OkIfGloballyScoped1ArgSet)
{
  try
  {
    OkIfGloballyScoped1ArgSet<bool>::run();
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
      memset ((T1 const) radius, cylinder.radius)
        ((T2 const) height, cylinder.height)
        ((T3 &) volume, cylinder.volume) )
    {
      this->volume = this->radius * this->height;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(cylinder.radius * cylinder.height, cylinder.volume);
  }
};
}
TEST(wg_autofunctor_memsetexplicittpl, OkIf3ArgsOfVaryingMutabilitySet)
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
    (useLocalKeyword, memset (local(SomeLocalClass) obj, localObj) )
    {
      this->obj.value += 1;
      EXPECT_EQ(this->obj.value, 11);
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(localObj.value, 10);
  }
};
}
TEST(wg_autofunctor_memsetexplicittpl, OkIfLocalNoQualTypeSet)
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
    (useLocalKeyword, memset (local(SomeLocalClass) ref obj, localObj) )
    {
      this->obj.value = 10;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(localObj.value, 10);
  }
};
}
TEST(wg_autofunctor_memsetexplicittpl, OkIfLocalRefTypeSet)
{
  try
  {
    OkIfLocalRefTypeSet<int>::run();
  }
  WG_GTEST_CATCH
}
