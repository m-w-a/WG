#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclClass.hh>
#include <string>

#define WG_LCLCLASS_TESTS_MULTIPLEUSEINSAMEMACRO_DEFINETYPES() \
    WG_LCLCLASS \
    (Local1, \
     derives (protected Base) \
     memdecl (local(Param0Type) name) \
     memlike (var) \
     memset (score, 21) ) \
      void init() \
      { \
        EXPECT_EQ(ID, 11); \
        EXPECT_FALSE(var); \
        EXPECT_EQ(score, 21); \
      } \
    WG_LCLCLASS_END; \
    \
    WG_LCLCLASS \
    (Local2, \
     derives (protected Base) \
     memdecl (local(Param0Type) name) \
     memlike (var) \
     memset (score, 21) ) \
      void init() \
      { \
        EXPECT_EQ(ID, 11); \
        EXPECT_FALSE(var); \
        EXPECT_EQ(score, 21); \
      } \
    WG_LCLCLASS_END;

TEST(wg_lclclass_multipleuseinsamemacro, Tester)
{
  try
  {
    struct Base { enum { ID = 11 }; };

    bool var = false;

    struct Param0Type {};

    WG_LCLCLASS_TESTS_MULTIPLEUSEINSAMEMACRO_DEFINETYPES();

    Local1 l1(Param0Type(), var);
    Local2 l2(Param0Type(), var);
  }
  WG_GTEST_CATCH
}
