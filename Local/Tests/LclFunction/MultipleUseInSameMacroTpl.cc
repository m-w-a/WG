#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/Tests/LclFunction/Utils/TestLclFunction.hh>
#include <WG/Local/Tests/Utils/Utils.hh>

#define WG_LOCAL_TESTS_LCLFUNCTION_MULTIPLEUSEINSAMEMACROTPL_DEFINEFUNCS() \
    WG_TEST_LCLFUNCTION_TPL \
    (makeGingerBreadCookie1, \
      return (int) \
      params (bool salt) (bool sugar) \
      varbind (const pinchOfSalt) \
      varset (const dos, dashOfSugar) ) \
    { \
      WG_TEST_LCLFUNCTION_MARKCALL(makeGingerBreadCookie1) \
      return \
        salt == pinchOfSalt && \
        sugar == dos; \
    } \
    WG_TEST_LCLFUNCTION_END; \
    \
    WG_TEST_LCLFUNCTION_TPL \
    (makeGingerBreadCookie2, \
      return (int) \
      params (bool salt) (bool sugar) \
      varbind (const pinchOfSalt) \
      varset (const dos, dashOfSugar) ) \
    { \
      WG_TEST_LCLFUNCTION_MARKCALL(makeGingerBreadCookie2) \
      return \
        salt == pinchOfSalt && \
        sugar == dos; \
    } \
    WG_TEST_LCLFUNCTION_END;

namespace
{
template <typename T1, typename T2>
struct TestTpl
{
  static void run()
  {
    bool success = false;

    T1 pinchOfSalt = true;
    T2 dashOfSugar = 0;

    WG_LOCAL_TESTS_LCLFUNCTION_MULTIPLEUSEINSAMEMACROTPL_DEFINEFUNCS();

    success = makeGingerBreadCookie1(pinchOfSalt, dashOfSugar);
    WG_TEST_LCLFUNCTION_VERIFYCALL(makeGingerBreadCookie1);
    EXPECT_TRUE(success);

    success = makeGingerBreadCookie2(pinchOfSalt, dashOfSugar);
    WG_TEST_LCLFUNCTION_VERIFYCALL(makeGingerBreadCookie2)
    EXPECT_TRUE(success);
  }
};
}
TEST(wg_lclfunction_multipleuseinsamemacro_tpl, Test)
{
  try
  {
    TestTpl<bool, int>::run();
  }
  WG_GTEST_CATCH
}
