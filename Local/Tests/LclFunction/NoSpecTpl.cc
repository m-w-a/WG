#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/Tests/LclFunction/Utils/TestLclFunction.hh>
#include <WG/Local/Tests/Utils/Utils.hh>

namespace
{
typedef float ignored_type;
bool wasCalled = false;

template <typename T>
struct NoSpec
{
  static void run()
  {
    WG_TEST_LCLFUNCTION_TPL(nospec, void)
    {
      WG_TEST_LCLFUNCTION_MARKCALL(nospec);
      wasCalled = true;
    }WG_TEST_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(
      WG_LCLFUNCTION_TYPENAME(nospec),
      nospec);

    nospec();
    WG_TEST_LCLFUNCTION_VERIFYCALL(nospec);

    EXPECT_TRUE(wasCalled);
  }
};
}

TEST(wg_lclfunction_tpl, NoSpec)
{
  try
  {
    NoSpec<ignored_type>::run();
  }
  WG_GTEST_CATCH
}
