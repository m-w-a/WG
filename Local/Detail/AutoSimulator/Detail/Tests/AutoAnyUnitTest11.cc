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

TEST(wg_autosimulator_detail_autoany_cpp11, MutableLValue)
{
  ExprGenerator expr;

#define EXPR expr.mutableLValue()
  bool autosimFlag = false;
  auto_any_t obj =
    WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CAPTURE(EXPR, autosimFlag);

  EXPECT_FALSE(WG_AUTOSIMULATOR_DETAIL_AUTOANY_ISRVALUE(obj, EXPR));
  EXPECT_EQ(
    ExpressionCategory::LValue,
    expressionCategory(WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CATEGORY(EXPR)) );
#undef EXPR
}

TEST(wg_autosimulator_detail_autoany_cpp11, ConstLValue)
{
  ExprGenerator expr;

#define EXPR expr.constLValue()
  bool autosimFlag = false;
  auto_any_t obj =
    WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CAPTURE(EXPR, autosimFlag);

  EXPECT_FALSE(WG_AUTOSIMULATOR_DETAIL_AUTOANY_ISRVALUE(obj, EXPR));
  EXPECT_EQ(
    ExpressionCategory::LValue,
    expressionCategory(WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CATEGORY(EXPR)) );
#undef EXPR
}

TEST(wg_autosimulator_detail_autoany_cpp11, MutableRValue)
{
  ExprGenerator expr;

#define EXPR expr.mutableRValue()
  bool autosimFlag = false;
  auto_any_t obj =
    WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CAPTURE(EXPR, autosimFlag);

  EXPECT_TRUE(WG_AUTOSIMULATOR_DETAIL_AUTOANY_ISRVALUE(obj, EXPR));
  EXPECT_EQ(
    ExpressionCategory::MutableRValue,
    expressionCategory(WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CATEGORY(EXPR)) );
#undef EXPR
}

TEST(wg_autosimulator_detail_autoany_cpp11, ConstRValue)
{
  ExprGenerator expr;

#define EXPR expr.constRValue()
  bool autosimFlag = false;
  auto_any_t obj =
    WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CAPTURE(EXPR, autosimFlag);

  EXPECT_TRUE(WG_AUTOSIMULATOR_DETAIL_AUTOANY_ISRVALUE(obj, EXPR));
  EXPECT_EQ(
    ExpressionCategory::ConstRValue,
    expressionCategory(WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CATEGORY(EXPR)) );
#undef EXPR
}
