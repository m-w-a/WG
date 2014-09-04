#include <gtest/gtest.h>

#define WG_AUTOSIMULATOR_AUTOANYGROUP_CONFIG_PARAMS_MAX_ARITY 10

#include <WG/Local/Detail/AutoSimulator/Detail/AutoAnyGroup.hh>
#include <WG/Local/Detail/AutoSimulator/Tests/Utils.hh>

namespace
{

typedef ::wg::autosimulator::detail::auto_any_group const & auto_any_group_t;
using ::wg::autosimulator::detail::test::ExprGenerator;

}

using namespace ::wg::autosimulator;

TEST(wg_autosimulator_detail_autoanygroup, IsRValue1)
{
  ExprGenerator expr;

  bool autosimFlag = false;

#define EXPR \
  (expr.mutableArray())          (expr.constArray())     \
  (expr.copyonlyMutableRValue()) (expr.copyonlyConstRValue())  \
  (expr.copyonlyMutableLValue()) (expr.copyonlyConstLValue()) \
  (expr.moveonlyMutableRValue()) (expr.moveonlyMutableLValue()) \
  (expr.moveonlyConstLValue())

  auto_any_group_t grp = WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_MAKEGROUP(EXPR);
  WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_INITGROUP(grp, autosimFlag, EXPR);

  EXPECT_FALSE( WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_ITEM_ISRVALUE(grp, 0, EXPR) );
  EXPECT_FALSE( WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_ITEM_ISRVALUE(grp, 1, EXPR) );

  EXPECT_TRUE( WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_ITEM_ISRVALUE(grp, 2, EXPR) );
  EXPECT_TRUE( WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_ITEM_ISRVALUE(grp, 3, EXPR) );
  EXPECT_FALSE( WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_ITEM_ISRVALUE(grp, 4, EXPR) );
  EXPECT_FALSE( WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_ITEM_ISRVALUE(grp, 5, EXPR) );

  EXPECT_TRUE( WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_ITEM_ISRVALUE(grp, 6, EXPR) );
  EXPECT_FALSE( WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_ITEM_ISRVALUE(grp, 7, EXPR) );
  EXPECT_FALSE( WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_ITEM_ISRVALUE(grp, 8, EXPR) );

#undef EXPR
}

TEST(wg_autosimulator_detail_autoanygroup, IsRValue2)
{
  ExprGenerator expr;

  bool autosimFlag = false;

#define EXPR \
  (expr.copymoveMutableRValue()) (expr.copymoveConstRValue()) \
  (expr.copymoveMutableLValue()) (expr.copymoveConstLValue())

  auto_any_group_t grp = WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_MAKEGROUP(EXPR);
  WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_INITGROUP(grp, autosimFlag, EXPR);

  EXPECT_TRUE( WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_ITEM_ISRVALUE(grp, 0, EXPR) );
  EXPECT_TRUE( WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_ITEM_ISRVALUE(grp, 1, EXPR) );
  EXPECT_FALSE( WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_ITEM_ISRVALUE(grp, 2, EXPR) );
  EXPECT_FALSE( WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_ITEM_ISRVALUE(grp, 3, EXPR) );

#undef EXPR
}

namespace
{

struct CustomBase
{
  template <typename T>
  void finalize(T &)
  {
  }
};

}

TEST(wg_autosimulator_detail_autoanygroup_custom, IsRValue1)
{
  ExprGenerator expr;

  bool autosimFlag = false;

#define EXPR \
  (expr.mutableArray())          (expr.constArray())     \
  (expr.copyonlyMutableRValue()) (expr.copyonlyConstRValue())  \
  (expr.copyonlyMutableLValue()) (expr.copyonlyConstLValue()) \
  (expr.moveonlyMutableRValue()) (expr.moveonlyMutableLValue()) \
  (expr.moveonlyConstLValue())

  CustomBase const & grp =
    WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_MAKECUSTOMGROUP(CustomBase, EXPR);
  WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_INITGROUP(grp, autosimFlag, EXPR);

  EXPECT_FALSE( WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_ITEM_ISRVALUE(grp, 0, EXPR) );
  EXPECT_FALSE( WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_ITEM_ISRVALUE(grp, 1, EXPR) );

  EXPECT_TRUE( WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_ITEM_ISRVALUE(grp, 2, EXPR) );
  EXPECT_TRUE( WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_ITEM_ISRVALUE(grp, 3, EXPR) );
  EXPECT_FALSE( WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_ITEM_ISRVALUE(grp, 4, EXPR) );
  EXPECT_FALSE( WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_ITEM_ISRVALUE(grp, 5, EXPR) );

  EXPECT_TRUE( WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_ITEM_ISRVALUE(grp, 6, EXPR) );
  EXPECT_FALSE( WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_ITEM_ISRVALUE(grp, 7, EXPR) );
  EXPECT_FALSE( WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_ITEM_ISRVALUE(grp, 8, EXPR) );
#undef EXPR
}

TEST(wg_autosimulator_detail_autoanygroup_custom, IsRValue2)
{
  ExprGenerator expr;

  bool autosimFlag = false;

#define EXPR \
  (expr.copymoveMutableRValue()) (expr.copymoveConstRValue()) \
  (expr.copymoveMutableLValue()) (expr.copymoveConstLValue())

  CustomBase const & grp =
    WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_MAKECUSTOMGROUP(CustomBase, EXPR);
  WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_INITGROUP(grp, autosimFlag, EXPR);

  EXPECT_TRUE( WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_ITEM_ISRVALUE(grp, 0, EXPR) );
  EXPECT_TRUE( WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_ITEM_ISRVALUE(grp, 1, EXPR) );
  EXPECT_FALSE( WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_ITEM_ISRVALUE(grp, 2, EXPR) );
  EXPECT_FALSE( WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_ITEM_ISRVALUE(grp, 3, EXPR) );
#undef EXPR
}
