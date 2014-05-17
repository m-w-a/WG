#include <gtest/gtest.h>
#include <WG/Local/LclClass.hh>
#include <string>

TEST(wg_lclclass_allcombo, Tester)
{
  struct Base { enum { ID = 11 }; };

  bool var = false;

  WG_LCLCLASS
  (Local,
   derives (protected Base)
   memext (type(std::string const) name) (var)
   memint (score, 21) )
    void init()
    {
      EXPECT_EQ(ID, 11);
      EXPECT_FALSE(var);
      EXPECT_EQ(name, "FooBar");
      EXPECT_EQ(score, 21);
    }
  WG_LCLCLASS_END;

  Local l("FooBar", var);
}
