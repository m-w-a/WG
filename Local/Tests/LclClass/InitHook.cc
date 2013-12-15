#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclClass.hh>

TEST(wg_lclclass_inithook, IsCalled)
{
  try
  {
    int var = 0;
    WG_LCLCLASS(Local, memdecl((int &) var) )
      void init()
      {
        ++var;
      }
    WG_LCLCLASS_END;

    Local l(var);

    EXPECT_EQ(1, var);
  }
  WG_GTEST_CATCH
}
