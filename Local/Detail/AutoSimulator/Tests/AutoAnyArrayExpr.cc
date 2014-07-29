#include <gtest/gtest.h>
#include <WG/Local/Detail/AutoSimulator/AutoSimulator.hh>
#include <WG/Local/Detail/AutoSimulator/Tests/Utils.hh>

namespace
{

typedef int A5[5];
typedef A5 const ConstA5;

}

using namespace ::wg::autosimulator;

TEST(wg_autosimulator_autoany, MutableArrayExpr)
{
  A5 arr = {0, 1, 2, 3, 5};

  bool isRValue = false;
  auto_any_t obj = WG_AUTOSIMULATOR_AUTOANY_CAPTURE(arr, isRValue);

  EXPECT_FALSE(detail::test::isConstLValue(WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, arr)));
  EXPECT_EQ(5, WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, arr)[4]);

  WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, arr)[4] = 15;
  EXPECT_EQ(15, WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, arr)[4]);
}

TEST(wg_autosimulator_autoany, ConstArrayExpr)
{
  ConstA5 const arr = {0, 1, 2, 3, 5};

  bool isRValue = false;
  auto_any_t obj = WG_AUTOSIMULATOR_AUTOANY_CAPTURE(arr, isRValue);

  EXPECT_TRUE(detail::test::isConstLValue(WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, arr)));
  EXPECT_EQ(5, WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, arr)[4]);
}
