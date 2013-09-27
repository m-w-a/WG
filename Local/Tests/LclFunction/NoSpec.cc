#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>

TEST(wg_lclfunction, NoSpec)
{
  try
  {
    static bool wasCalled = false;
    WG_LCLFUNCTION(nospec, void)
    {
      wasCalled = true;
    }WG_LCLFUNCTION_END;

    nospec();

    EXPECT_TRUE(wasCalled);
  }
  WG_GTEST_CATCH
}
