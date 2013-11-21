//#include <gtest/gtest.h>
//#include <WG/GTest/Exceptions.hh>
#include <boost/type_traits/is_base_of.hpp>
#include <WG/Local/LclClass.hh>
#include "BaseClasses.hh"

TEST(wg_lclclass_derives, OkIfPublic)
{
  try
  {
    WG_LCLCLASS(public_derived_t, derives (public base1) )
    WG_LCLCLASS_END;

    EXPECT_TRUE(boost::is_base_of<base1, public_derived_t>::value)
  }
  WG_GTEST_CATCH
}

TEST(wg_lclclass_derives, OkIfProtected)
{
  try
  {
    WG_LCLCLASS(protected_derived_t, derives (protected base1) )
    WG_LCLCLASS_END;

    EXPECT_TRUE(boost::is_base_of<base1, public_derived_t>::value)
  }
  WG_GTEST_CATCH
}

TEST(wg_lclclass_derives, OkIfPrivate)
{
  try
  {
    WG_LCLCLASS(private_derived_t, derives (private base1) )
    WG_LCLCLASS_END;

    EXPECT_TRUE(boost::is_base_of<base1, public_derived_t>::value)
  }
  WG_GTEST_CATCH
}

TEST(wg_lclclass_derives, OkIfVirtual)
{
  try
  {
    struct local_base_t : public virtual base1
    {};

    WG_LCLCLASS(virtual_derived_t, derives (virtual base1) )
    WG_LCLCLASS_END;

    EXPECT_TRUE(boost::is_base_of<base1, public_derived_t>::value)
  }
  WG_GTEST_CATCH
}

TEST(wg_lclclass_derives, OkIfAccessUnspecified)
{
  try
  {
    WG_LCLCLASS(accessunspecified_derived_t, derives (base1) )
    WG_LCLCLASS_END;

    EXPECT_TRUE(boost::is_base_of<base1, public_derived_t>::value)
  }
  WG_GTEST_CATCH
}

TEST(wg_lclclass_derives, OkIfAllCombo)
{
  try
  {
    WG_LCLCLASS
    (allcombo_derived_t,
     derives
       (public base1) (protected base2) (private base3) (virtual base4) (base5)
    )
    WG_LCLCLASS_END;

    EXPECT_TRUE(boost::is_base_of<base1, public_derived_t>::value)
    EXPECT_TRUE(boost::is_base_of<base12, public_derived_t>::value)
    EXPECT_TRUE(boost::is_base_of<base3, public_derived_t>::value)
    EXPECT_TRUE(boost::is_base_of<base4, public_derived_t>::value)
    EXPECT_TRUE(boost::is_base_of<base5, public_derived_t>::value)
  }
  WG_GTEST_CATCH
}
