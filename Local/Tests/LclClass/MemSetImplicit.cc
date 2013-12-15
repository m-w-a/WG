#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/Tests/TestHelper.hh>
#include <WG/Local/LclClass.hh>
#include <boost/tuple/tuple.hpp>

TEST(wg_lclclass_memsetimplicit, OkIfMemValueGloballyScoped)
{
  try
  {
    WG_LCLCLASS
    (Local,
      memset (assigner, ::boost::make_tuple(true)) )
      void init()
      {
        WG_TESTHELPER_ASSERT_ISNOTCONST(assigner);
        WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
          ::boost::tuple<bool>, assigner);

        EXPECT_EQ(true, assigner.get<0>());
      }
    WG_LCLCLASS_END;

    Local obj;
  }
  WG_GTEST_CATCH
}

TEST(wg_lclclass_memsetimplicit, OkIf3MemOfVaryingMutabilitySet)
{
  try
  {
    WG_LCLCLASS
    (CalculateVolume,
      memset
        (const radius, 2)
        (height, 10ul)
        (volume, radius * height) )
      void init()
      {
        WG_TESTHELPER_ASSERT_ISCONST(radius);
        WG_TESTHELPER_ASSERT_ISNOTCONST(height);
        WG_TESTHELPER_ASSERT_ISNOTCONST(volume);

        WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, radius);
        WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(unsigned long, height);
        WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(unsigned long, volume);
      }
    WG_LCLCLASS_END;

    CalculateVolume c;
  }
  WG_GTEST_CATCH
}
