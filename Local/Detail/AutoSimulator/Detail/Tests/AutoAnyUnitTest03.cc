#include <gtest/gtest.h>
#include <WG/Local/Detail/AutoSimulator/Detail/AutoAny.hh>

namespace
{
typedef ::wg::autosimulator::detail::auto_any const & auto_any_t;

struct ExpressionCategory
{
  enum Type
  {
    CompileTimeDeterminedAsLValue,
    RunTimeDetermined
  };
};

ExpressionCategory::Type expressionCategory(::boost::mpl::false_ *)
{
  return ExpressionCategory::CompileTimeDeterminedAsLValue;
}

ExpressionCategory::Type expressionCategory(bool *)
{
  return ExpressionCategory::RunTimeDetermined;
}

struct EmptyStruct {};
typedef EmptyStruct ArrayType[5];

EmptyStruct & mutableNonArrayLValue()
{
  static EmptyStruct toRet;
  return toRet;
}

EmptyStruct const & constNonArrayLValue()
{
  return mutableNonArrayLValue();
}

ArrayType & mutableArrayLValue()
{
  static ArrayType toRet;
  return toRet;
}

ArrayType const & constArrayLValue()
{
  return mutableArrayLValue();
}

EmptyStruct mutableRValue()
{
  return EmptyStruct();
}

EmptyStruct const constRValue()
{
  return EmptyStruct();
}

}

TEST(wg_autosimulator_detail_autoany_03, MutableNonArrayLValue)
{
#define EXPR mutableNonArrayLValue()
  bool isRValue = false;
  auto_any_t obj =
    WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CAPTURE(EXPR, isRValue);

  EXPECT_FALSE(obj.is_rvalue());
  EXPECT_EQ(
    ExpressionCategory::CompileTimeDeterminedAsLValue,
    expressionCategory(WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CATEGORY(EXPR)) );
#undef EXPR
}

TEST(wg_autosimulator_detail_autoany_03, ConstNonArrayLValue)
{
#define EXPR constNonArrayLValue()
  bool isRValue = false;
  auto_any_t obj =
    WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CAPTURE(EXPR, isRValue);

  EXPECT_FALSE(obj.is_rvalue());
  EXPECT_EQ(
    ExpressionCategory::RunTimeDetermined,
    expressionCategory(WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CATEGORY(EXPR)) );
#undef EXPR
}

TEST(wg_autosimulator_detail_autoany_03, MutableArrayLValue)
{
#define EXPR mutableArrayLValue()
  bool isRValue = false;
  auto_any_t obj =
    WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CAPTURE(EXPR, isRValue);

  EXPECT_FALSE(obj.is_rvalue());
  EXPECT_EQ(
    ExpressionCategory::CompileTimeDeterminedAsLValue,
    expressionCategory(WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CATEGORY(EXPR)) );
#undef EXPR
}

TEST(wg_autosimulator_detail_autoany_03, ConstArrayLValue)
{
#define EXPR constArrayLValue()
  bool isRValue = false;
  auto_any_t obj =
    WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CAPTURE(EXPR, isRValue);

  EXPECT_FALSE(obj.is_rvalue());
  EXPECT_EQ(
    ExpressionCategory::CompileTimeDeterminedAsLValue,
    expressionCategory(WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CATEGORY(EXPR)) );
#undef EXPR
}

TEST(wg_autosimulator_detail_autoany_03, MutableRValue)
{
#define EXPR mutableRValue()
  bool isRValue = false;
  auto_any_t obj =
    WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CAPTURE(EXPR, isRValue);

  EXPECT_TRUE(obj.is_rvalue());
  EXPECT_EQ(
    ExpressionCategory::RunTimeDetermined,
    expressionCategory(WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CATEGORY(EXPR)) );
#undef EXPR
}

TEST(wg_autosimulator_detail_autoany_03, ConstRValue)
{
#define EXPR constRValue()
  bool isRValue = false;
  auto_any_t obj =
    WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CAPTURE(EXPR, isRValue);

  EXPECT_TRUE(obj.is_rvalue());
  EXPECT_EQ(
    ExpressionCategory::RunTimeDetermined,
    expressionCategory(WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CATEGORY(EXPR)) );
#undef EXPR
}
