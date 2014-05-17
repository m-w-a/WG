#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/Tests/LclFunction/Utils/TestLclFunction.hh>
#include <WG/Local/Tests/Utils/Utils.hh>

TEST(wg_lclfunction, NoSpec)
{
  try
  {
    static bool wasCalled = false;
    WG_TEST_LCLFUNCTION(nospec, void)
    {
      WG_TEST_LCLFUNCTION_MARKCALL(nospec);
      wasCalled = true;
    }WG_TEST_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
      WG_LCLFUNCTION_TYPENAME(nospec),
      nospec);

    nospec();
    WG_TEST_LCLFUNCTION_VERIFYCALL(nospec);

    EXPECT_TRUE(wasCalled);
  }
  WG_GTEST_CATCH
}
