#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclClass.hh>
#include <string>

#define WG_LCLCLASS_TESTS_MULTIPLEUSEINSAMEMACRO_DEFINETYPES() \
    WG_LCLCLASS_TPL \
    (Local1, \
     derives (protected Base) \
     memdecl (local(Param0Type) name) \
     memlike (var) \
     memset (score, 21) ) \
      void init() \
      { \
        EXPECT_EQ(Local1::ID, 11); \
        EXPECT_FALSE(var); \
        EXPECT_EQ(score, 21); \
      } \
    WG_LCLCLASS_END; \
    \
    WG_LCLCLASS_TPL \
    (Local2, \
     derives (protected Base) \
     memdecl (local(Param0Type) name) \
     memlike (var) \
     memset (score, 21) ) \
      void init() \
      { \
        EXPECT_EQ(Local2::ID, 11); \
        EXPECT_FALSE(var); \
        EXPECT_EQ(score, 21); \
      } \
    WG_LCLCLASS_END;

namespace
{
struct ignore;

template <typename IGNORED>
struct Tester
{
  static void run()
  {
    struct Base { enum { ID = 11 }; };

    bool var = false;

    struct Param0Type {};

    WG_LCLCLASS_TESTS_MULTIPLEUSEINSAMEMACRO_DEFINETYPES();

    Local1 l1(Param0Type(), var);
    Local2 l2(Param0Type(), var);
  }
};
}
TEST(wg_lclclass_multipleuseinsamemacro_tpl, Tester)
{
  try
  {
    Tester<ignore>::run();
  }
  WG_GTEST_CATCH
}
