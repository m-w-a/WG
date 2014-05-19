#include <gtest/gtest.h>
#include <WG/Local/LclClass.hh>

namespace
{
struct base1 { char a; };
struct base2 { short b; };
struct base3 { int c; };
struct base4 { long d; };
struct base5 { char * e; };
}

TEST(wg_lclclass_derives, OkIfPublic)
{
  WG_LCLCLASS(public_derived_t, derives (public base1) )
  WG_LCLCLASS_END;

  public_derived_t  obj;
  base1 * is_base_of = &obj;
  (void)is_base_of;
}

TEST(wg_lclclass_derives, OkIfProtected)
{
  WG_LCLCLASS(protected_derived_t, derives (protected base1) )
  WG_LCLCLASS_END;

  struct final_dervied_t : private protected_derived_t
  {
    void test()
    {
      protected_derived_t * base = this;
      // Tests base-of because implicit casting works.
      // Tests protected derivation because implicit casting worked in a
      // derived class of protected_derived_t.
      base1 * is_protected_base_of = base;
      (void)is_protected_base_of;
    }
  };
}

TEST(wg_lclclass_derives, OkIfPrivate)
{
  WG_LCLCLASS(private_derived_t, derives (private base1) )
    void test()
    {
      base1 * is_base_of = this;
      (void)is_base_of;
    }
  WG_LCLCLASS_END;
}

TEST(wg_lclclass_derives, OkIfVirtual)
{
  struct local_base_t : public virtual base1
  {};

  WG_LCLCLASS
  (virtual_derived_t, derives (public local_base_t) (public virtual base1) )
  WG_LCLCLASS_END;

  virtual_derived_t obj;
  // Tests virtual inheritance.
  // If not derived virtually, then ambigous compiler error will result.
  (void)obj.a;
}

TEST(wg_lclclass_derives, OkIfAccessUnspecified)
{
  WG_LCLCLASS(accessunspecified_derived_t, derives (base1) )
    void test()
    {
      base1 * is_base_of = this;
      (void)is_base_of;
    }
  WG_LCLCLASS_END;
}

TEST(wg_lclclass_derives, OkIfAllCombo)
{
  WG_LCLCLASS
  (allcombo_derived_t,
   derives
     (public base1) (protected base2) (private base3) (virtual base4) (base5)
  )
    void test()
    {
      { base3 * is_base_of = this; (void)is_base_of; }
      { base4 * is_base_of = this; (void)is_base_of; }
      { base5 * is_base_of = this; (void)is_base_of; }
    }
  WG_LCLCLASS_END;

  struct final_dervied_t : private allcombo_derived_t
  {
    void test()
    {
      allcombo_derived_t * base = this;
      // Tests base-of because implicit casting works.
      // Tests protected derivation because implicit casting worked in a
      // derived class of allcombo_derived_t.
      base2 * is_protected_base_of = base;
      (void)is_protected_base_of;
    }
  };

  allcombo_derived_t obj;
  base1 * is_base_of = &obj;
  (void)is_base_of;
}
