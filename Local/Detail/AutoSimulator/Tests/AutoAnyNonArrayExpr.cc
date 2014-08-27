#include <gtest/gtest.h>
#include <WG/Local/Detail/AutoSimulator/AutoSimulator.hh>
#include <WG/Local/Detail/AutoSimulator/Tests/Utils.hh>

using namespace ::wg::autosimulator;
using namespace ::wg::autosimulator::detail::test;

TEST(wg_autosimulator_autoany, MutableRValueExpr)
{
  ExprGenerator expr;
#define EXPR expr.mutableRValue()
  bool autosimFlag = false;
  auto_any_t obj = WG_AUTOSIMULATOR_AUTOANY_CAPTURE(EXPR, autosimFlag);

  EXPECT_FALSE(isConst(WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR)));
  EXPECT_EQ(11, WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR).value);

  WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR).value = 12;
  EXPECT_EQ(12, WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR).value);
#undef EXPR
}

TEST(wg_autosimulator_autoany, ConstRValueExpr)
{
  ExprGenerator expr;
#define EXPR expr.constRValue()
  bool autosimFlag = false;
  auto_any_t obj = WG_AUTOSIMULATOR_AUTOANY_CAPTURE(EXPR, autosimFlag);

  EXPECT_TRUE(isConst(WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR)));
  EXPECT_EQ(11, WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR).value);
#undef EXPR
}

TEST(wg_autosimulator_autoany, MutableLValueExpr)
{
  ExprGenerator expr;
#define EXPR expr.mutableLValue()
  bool autosimFlag = false;
  auto_any_t obj = WG_AUTOSIMULATOR_AUTOANY_CAPTURE(EXPR, autosimFlag);

  EXPECT_FALSE(isConst(WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR)));
  EXPECT_EQ(11, WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR).value);

  WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR).value = 12;
  EXPECT_EQ(12, WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR).value);
#undef EXPR
}

TEST(wg_autosimulator_autoany, ConstLValueExpr)
{
  ExprGenerator expr;
#define EXPR expr.constLValue()
  bool autosimFlag = false;
  auto_any_t obj = WG_AUTOSIMULATOR_AUTOANY_CAPTURE(EXPR, autosimFlag);

  EXPECT_TRUE(isConst(WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR)));
  EXPECT_EQ(11, WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR).value);
#undef EXPR
}

TEST(wg_autosimulator_autoany, MoveOnlyMutableRValueExpr)
{
  ExprGenerator expr;
#define EXPR expr.moveonlyMutableRValue()
  bool autosimFlag = false;
  auto_any_t obj = WG_AUTOSIMULATOR_AUTOANY_CAPTURE(EXPR, autosimFlag);

  EXPECT_FALSE(isConst(WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR)));
  EXPECT_EQ(121, WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR).value);

  WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR).value = 122;
  EXPECT_EQ(122, WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR).value);
#undef EXPR
}

TEST(wg_autosimulator_autoany, MoveOnlyMutableLValueExpr)
{
  ExprGenerator expr;
#define EXPR expr.moveonlyMutableLValue()
  bool autosimFlag = false;
  auto_any_t obj = WG_AUTOSIMULATOR_AUTOANY_CAPTURE(EXPR, autosimFlag);

  EXPECT_FALSE(isConst(WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR)));
  EXPECT_EQ(121, WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR).value);

  WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR).value = 122;
  EXPECT_EQ(122, WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR).value);
#undef EXPR
}
