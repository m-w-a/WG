#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>
#include <boost/tuple/tuple.hpp>

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

TEST(wg_autofunctor_return, OkIfGloballyScoped)
{
  try
  {
    ::boost::tuple<bool> didAssign = ::boost::make_tuple(false);

    WG_AUTOFUNCTOR
    (ret,
      assignto (didAssign)
      return (::boost::tuple<bool>) )
    {
      return ::boost::make_tuple(true);
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_TRUE(didAssign.get<0>());
  }
  WG_GTEST_CATCH
}
