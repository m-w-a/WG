#include <gtest/gtest.h>
#include <WG/Local/Detail/AutoSimulator/AutoSimulator.hh>
#include <WG/Local/Detail/AutoSimulator/Tests/Utils.hh>

using namespace ::wg::autosimulator;

TEST(wg_autosimulator_autoany, MutableRValueExpr)
{
  detail::test::ExprGenerator expr;
#define EXPR expr.mutableRValue()
  bool autosimFlag = false;
  auto_any_t obj = WG_AUTOSIMULATOR_AUTOANY_CAPTURE(EXPR, autosimFlag);

  EXPECT_FALSE(detail::test::isConstLValue(WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR)));
  EXPECT_EQ(11, WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR).value);

  WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR).value = 12;
  EXPECT_EQ(12, WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR).value);
#undef EXPR
}

TEST(wg_autosimulator_autoany, ConstRValueExpr)
{
  detail::test::ExprGenerator expr;
#define EXPR expr.constRValue()
  bool autosimFlag = false;
  auto_any_t obj = WG_AUTOSIMULATOR_AUTOANY_CAPTURE(EXPR, autosimFlag);

  EXPECT_TRUE(detail::test::isConstLValue(WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR)));
  EXPECT_EQ(11, WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR).value);
#undef EXPR
}

TEST(wg_autosimulator_autoany, MutableLValueExpr)
{
  detail::test::ExprGenerator expr;
#define EXPR expr.mutableLValue()
  bool autosimFlag = false;
  auto_any_t obj = WG_AUTOSIMULATOR_AUTOANY_CAPTURE(EXPR, autosimFlag);

  EXPECT_FALSE(detail::test::isConstLValue(WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR)));
  EXPECT_EQ(11, WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR).value);

  WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR).value = 12;
  EXPECT_EQ(12, WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR).value);
#undef EXPR
}

TEST(wg_autosimulator_autoany, ConstLValueExpr)
{
  detail::test::ExprGenerator expr;
#define EXPR expr.constLValue()
  bool autosimFlag = false;
  auto_any_t obj = WG_AUTOSIMULATOR_AUTOANY_CAPTURE(EXPR, autosimFlag);

  EXPECT_TRUE(detail::test::isConstLValue(WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR)));
  EXPECT_EQ(11, WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR).value);
#undef EXPR
}
