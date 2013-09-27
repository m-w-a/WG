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
template <typename T1>
struct OkIfNonLocalExplicit
{
  static void run()
  {
    T1 didAssign = 0;
    WG_AUTOFUNCTOR_TPL(assign, assignto ((bool) didAssign) )
    {
      return true;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_TRUE(didAssign);
  }
};
}
TEST(wg_autofunctor_assigntotpl, OkIfNonLocalExplicit)
{
  try
  {
    OkIfNonLocalExplicit<bool>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T1, typename T2>
struct OkIfNonLocalExplicitPPEscaped
{
  static void run()
  {
    std::pair<T1, T2> didAssign = std::make_pair(false, 0);
    WG_AUTOFUNCTOR_TPL
    (assign,
      assignto (ppescape((std::pair<T1, T2>)) didAssign) )
    {
      return std::make_pair(true, 1);
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_TRUE(didAssign.first);
  }
};
}
TEST(wg_autofunctor_assigntotpl, OkIfNonLocalExplicitPPEscaped)
{
  try
  {
    OkIfNonLocalExplicitPPEscaped<bool, int>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T>
struct OkIfNonLocalImplicit
{
  static void run()
  {
    T didAssign = 0;
    WG_AUTOFUNCTOR_TPL(assign, assignto (didAssign) )
    {
      return true;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_TRUE(didAssign);
  }
};
}
TEST(wg_autofunctor_assigntotpl, OkIfNonLocalImplicit)
{
  try
  {
    OkIfNonLocalImplicit<bool>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T>
struct OkIfLocal
{
  static void run()
  {
    struct SomeLocalType
    {
      int value;
    } obj = {0};

    WG_AUTOFUNCTOR_TPL(assign, assignto (local(SomeLocalType) obj) )
    {
      SomeLocalType toRet = {1};

      return toRet;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(obj.value, 1);
  }
};
}
TEST(wg_autofunctor_assigntotpl, OkIfLocal)
{
  try
  {
    OkIfLocal<ignored_type>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T>
struct OkIfLocalRef
{
  static void run()
  {
    struct SomeLocalType
    {
      int value;
    } obj = {0};

    WG_AUTOFUNCTOR_TPL(assign, assignto (local(SomeLocalType) ref obj) )
    {
      static SomeLocalType toRet = {1};

      return toRet;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(obj.value, 1);
  }
};
}
TEST(wg_autofunctor_assigntotpl, OkIfLocalRef)
{
  try
  {
    OkIfLocalRef<ignored_type>::run();
  }
  WG_GTEST_CATCH
}
