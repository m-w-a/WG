#include <gtest/gtest.h>
#include <WG/Local/LclClass.hh>

TEST(wg_lclclass_inithook, IsCalled)
{
  int var = 0;
  WG_LCLCLASS(Local, memext (type(int &) var) )
    void init()
    {
      ++var;
    }
  WG_LCLCLASS_END;

  Local l(var);

  EXPECT_EQ(1, var);
}
