#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>

namespace
{
template <typename T1>
struct OkIfNonLocalExplicit
{
  static void run()
  {
    T1 didAssign = 0;
    WG_AUTOFUNCTOR(assign, assignto ((bool) didAssign) )
    {
      return true;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_TRUE(didAssign);
  }
};
}
TEST(wg_autofunctor_assigntotpl, OkIfNonLocalExplicit)
{
  try
  {
    OkIfNonLocalExplicit<bool>::run();
  }
  WG_GTEST_CATCH
}
