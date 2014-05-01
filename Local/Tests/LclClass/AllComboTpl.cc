#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclClass.hh>
#include <string>

namespace
{
template <typename T>
struct Tester
{
  static void run()
  {
    struct Base { enum { ID = 11 }; };

    bool var = false;

    WG_LCLCLASS_TPL
    (Local,
     derives (protected Base)
     memext (type(T const) name) (var)
     memint (score, 21) )
      void init()
      {
        EXPECT_EQ(Local::ID, 11);
        EXPECT_FALSE(var);
        EXPECT_EQ(name, "FooBar");
        EXPECT_EQ(score, 21);
      }
    WG_LCLCLASS_END;

    Local l("FooBar", var);
  }
};
}
TEST(wg_lclclass_allcombo_tpl, Test)
{
  try
  {
    Tester<std::string>::run();
  }
  WG_GTEST_CATCH
}
