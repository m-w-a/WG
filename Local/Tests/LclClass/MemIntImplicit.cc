#include <gtest/gtest.h>
#include <WG/Local/Tests/Utils/Utils.hh>
#include <WG/Local/LclClass.hh>
#include <boost/tuple/tuple.hpp>

TEST(wg_lclclass_memintimplicit, OkIfMemValueGloballyScoped)
{
  WG_LCLCLASS
  (Local,
    memint (assigner, ::boost::make_tuple(true)) )
    void init()
    {
      WG_TEST_ASSERT_ISNOTCONST(assigner);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
        ::boost::tuple<bool>, assigner);

      EXPECT_EQ(true, assigner.get<0>());
    }
  WG_LCLCLASS_END;

  Local obj;
}

TEST(wg_lclclass_memintimplicit, OkIf3MemOfVaryingMutabilitySet)
{
  WG_LCLCLASS
  (CalculateVolume,
    memint
      (const radius, 2)
      (height, 10ul)
      (volume, radius * height) )
    void init()
    {
      WG_TEST_ASSERT_ISCONST(radius);
      WG_TEST_ASSERT_ISNOTCONST(height);
      WG_TEST_ASSERT_ISNOTCONST(volume);

      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, radius);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(unsigned long, height);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(unsigned long, volume);
    }
  WG_LCLCLASS_END;

  CalculateVolume c;
}
