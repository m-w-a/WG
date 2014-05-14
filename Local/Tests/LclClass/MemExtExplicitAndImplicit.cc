#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/Tests/Utils/Utils.hh>
#include <WG/Local/LclClass.hh>

TEST(wg_lclclass_memextexplicitandimplicit, OkIf3MemOfVaryingMutabilitySet)
{
  try
  {
    short const radius = 2;
    int const height = 10;
    long volume = -1;

    WG_LCLCLASS
    (CalculateVolume,
      memext (const radius) (type(int) height) (const volume) )
      void init()
      {
        WG_TEST_ASSERT_ISCONST(radius);
        WG_TEST_ASSERT_ISNOTCONST(height);
        WG_TEST_ASSERT_ISCONST(volume);

        WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(short, radius);
        WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, height);
        WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(long, volume);

        EXPECT_EQ(2, radius);
        EXPECT_EQ(10, height);
        EXPECT_EQ(20, volume);
      }
    WG_LCLCLASS_END;

    CalculateVolume c(radius, height, radius * height);
  }
  WG_GTEST_CATCH
}
