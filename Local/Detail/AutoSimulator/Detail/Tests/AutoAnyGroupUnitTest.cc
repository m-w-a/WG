#include <gtest/gtest.h>
#include <WG/Local/Detail/AutoSimulator/Detail/AutoAnyGroup.hh>
#include <WG/Local/Detail/AutoSimulator/Tests/Utils.hh>

namespace
{

typedef ::wg::autosimulator::detail::auto_any_group const & auto_any_group_t;
using ::wg::autosimulator::detail::test::ExprGenerator;

}

using namespace ::wg::autosimulator;

TEST(wg_autosimulator_detail_autoanygroup, IsRValue)
{
  ExprGenerator expr;

  bool autosimFlag = false;

#define EXPR \
  (expr.array())                (expr.constArray())     \
  (expr.copyonlyMutableRValue()) (expr.copyonlyConstRValue())  \
  (expr.copyonlyMutableLValue())  (expr.copyonlyConstLValue()) \
  (expr.moveonlyMutableRValue()) (expr.moveonlyMutableLValue())

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

TEST(wg_autosimulator_detail_autoanygroup_custom, IsRValue)
{
  ExprGenerator expr;

  bool autosimFlag = false;

#define EXPR \
  (expr.array())                (expr.constArray())     \
  (expr.copyonlyMutableRValue()) (expr.copyonlyConstRValue())  \
  (expr.copyonlyMutableLValue())  (expr.copyonlyConstLValue()) \
  (expr.moveonlyMutableRValue()) (expr.moveonlyMutableLValue())

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

#undef EXPR
}
