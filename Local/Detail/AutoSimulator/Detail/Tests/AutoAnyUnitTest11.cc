#include <gtest/gtest.h>
#include <WG/Local/Detail/AutoSimulator/Detail/AutoAny.hh>
#include <WG/Local/Detail/AutoSimulator/Tests/Utils.hh>

namespace
{

typedef ::wg::autosimulator::detail::auto_any const & auto_any_t;

struct ExpressionCategory
{
  enum Type
  {
    LValue,
    MutableRValue,
    ConstRValue
  };
};

ExpressionCategory::Type expressionCategory(
  ::wg::autosimulator::detail::expr_category_lvalue)
{
  return ExpressionCategory::LValue;
}

ExpressionCategory::Type expressionCategory(
  ::wg::autosimulator::detail::expr_category_mutable_rvalue)
{
  return ExpressionCategory::MutableRValue;
}

ExpressionCategory::Type expressionCategory(
  ::wg::autosimulator::detail::expr_category_const_rvalue)
{
  return ExpressionCategory::ConstRValue;
}

}

using ::wg::autosimulator::detail::test::ExprGenerator;

TEST(wg_autosimulator_detail_autoany_cpp11, MutableArray)
{
  ExprGenerator expr;

#define EXPR expr.mutableArray()
  bool autosimFlag = false;
  auto_any_t obj =
    WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CAPTURE(EXPR, autosimFlag);

  EXPECT_FALSE(WG_AUTOSIMULATOR_DETAIL_AUTOANY_ISRVALUE(obj, EXPR));
  EXPECT_EQ(
    ExpressionCategory::LValue,
    expressionCategory(WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CATEGORY(EXPR)) );
#undef EXPR
}

TEST(wg_autosimulator_detail_autoany_cpp11, ConstArray)
{
  ExprGenerator expr;

#define EXPR expr.constArray()
  bool autosimFlag = false;
  auto_any_t obj =
    WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CAPTURE(EXPR, autosimFlag);

  EXPECT_FALSE(WG_AUTOSIMULATOR_DETAIL_AUTOANY_ISRVALUE(obj, EXPR));
  EXPECT_EQ(
    ExpressionCategory::LValue,
    expressionCategory(WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CATEGORY(EXPR)) );
#undef EXPR
}

TEST(wg_autosimulator_detail_autoany_cpp11, CopyOnlyMutableLValue)
{
  ExprGenerator expr;

#define EXPR expr.copyonlyMutableLValue()
  bool autosimFlag = false;
  auto_any_t obj =
    WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CAPTURE(EXPR, autosimFlag);

  EXPECT_FALSE(WG_AUTOSIMULATOR_DETAIL_AUTOANY_ISRVALUE(obj, EXPR));
  EXPECT_EQ(
    ExpressionCategory::LValue,
    expressionCategory(WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CATEGORY(EXPR)) );
#undef EXPR
}

TEST(wg_autosimulator_detail_autoany_cpp11, CopyOnlyConstLValue)
{
  ExprGenerator expr;

#define EXPR expr.copyonlyConstLValue()
  bool autosimFlag = false;
  auto_any_t obj =
    WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CAPTURE(EXPR, autosimFlag);

  EXPECT_FALSE(WG_AUTOSIMULATOR_DETAIL_AUTOANY_ISRVALUE(obj, EXPR));
  EXPECT_EQ(
    ExpressionCategory::LValue,
    expressionCategory(WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CATEGORY(EXPR)) );
#undef EXPR
}

TEST(wg_autosimulator_detail_autoany_cpp11, CopyOnlyMutableRValue)
{
  ExprGenerator expr;

#define EXPR expr.copyonlyMutableRValue()
  bool autosimFlag = false;
  auto_any_t obj =
    WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CAPTURE(EXPR, autosimFlag);

  EXPECT_TRUE(WG_AUTOSIMULATOR_DETAIL_AUTOANY_ISRVALUE(obj, EXPR));
  EXPECT_EQ(
    ExpressionCategory::MutableRValue,
    expressionCategory(WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CATEGORY(EXPR)) );
#undef EXPR
}

TEST(wg_autosimulator_detail_autoany_cpp11, CopyOnlyConstRValue)
{
  ExprGenerator expr;

#define EXPR expr.copyonlyConstRValue()
  bool autosimFlag = false;
  auto_any_t obj =
    WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CAPTURE(EXPR, autosimFlag);

  EXPECT_TRUE(WG_AUTOSIMULATOR_DETAIL_AUTOANY_ISRVALUE(obj, EXPR));
  EXPECT_EQ(
    ExpressionCategory::ConstRValue,
    expressionCategory(WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CATEGORY(EXPR)) );
#undef EXPR
}

TEST(wg_autosimulator_detail_autoany_cpp11, MoveOnlyMutableRValue)
{
  ExprGenerator expr;

#define EXPR expr.moveonlyMutableRValue()
  bool autosimFlag = false;
  auto_any_t obj =
    WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CAPTURE(EXPR, autosimFlag);

  EXPECT_TRUE(WG_AUTOSIMULATOR_DETAIL_AUTOANY_ISRVALUE(obj, EXPR));
  EXPECT_EQ(
    ExpressionCategory::MutableRValue,
    expressionCategory(WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CATEGORY(EXPR)) );
#undef EXPR
}

TEST(wg_autosimulator_detail_autoany_cpp11, MoveOnlyMutableLValue)
{
  ExprGenerator expr;

#define EXPR expr.moveonlyMutableLValue()
  bool autosimFlag = false;
  auto_any_t obj =
    WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CAPTURE(EXPR, autosimFlag);

  EXPECT_FALSE(WG_AUTOSIMULATOR_DETAIL_AUTOANY_ISRVALUE(obj, EXPR));
  EXPECT_EQ(
    ExpressionCategory::LValue,
    expressionCategory(WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CATEGORY(EXPR)) );
#undef EXPR
}

TEST(wg_autosimulator_detail_autoany_cpp11, MoveOnlyConstLValue)
{
  ExprGenerator expr;

#define EXPR expr.moveonlyConstLValue()
  bool autosimFlag = false;
  auto_any_t obj =
    WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CAPTURE(EXPR, autosimFlag);

  EXPECT_FALSE(WG_AUTOSIMULATOR_DETAIL_AUTOANY_ISRVALUE(obj, EXPR));
  EXPECT_EQ(
    ExpressionCategory::LValue,
    expressionCategory(WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CATEGORY(EXPR)) );
#undef EXPR
}
