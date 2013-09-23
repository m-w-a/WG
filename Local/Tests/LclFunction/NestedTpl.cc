#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>

namespace
{
template <typename T>
struct OneLevel
{
  static void run()
  {
    T count = 0;

    WG_LCLFUNCTION_TPL(oneStep, varbind (ref count) )
    {
      ++count;

      WG_LCLFUNCTION_TPL(twoStep, varbind (ref count) )
      {
        count += 2;
      }
      WG_LCLFUNCTION_END;

      twoStep();
    }
    WG_LCLFUNCTION_END;

    oneStep();

    EXPECT_EQ(count, 3);
  }
};
}
TEST(wg_lclfunction_nested_tpl, OneLevel)
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

    WG_LCLFUNCTION_TPL(oneStep, varbind (ref count) )
    {
      ++count;

      WG_LCLFUNCTION_TPL(twoStep, params ((int &) count) )
      {
        count += 2;

        WG_LCLFUNCTION_TPL(threeStep, varset (ref var, count) )
        {
          var += 3;
        }
        WG_LCLFUNCTION_END;

        threeStep();
      }
      WG_LCLFUNCTION_END;

      twoStep(count);
    }
    WG_LCLFUNCTION_END;

    oneStep();

    EXPECT_EQ(count, 6);
  }
};
}
TEST(wg_lclfunction_nested_tpl, TwoLevel)
{
  try
  {
    TwoLevel<int>::run();
  }
  WG_GTEST_CATCH
}
