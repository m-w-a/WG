#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>

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

    WG_LCLFUNCTION_TPL
    (makeGingerBreadCookie,
      return (int)
      params ((bool) salt) ((bool) sugar)
      varbind (const pinchOfSalt)
      varset (const dos, dashOfSugar) )
    {
      return
        salt == pinchOfSalt &&
        sugar == dos;
    }
    WG_LCLFUNCTION_END;

    success = makeGingerBreadCookie(pinchOfSalt, dashOfSugar);

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
