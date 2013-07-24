#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>

TEST(wg_autofunctor_selftype, TwoLevel)
{
  try
  {
    int count = 0;

    WG_AUTOFUNCTOR(oneStep, membind (ref count) )
    {
      ++count;

      WG_AUTOFUNCTOR
      (twoStep,
        memset (local(WG_AUTOFUNCTOR_TYPE(oneStep) *) const parent, this) )
      {
        parent->count += 2;

        WG_AUTOFUNCTOR
        (threeStep,
          memset (local(WG_AUTOFUNCTOR_TYPE(twoStep) *) const parent, this) )
        {
          parent->parent->count += 3;
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
