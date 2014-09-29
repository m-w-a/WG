#include <gtest/gtest.h>
#include <WG/Local/LclClass.hh>
#include <string>

namespace
{
template <typename T>
struct Tester
{
  static void run()
  {
    struct Base1
    {
      explicit Base1(int v)
      : value(v)
      {}

      int value;
    };

    struct Base2 { enum { ID = 11 }; };

    bool var = false;

    WG_LCLCLASS_TPL
    (Local,
     derives (public Base1) (protected Base2)
     memext (type(T const) name) (var)
     memint (score, 21)
     baseinit (Base1(31)) )
      void init()
      {
        EXPECT_EQ(Local::ID, 11);
        EXPECT_FALSE(var);
        EXPECT_EQ(name, "FooBar");
        EXPECT_EQ(score, 21);
        EXPECT_EQ(this->value, 31);
      }
    WG_LCLCLASS_END;

    Local l("FooBar", var);
  }
};
}

TEST(wg_lclclass_allcombo_tpl, Test)
{
  Tester<std::string>::run();
}
