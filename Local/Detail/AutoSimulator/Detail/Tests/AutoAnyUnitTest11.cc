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
    RValue
  };
};

ExpressionCategory::Type expressionCategory(
  ::wg::autosimulator::detail::expr_category_lvalue)
{
  return ExpressionCategory::LValue;
}

ExpressionCategory::Type expressionCategory(
  ::wg::autosimulator::detail::expr_category_rvalue)
{
  return ExpressionCategory::RValue;
}

}

using ::wg::autosimulator::detail::test::ExprGenerator;

TEST(wg_autosimulator_detail_autoany_cpp11, MutableLValue)
{
  ExprGenerator expr;

#define EXPR expr.mutableLValue()
  bool isRValue = false;
  auto_any_t obj =
    WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CAPTURE(EXPR, isRValue);
  (void)obj;

  EXPECT_FALSE(isRValue);
  EXPECT_EQ(
    ExpressionCategory::LValue,
    expressionCategory(WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CATEGORY(EXPR)) );
#undef EXPR
}

TEST(wg_autosimulator_detail_autoany_cpp11, ConstLValue)
{
  ExprGenerator expr;

#define EXPR expr.constLValue()
  bool isRValue = false;
  auto_any_t obj =
    WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CAPTURE(EXPR, isRValue);
  (void)obj;

  EXPECT_FALSE(isRValue);
  EXPECT_EQ(
    ExpressionCategory::LValue,
    expressionCategory(WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CATEGORY(EXPR)) );
#undef EXPR
}

TEST(wg_autosimulator_detail_autoany_cpp11, MutableRValue)
{
  ExprGenerator expr;

#define EXPR expr.mutableRValue()
  bool isRValue = false;
  auto_any_t obj =
    WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CAPTURE(EXPR, isRValue);
  (void)obj;

  EXPECT_TRUE(isRValue);
  EXPECT_EQ(
    ExpressionCategory::RValue,
    expressionCategory(WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CATEGORY(EXPR)) );
#undef EXPR
}

TEST(wg_autosimulator_detail_autoany_cpp11, ConstRValue)
{
  ExprGenerator expr;

#define EXPR expr.constRValue()
  bool isRValue = false;
  auto_any_t obj =
    WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CAPTURE(EXPR, isRValue);
  (void)obj;

  EXPECT_TRUE(isRValue);
  EXPECT_EQ(
    ExpressionCategory::RValue,
    expressionCategory(WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CATEGORY(EXPR)) );
#undef EXPR
}
