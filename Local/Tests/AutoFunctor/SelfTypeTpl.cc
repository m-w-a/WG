#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>

namespace
{
template <typename T>
struct TwoLevel
{
  static void run()
  {
    T count = 0;

    WG_AUTOFUNCTOR_TPL(oneStep, membind (ref count) )
    {
      ++count;

      WG_AUTOFUNCTOR_TPL
      (twoStep,
        memset (local(WG_AUTOFUNCTOR_TYPE(oneStep) *) const parent, this) )
      {
        parent->count += 2;

        WG_AUTOFUNCTOR_TPL
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
};
}
TEST(wg_autofunctor_selftypetpl, TwoLevel)
{
  try
  {
    TwoLevel<int>::run();
  }
  WG_GTEST_CATCH
}
