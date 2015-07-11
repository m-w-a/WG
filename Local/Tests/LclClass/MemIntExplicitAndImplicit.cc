#include <gtest/gtest.h>
#include <WG/Local/Tests/Utils/Utils.hh>
#include <WG/Local/LclClass.hh>

TEST(wg_lclclass_memintexplicitandimplicit, OkIf3MemOfVaryingMutabilitySet)
{
  WG_LCLCLASS
  (CalculateVolume,
    memint
      (const radius, 2)
      (height, 10)
      (type(long const) volume, radius * height) )
    void init()
    {
      WG_TEST_ASSERT_ISCONST(radius);
      WG_TEST_ASSERT_ISNOTCONST(height);
      WG_TEST_ASSERT_ISCONST(volume);

      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(long, volume);
    }
  WG_LCLCLASS_END;

  CalculateVolume c;
}
