#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>
#include <utility>
#include <boost/typeof/typeof.hpp>
#include <WG/Local/Tests/TestHelper.hh>

namespace
{
template <typename T>
struct EnsureTypeOfNotUsed
{
  static void run()
  {
    float value = 1.2f;

    WG_LCLFUNCTION_TPL(bindByDiffType, varbind ((T const) value) )
    {
//      WG_PP_TESTHELPER_IS_SAME_TYPE(
//        T const, BOOST_TYPEOF_TPL(value) const);
        EXPECT_EQ(1, value);
    }WG_LCLFUNCTION_END;

    bindByDiffType();
  }
};
}
TEST(wg_lclfunction_varbindexplicit_tpl, EnsureTypeOfNotUsed)
{
  EnsureTypeOfNotUsed<int>::run();
}
