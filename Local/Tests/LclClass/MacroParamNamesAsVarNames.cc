#include <gtest/gtest.h>
#include <WG/Local/LclClass.hh>

TEST(wg_lclclass_macroparamnamesasvarnames, ImplicitlyTyped)
{
  bool type = true;

  WG_LCLCLASS(Local,
    memext (type) memint (lcltype, 'a') )
      void init()
      {
        EXPECT_EQ(true, type);
        EXPECT_EQ('a', lcltype);
      }
  WG_LCLCLASS_END;

  Local l(type);
}

TEST(wg_lclclass_macroparamnamesasvarnames, ExplicitlyTyped)
{
  struct SomeLocalType
  {
    char value;
  };

  SomeLocalType slo = {'a'};

  WG_LCLCLASS(Local,
    memext (lcltype(SomeLocalType) lcltype) memint (type(bool) type, true) )
      void init()
      {
        EXPECT_EQ('a', lcltype.value);
        EXPECT_EQ(true, type);
      }
  WG_LCLCLASS_END;

  Local l(slo);
}
