#include <gtest/gtest.h>
#include <WG/Local/Detail/AutoSimulator/AutoSimulator.hh>
#include <WG/Local/Detail/AutoSimulator/Tests/Utils.hh>

using namespace ::wg::autosimulator;
using namespace ::wg::autosimulator::detail::test;

TEST(wg_autosimulator_autoany, MutableArrayExpr)
{
  ExprGenerator expr;
#define EXPR expr.mutableArray()
  bool autosimFlag = false;
  auto_any_t obj = WG_AUTOSIMULATOR_AUTOANY_CAPTURE(EXPR, autosimFlag);

  EXPECT_FALSE(
    isConst(WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR)));
  EXPECT_EQ(4, WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR)[4]);

  WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR)[4] = 15;
  EXPECT_EQ(15, WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR)[4]);
#undef EXPR
}

TEST(wg_autosimulator_autoany, ConstArrayExpr)
{
  ExprGenerator expr;
#define EXPR expr.constArray()
  bool autosimFlag = false;
  auto_any_t obj = WG_AUTOSIMULATOR_AUTOANY_CAPTURE(EXPR, autosimFlag);

  EXPECT_TRUE(isConst(WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR)));
  EXPECT_EQ(14, WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR)[4]);
#undef EXPR
}
