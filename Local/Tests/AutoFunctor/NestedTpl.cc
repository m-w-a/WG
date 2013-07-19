#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>

namespace
{
template <typename T>
struct OneLevel
{
  static void run()
  {
    T count = 0;

    WG_AUTOFUNCTOR_TPL(oneStep, parambind (ref count) )
    {
      ++count;

      WG_AUTOFUNCTOR_TPL(twoStep, parambind (ref count) )
      {
        count += 2;
      }
      WG_AUTOFUNCTOR_END;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(count, 3);
  }
};
}
TEST(wg_autofunctor_nestedtpl, OneLevel)
{
  try
  {
    OneLevel<int>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T>
struct TwoLevel
{
  static void run()
  {
    T count = 0;

    WG_AUTOFUNCTOR_TPL(oneStep, parambind (ref count) )
    {
      ++count;

      WG_AUTOFUNCTOR_TPL(twoStep, parambind (ref count) )
      {
        count += 2;

        WG_AUTOFUNCTOR_TPL(threeStep, parambind (ref count) )
        {
          count += 3;
        }
        WG_AUTOFUNCTOR_END;
      }
      WG_AUTOFUNCTOR_END;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(count, 6);
  }
};
}
TEST(wg_autofunctor_nestedtpl, TwoLevel)
{
  try
  {
    TwoLevel<int>::run();
  }
  WG_GTEST_CATCH
}
