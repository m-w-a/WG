#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/Tests/LclFunction/Utils/TestLclFunction.hh>
#include <WG/Local/Tests/Utils/Utils.hh>

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

    WG_TEST_LCLFUNCTION_TPL
    (makeGingerBreadCookie,
      return (int)
      params (bool salt) (bool sugar)
      varbind (const pinchOfSalt)
      varset (const dos, dashOfSugar) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(makeGingerBreadCookie);

      WG_TEST_ASSERT_ISNOTCONST_TPL(salt);
      WG_TEST_ASSERT_ISNOTCONST_TPL(sugar);
      WG_TEST_ASSERT_ISCONST_TPL(pinchOfSalt);
      WG_TEST_ASSERT_ISCONST_TPL(dos);

      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(bool, salt);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(bool, sugar);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T1, pinchOfSalt);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T2, dashOfSugar);

      return
        salt == pinchOfSalt &&
        sugar == dos;
    }
    WG_TEST_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(
      int, makeGingerBreadCookie(0,0));

    success = makeGingerBreadCookie(pinchOfSalt, dashOfSugar);
    WG_TEST_LCLFUNCTION_VERIFYCALL(makeGingerBreadCookie);

    EXPECT_TRUE(success);
  }
};
}
TEST(wg_lclfunction_allcombo_tpl, Test)
{
  try
  {
    TestTpl<bool, int>::run();
  }
  WG_GTEST_CATCH
}
