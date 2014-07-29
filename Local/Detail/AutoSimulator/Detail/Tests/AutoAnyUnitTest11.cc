#include <gtest/gtest.h>
#include <WG/Local/Detail/AutoSimulator/Detail/AutoAny.hh>

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

struct EmptyStruct {};

EmptyStruct & mutableLValue()
{
  static EmptyStruct toRet;
  return toRet;
}

EmptyStruct const & constLValue()
{
  return mutableLValue();
}

EmptyStruct mutableRValue()
{
  return EmptyStruct();
}

EmptyStruct constRValue()
{
  return EmptyStruct();
}

}

TEST(wg_autosimulator_detail_autoany_cpp11, MutableLValue)
{
#define EXPR mutableLValue()
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
#define EXPR constLValue()
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
#define EXPR mutableRValue()
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
#define EXPR constRValue()
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
