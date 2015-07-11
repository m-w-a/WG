#include <gtest/gtest.h>
#include <WG/Local/Detail/AutoSimulator/AutoSimulator.hh>
#include <WG/Local/Detail/AutoSimulator/Tests/Utils.hh>

using namespace ::wg::autosimulator;
using namespace ::wg::autosimulator::detail::test;

TEST(wg_autosimulator_autoany, CopyOnlyMutableRValueExpr)
{
  ExprGenerator expr;
#define EXPR expr.copyonlyMutableRValue()
  bool autosimFlag = false;
  auto_any_t obj = WG_AUTOSIMULATOR_AUTOANY_CAPTURE(EXPR, autosimFlag);

  EXPECT_FALSE(isConst(WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR)));
  EXPECT_EQ(11, WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR).value);

  WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR).value = 12;
  EXPECT_EQ(12, WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR).value);
#undef EXPR
}

TEST(wg_autosimulator_autoany, CopyOnlyConstRValueExpr)
{
  ExprGenerator expr;
#define EXPR expr.copyonlyConstRValue()
  bool autosimFlag = false;
  auto_any_t obj = WG_AUTOSIMULATOR_AUTOANY_CAPTURE(EXPR, autosimFlag);

  EXPECT_TRUE(isConst(WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR)));
  EXPECT_EQ(11, WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR).value);
#undef EXPR
}

TEST(wg_autosimulator_autoany, CopyOnlyMutableLValueExpr)
{
  ExprGenerator expr;
#define EXPR expr.copyonlyMutableLValue()
  bool autosimFlag = false;
  auto_any_t obj = WG_AUTOSIMULATOR_AUTOANY_CAPTURE(EXPR, autosimFlag);

  EXPECT_FALSE(isConst(WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR)));
  EXPECT_EQ(11, WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR).value);

  WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR).value = 12;
  EXPECT_EQ(12, WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR).value);
#undef EXPR
}

TEST(wg_autosimulator_autoany, CopyOnlyConstLValueExpr)
{
  ExprGenerator expr;
#define EXPR expr.copyonlyConstLValue()
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

TEST(wg_autosimulator_autoany, MoveOnlyConstLValueExpr)
{
  ExprGenerator expr;
#define EXPR expr.moveonlyConstLValue()
  bool autosimFlag = false;
  auto_any_t obj = WG_AUTOSIMULATOR_AUTOANY_CAPTURE(EXPR, autosimFlag);

  EXPECT_TRUE(isConst(WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR)));
  EXPECT_EQ(121, WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR).value);
#undef EXPR
}

TEST(wg_autosimulator_autoany, CopyMoveMutableRValue)
{
  ExprGenerator expr;
#define EXPR expr.copymoveMutableRValue()
  bool autosimFlag = false;
  auto_any_t obj = WG_AUTOSIMULATOR_AUTOANY_CAPTURE(EXPR, autosimFlag);

  EXPECT_FALSE(isConst(WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR)));
  EXPECT_EQ(345, WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR).value);

  WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR).value = 346;
  EXPECT_EQ(346, WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR).value);
#undef EXPR
}

TEST(wg_autosimulator_autoany, CopyMoveConstRValue)
{
  ExprGenerator expr;
#define EXPR expr.copymoveConstRValue()
  bool autosimFlag = false;
  auto_any_t obj = WG_AUTOSIMULATOR_AUTOANY_CAPTURE(EXPR, autosimFlag);

  EXPECT_TRUE(isConst(WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR)));
  EXPECT_EQ(345, WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR).value);
#undef EXPR
}

TEST(wg_autosimulator_autoany, CopyMoveMutableLValue)
{
  ExprGenerator expr;
#define EXPR expr.copymoveMutableLValue()
  bool autosimFlag = false;
  auto_any_t obj = WG_AUTOSIMULATOR_AUTOANY_CAPTURE(EXPR, autosimFlag);

  EXPECT_FALSE(isConst(WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR)));
  EXPECT_EQ(345, WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR).value);

  WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR).value = 346;
  EXPECT_EQ(346, WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR).value);
#undef EXPR
}

TEST(wg_autosimulator_autoany, CopyMoveConstLValue)
{
  ExprGenerator expr;
#define EXPR expr.copymoveConstLValue()
  bool autosimFlag = false;
  auto_any_t obj = WG_AUTOSIMULATOR_AUTOANY_CAPTURE(EXPR, autosimFlag);

  EXPECT_TRUE(isConst(WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR)));
  EXPECT_EQ(345, WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR).value);
#undef EXPR
}
