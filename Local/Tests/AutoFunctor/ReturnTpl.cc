#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>
#include <utility>
#include <boost/type_traits/add_const.hpp>

namespace
{
template <typename T>
struct OkIfReturnSpecified
{
  static void run()
  {
    T didAssign = false;

    WG_AUTOFUNCTOR_TPL
    (ret,
      assignto (didAssign)
      return (typename boost::add_const<T>::type) )
    {
      return true;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_TRUE(didAssign);
  }
};
}
TEST(wg_autofunctor_returntpl, OkIfReturnSpecified)
{
  try
  {
    OkIfReturnSpecified<bool>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T1, typename T2>
struct OkIfReturnPPEscaped
{
  static void run()
  {
    std::pair<T1, T2> didAssign = std::make_pair(false, 0);

    WG_AUTOFUNCTOR_TPL
    (ret,
      assignto (didAssign)
      return (ppescape((std::pair<T1, T2>)) const) )
    {
      return std::make_pair(true, 1);
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_TRUE(didAssign.first);
  }
};
}
TEST(wg_autofunctor_returntpl, OkIfReturnPPEscaped)
{
  try
  {
    OkIfReturnPPEscaped<bool, int>::run();
  }
  WG_GTEST_CATCH
}
