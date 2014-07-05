#include <gtest/gtest.h>
#include <WG/Local/Detail/AutoSimulator/Detail/AutoAnyGroup.hh>

namespace
{

typedef ::wg::autosimulator::detail::auto_any_group const & auto_any_group_t;

typedef int A5[5];
typedef A5 const ConstA5;

struct Cntr
{
  Cntr()
  : value(11)
  {
  }

  int value;
};

Cntr mutableRValue()
{
  return Cntr();
}

Cntr const constRValue()
{
  return Cntr();
}

Cntr & mutableLValue()
{
  static Cntr toRet;
  return toRet;
}

Cntr const & constLValue()
{
  static Cntr toRet;
  return toRet;
}

}

using namespace ::wg::autosimulator;

TEST(wg_autosimulator_detail_autoanygroup, IsRValue)
{
  A5 arr = {1, 2, 3, 4, 5};
  ConstA5 carr = {11, 12, 13, 14, 15};;

  bool isRValue = false;

#define EXPR \
  (arr)             (carr)              ( mutableRValue() ) \
  ( constRValue() ) ( mutableLValue() ) ( constLValue() )

  auto_any_group_t grp = WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_MAKEGROUP(EXPR);
  WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_INITGROUP(grp, isRValue, EXPR);

  EXPECT_FALSE( WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_ITEM_ISRVALUE(grp, 0, EXPR) );
  EXPECT_FALSE( WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_ITEM_ISRVALUE(grp, 1, EXPR) );
  EXPECT_TRUE( WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_ITEM_ISRVALUE(grp, 2, EXPR) );
  EXPECT_TRUE( WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_ITEM_ISRVALUE(grp, 3, EXPR) );
  EXPECT_FALSE( WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_ITEM_ISRVALUE(grp, 4, EXPR) );
  EXPECT_FALSE( WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_ITEM_ISRVALUE(grp, 5, EXPR) );

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
  A5 arr = {1, 2, 3, 4, 5};
  ConstA5 carr = {11, 12, 13, 14, 15};;

  bool isRValue = false;

#define EXPR \
  (arr)             (carr)              ( mutableRValue() ) \
  ( constRValue() ) ( mutableLValue() ) ( constLValue() )

  CustomBase const & grp =
    WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_MAKECUSTOMGROUP(CustomBase, EXPR);
  WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_INITGROUP(grp, isRValue, EXPR);

  EXPECT_FALSE( WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_ITEM_ISRVALUE(grp, 0, EXPR) );
  EXPECT_FALSE( WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_ITEM_ISRVALUE(grp, 1, EXPR) );
  EXPECT_TRUE( WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_ITEM_ISRVALUE(grp, 2, EXPR) );
  EXPECT_TRUE( WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_ITEM_ISRVALUE(grp, 3, EXPR) );
  EXPECT_FALSE( WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_ITEM_ISRVALUE(grp, 4, EXPR) );
  EXPECT_FALSE( WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_ITEM_ISRVALUE(grp, 5, EXPR) );

#undef EXPR
}
