#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>

TEST(wg_autofunctor_nested, OneLevel)
{
  try
  {
    int count = 0;

    WG_AUTOFUNCTOR(oneStep, parambind (ref count) )
    {
      ++count;

      WG_AUTOFUNCTOR(twoStep, parambind (ref count) )
      {
        count += 2;
      }
      WG_AUTOFUNCTOR_END;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(count, 3);
  }
  WG_GTEST_CATCH
}

TEST(wg_autofunctor_nested, TwoLevel)
{
  try
  {
    int count = 0;

    WG_AUTOFUNCTOR(oneStep, parambind (ref count) )
    {
      ++count;

      WG_AUTOFUNCTOR(twoStep, parambind (ref count) )
      {
        count += 2;

        WG_AUTOFUNCTOR(threeStep, parambind (ref count) )
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
  WG_GTEST_CATCH
}
