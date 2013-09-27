#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>

TEST(wg_lclfunction_nested, OneLevel)
{
  try
  {
    int count = 0;

    WG_LCLFUNCTION(oneStep, varbind (ref count) )
    {
      ++count;

      WG_LCLFUNCTION(twoStep, varbind (ref count) )
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
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_nested, TwoLevel)
{
  try
  {
    int count = 0;

    WG_LCLFUNCTION(oneStep, varbind (ref count) )
    {
      ++count;

      WG_LCLFUNCTION(twoStep, params ((int &) count) )
      {
        count += 2;

        WG_LCLFUNCTION(threeStep, varset (ref var, count) )
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
  WG_GTEST_CATCH
}
