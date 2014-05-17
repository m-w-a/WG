#include <gtest/gtest.h>
#include <WG/Local/LclClass.hh>

TEST(wg_lclclass_nested, TwoLevels)
{
  long var = 1;

  WG_LCLCLASS(Level1, memext (ref var) )
    WG_LCLCLASS(Level2, memext (ref var) )
      void init() { ++var; }
    WG_LCLCLASS_END;

    void init() { ++var; Level2 l(var); }
  WG_LCLCLASS_END;

  Level1 l(var);

  EXPECT_EQ(3, var);
}
