#include <gtest/gtest.h>
#include <WG/Local/Tests/LclFunction/Utils/TestLclFunction.hh>
#include <WG/Local/Tests/Utils/Utils.hh>

#define WG_LOCAL_TESTS_LCLFUNCTION_MULTIPLEUSEINSAMEMACRO_DEFINEFUNCS() \
    WG_TEST_LCLFUNCTION \
    (makeGingerBreadCookie1, \
      return (int) \
      params (bool salt) (bool sugar) \
      varbind (const pinchOfSalt) \
      varset (const dos, dashOfSugar) ) \
    { \
      WG_TEST_LCLFUNCTION_MARKCALL(makeGingerBreadCookie1); \
      return \
        salt == pinchOfSalt && \
        sugar == dos; \
    } \
    WG_TEST_LCLFUNCTION_END; \
    \
    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF( \
      WG_LCLFUNCTION_TYPENAME(makeGingerBreadCookie1), \
      makeGingerBreadCookie1); \
    \
    WG_TEST_LCLFUNCTION \
    (makeGingerBreadCookie2, \
      return (int) \
      params (bool salt) (bool sugar) \
      varbind (const pinchOfSalt) \
      varset (const dos, dashOfSugar) ) \
    { \
      WG_TEST_LCLFUNCTION_MARKCALL(makeGingerBreadCookie2); \
      return \
        salt == pinchOfSalt && \
        sugar == dos; \
    } \
    WG_TEST_LCLFUNCTION_END; \
    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF( \
      WG_LCLFUNCTION_TYPENAME(makeGingerBreadCookie2), \
      makeGingerBreadCookie2); \

TEST(wg_lclfunction_multipleuseinsamemacro, Test)
{
  bool success = false;

  bool pinchOfSalt = true;
  int dashOfSugar = 0;

  WG_LOCAL_TESTS_LCLFUNCTION_MULTIPLEUSEINSAMEMACRO_DEFINEFUNCS();

  success = makeGingerBreadCookie1(pinchOfSalt, dashOfSugar);
  WG_TEST_LCLFUNCTION_VERIFYCALL(makeGingerBreadCookie1);
  EXPECT_TRUE(success);

  success = makeGingerBreadCookie2(pinchOfSalt, dashOfSugar);
  WG_TEST_LCLFUNCTION_VERIFYCALL(makeGingerBreadCookie2);
  EXPECT_TRUE(success);
}
