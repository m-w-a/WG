#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclClass.hh>

namespace
{
template <typename T>
struct TwoLevels
{
  static void run()
  {
    T var = 1;

    WG_LCLCLASS_TPL(Level1, memext (ref var) )
      WG_LCLCLASS_TPL(Level2, memext (ref var) )
        void init() { ++var; }
      WG_LCLCLASS_END;

      void init() { ++var; Level2 l(var); }
    WG_LCLCLASS_END;

    Level1 l(var);

    EXPECT_EQ(3, var);
  }
};
}
TEST(wg_lclclass_nested_tpl, TwoLevels)
{
  try
  {
    TwoLevels<long>::run();
  }
  WG_GTEST_CATCH
}
