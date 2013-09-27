#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>
#include <utility>

TEST(wg_autofunctor_return, OkIfSpecified)
{
  try
  {
    bool didAssign = false;

    WG_AUTOFUNCTOR(ret, assignto (didAssign) return (int) )
    {
      return 1;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_TRUE(didAssign);
  }
  WG_GTEST_CATCH
}

TEST(wg_autofunctor_return, OkIfPPEscaped)
{
  try
  {
    std::pair<bool, int> didAssign = std::make_pair(false, 0);

    WG_AUTOFUNCTOR
    (ret,
      assignto (didAssign)
      return (ppescape((std::pair<bool, int>))) )
    {
      return std::make_pair(true, 1);
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_TRUE(didAssign.first);
  }
  WG_GTEST_CATCH
}
