#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>
#include <WG/Local/Tests/TestHelper.hh>

#define WG_LOCAL_TESTS_LCLFUNCTION_MULTIPLEUSEINSAMEMACRO_DEFINEFUNCS() \
    WG_LCLFUNCTION \
    (makeGingerBreadCookie1, \
      return (int) \
      params (bool salt) (bool sugar) \
      varbind (const pinchOfSalt) \
      varset (const dos, dashOfSugar) ) \
    { \
      return \
        salt == pinchOfSalt && \
        sugar == dos; \
    } \
    WG_LCLFUNCTION_END; \
    \
    WG_LCLFUNCTION \
    (makeGingerBreadCookie2, \
      return (int) \
      params (bool salt) (bool sugar) \
      varbind (const pinchOfSalt) \
      varset (const dos, dashOfSugar) ) \
    { \
      return \
        salt == pinchOfSalt && \
        sugar == dos; \
    } \
    WG_LCLFUNCTION_END;

TEST(wg_lclfunction_multipleuseinsamemacro, Test)
{
  try
  {
    bool success = false;

    bool pinchOfSalt = true;
    int dashOfSugar = 0;

    WG_LOCAL_TESTS_LCLFUNCTION_MULTIPLEUSEINSAMEMACRO_DEFINEFUNCS();

    success = makeGingerBreadCookie1(pinchOfSalt, dashOfSugar);
    EXPECT_TRUE(success);

    success = makeGingerBreadCookie2(pinchOfSalt, dashOfSugar);
    EXPECT_TRUE(success);
  }
  WG_GTEST_CATCH
}
