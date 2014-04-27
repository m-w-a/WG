#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclClass.hh>

namespace
{
template <typename T>
struct IsCalled
{
  static void run()
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
};
}
TEST(wg_lclclass_inithook_tpl, IsCalled)
{
  try
  {
    IsCalled<int>::run();
  }
  WG_GTEST_CATCH
}
