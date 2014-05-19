#include <gtest/gtest.h>
#include <WG/Local/Tests/Utils/Utils.hh>
#include <WG/Local/LclClass.hh>
#include <boost/tuple/tuple.hpp>

TEST(wg_lclclass_memintexplicit, EnsureTypeOfNotUsed)
{
  WG_LCLCLASS(Local, memint (type(int) value, 1.2f) )
    void init()
    {
      WG_TEST_ASSERT_ISNOTCONST(value);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, value);

      EXPECT_EQ(1, value);
    }
  WG_LCLCLASS_END;

  Local obj;
}

TEST(wg_lclclass_memintexplicit, OkIfMemTypeGloballyScoped)
{
  WG_LCLCLASS
  (Local,
    memint (type(::boost::tuple<bool>) assigner, ::boost::make_tuple(true)) )
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

TEST(wg_lclclass_memintexplicit, OkIf3MemOfVaryingMutabilitySet)
{
  WG_LCLCLASS
  (CalculateVolume,
    memint
      (type(short const) radius, 2)
      (type(int const) height, 10)
      (type(long) volume, radius * height) )
    void init()
    {
      WG_TEST_ASSERT_ISCONST(radius);
      WG_TEST_ASSERT_ISCONST(height);
      WG_TEST_ASSERT_ISNOTCONST(volume);

      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(short, radius);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, height);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(long, volume);
    }
  WG_LCLCLASS_END;

  CalculateVolume c;
}

TEST(wg_lclclass_memintexplicit, OkIfNoQlfdLocalTypeSet)
{
  WG_TEST_LOCALTYPE_DECLARE(SomeLocalClass);

  WG_LCLCLASS
  (UseLocalKeyword, memint (lcltype(SomeLocalClass) obj, SomeLocalClass()) )
    void init()
    {
      WG_TEST_ASSERT_LOCALTYPE_ISNOTCONST(obj);
      WG_TEST_ASSERT_LOCALTYPE_ISSAMETYPE_MODULOCONSTANDREF(
        SomeLocalClass, obj);
    }
  WG_LCLCLASS_END;

  UseLocalKeyword ulk;
}

TEST(wg_lclclass_memintexplicit, OkIfConstQlfdLocalTypeSet)
{
  WG_TEST_LOCALTYPE_DECLARE(SomeLocalClass);

  WG_LCLCLASS
  (UseLocalKeyword, memint (lcltype(SomeLocalClass) const obj, SomeLocalClass()) )
    void init()
    {
      WG_TEST_ASSERT_LOCALTYPE_ISCONST(obj);
      WG_TEST_ASSERT_LOCALTYPE_ISSAMETYPE_MODULOCONSTANDREF(
        SomeLocalClass, obj);
    }
  WG_LCLCLASS_END;

  UseLocalKeyword ulk;
}
