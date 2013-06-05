#include <WG/Local/Detail/Tests/test.h>
#include <WG/Local/Detail/PP.hh>
#include "../VarDclnImplicit.hh"
#include <boost/preprocessor.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/type_traits/is_same.hpp>

//Unit Tests.
#define VDI1 var1
#define VDI2 const var2
#define VDI3 ref var3
#define VDI4 const ref var4
#define VDI5 this_
#define VDI6 const this_
/*
WG_PP_VARDCLNIMPLICIT_TUPLIZE(VDI1)
WG_PP_VARDCLNIMPLICIT_TUPLIZE(VDI2)
WG_PP_VARDCLNIMPLICIT_TUPLIZE(VDI3)
WG_PP_VARDCLNIMPLICIT_TUPLIZE(VDI4)
WG_PP_VARDCLNIMPLICIT_TUPLIZE(VDI5)
WG_PP_VARDCLNIMPLICIT_TUPLIZE(VDI6)

//EXPECTED:
//( BOOST_TYPEOF(var4) ) (var1)
//( add_const< BOOST_TYPEOF(var6) >::type ) (var2)
//( add_reference< BOOST_TYPEOF(var5) >::type ) (var3)
//( add_reference<add_const< BOOST_TYPEOF(var4) >::type>::type ) (var4)
//( BOOST_TYPEOF(this) ) (this_)
//( add_const<add_pointer<add_const<BOOST_TYPEOF(*this)>::type>::type>::type ) (this_)
*/

#define EXTRACT_TYPE(implicittype_var_2tuple) \
  BOOST_PP_SEQ_ELEM(0, implicittype_var_2tuple)

#define EXTRACT_VAR(implicittype_var_2tuple) \
  BOOST_PP_SEQ_ELEM(1, implicittype_var_2tuple)

#define TEST_DIDBIND_TYPE(expected, actual) \
  TEST_DIDBIND_TYPE2(expected, WG_PP_TOKENS_EATHEADTOKEN_WG_PP_DEDUCEDTYPE(actual))
#define TEST_DIDBIND_TYPE2(expected, actual) \
  BEGIN \
    boost::is_same<expected, actual>::value == true \
  END

#define TEST_DIDBIND_OBJ(expected, actual) \
  struct BOOST_PP_CAT(test_obj_did_bound, __LINE__) \
  { \
    int expected; \
    void operator()() \
    { \
      (void)actual; \
    } \
  };

void testNoQualBind()
{
  int var1 = 0;

#define RESULT WG_PP_VARDCLNIMPLICIT_TUPLIZE(VDI1)
  TEST_DIDBIND_TYPE( BOOST_TYPEOF(var1), EXTRACT_TYPE(RESULT) )
  TEST_DIDBIND_OBJ( var1, EXTRACT_VAR(RESULT) )
#undef RESULT
}

void testConstQualBind()
{
  int var2 = 0;

  using namespace boost;
#define RESULT WG_PP_VARDCLNIMPLICIT_TUPLIZE(VDI2)
  TEST_DIDBIND_TYPE(
    add_const<BOOST_TYPEOF(var2)>::type, EXTRACT_TYPE(RESULT) )
  TEST_DIDBIND_OBJ( var2, EXTRACT_VAR(RESULT) )
#undef RESULT
}

void testRefQualBind()
{
  int var3 = 0;

  using namespace boost;
#define RESULT WG_PP_VARDCLNIMPLICIT_TUPLIZE(VDI3)
  TEST_DIDBIND_TYPE(
    add_reference<BOOST_TYPEOF(var3)>::type, EXTRACT_TYPE(RESULT) )
  TEST_DIDBIND_OBJ( var3, EXTRACT_VAR(RESULT) )
#undef RESULT
}

void testConstRefBind()
{
  int var4 = 0;

  using namespace boost;
#define RESULT WG_PP_VARDCLNIMPLICIT_TUPLIZE(VDI4)
  TEST_DIDBIND_TYPE(
    add_reference<add_const<BOOST_TYPEOF(var4)>::type>::type,
    EXTRACT_TYPE(RESULT) )
  TEST_DIDBIND_OBJ( var4, EXTRACT_VAR(RESULT) )
#undef RESULT
}

struct testNoQualThisU
{
  void operator()()
  {
    using namespace boost;
#define RESULT WG_PP_VARDCLNIMPLICIT_TUPLIZE(VDI5)
    TEST_DIDBIND_TYPE(
      BOOST_TYPEOF(this),
      EXTRACT_TYPE(RESULT) )
    TEST_DIDBIND_OBJ( this_, EXTRACT_VAR(RESULT) )
#undef RESULT
  }
};

struct testConstQualThisU
{
  void operator()()
  {
    using namespace boost;
#define RESULT WG_PP_VARDCLNIMPLICIT_TUPLIZE(VDI6)
    TEST_DIDBIND_TYPE(
      add_const<BOOST_TYPEOF(*this)>::type * const,
      EXTRACT_TYPE(RESULT) )
    TEST_DIDBIND_OBJ( this_, EXTRACT_VAR(RESULT) )
#undef RESULT
  }
};
