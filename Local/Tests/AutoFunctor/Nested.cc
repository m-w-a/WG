#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>

TEST(wg_autofunctor, nested)
{
  try
  {
    int count = 0;

    WG_AUTOFUNCTOR(oneStep, \
      parambind ((int &) count) )
    {
      ++count;

      WG_AUTOFUNCTOR(twoStep, \
        parambind ((int &) count) )
      {
        count += 2;
      }WG_AUTOFUNCTOR_END;

    }WG_AUTOFUNCTOR_END;

    EXPECT_EQ(count, 3);
  }
  WG_GTEST_CATCH
}
