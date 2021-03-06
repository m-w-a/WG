#include <WG/Local/Tests/Utils/PreprocessorUnitTester.hh>
#include <WG/Local/Detail/PP/PP.hh>
#include <WG/Local/Detail/PP/Translator/FrontEnd/VarDclns/VarDclnImplicit.hh>
#include <boost/preprocessor.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/type_traits/is_same.hpp>
#include <WG/Local/Detail/PP/Translator/Markers.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/TypeExtractor.hh>

//Unit Tests.
#define VDI1 var1
#define VDI2 const var2
#define VDI3 ref var3
#define VDI4 const ref var4
#define VDI5 this_
#define VDI6 const this_

#define VDI101 var1, 101
#define VDI102 const var2, "Hello World!"
#define VDI104 const ref var4, 10.5f + 1
#define VDI105 this_ , pSomeObj
#define VDI106 ref this_ , someObj
#define VDI107 const this_ , pSomeObj
#define VDI108 const ref this_ , someObj

/*
RESCAN_WG_PP_VARDCLN_IMPLICIT_TUPLIZE_BOUNDDCLN(VDI1)
RESCAN_WG_PP_VARDCLN_IMPLICIT_TUPLIZE_BOUNDDCLN(VDI2)
RESCAN_WG_PP_VARDCLN_IMPLICIT_TUPLIZE_BOUNDDCLN(VDI3)
RESCAN_WG_PP_VARDCLN_IMPLICIT_TUPLIZE_BOUNDDCLN(VDI4)
RESCAN_WG_PP_VARDCLN_IMPLICIT_TUPLIZE_BOUNDDCLN(VDI5)
RESCAN_WG_PP_VARDCLN_IMPLICIT_TUPLIZE_BOUNDDCLN(VDI6)

//EXPECTED:
//( WG_PP_DEDUCEDTYPE type( BOOST_TYPEOF(var4) ) ) (var1)
//( WG_PP_DEDUCEDTYPE type( add_const< BOOST_TYPEOF(var6) >::type ) ) (var2)
//( WG_PP_DEDUCEDTYPE type( add_reference< BOOST_TYPEOF(var5) >::type ) ) (var3)
//( WG_PP_DEDUCEDTYPE type( add_reference<add_const< BOOST_TYPEOF(var4) >::type>::type ) ) (var4)
//( WG_PP_DEDUCEDTYPE type( BOOST_TYPEOF(this) const) ) (this_)
//( WG_PP_DEDUCEDTYPE type( add_const<add_pointer<add_const<BOOST_TYPEOF(*this)>::type>::type>::type ) ) (this_)
*/

//------
//Utils.
//------

#define EXTRACT_TYPE(implicittype_var_2tuple) \
  WG_PP_PARSEDTYPE_EXTRACTCPPTYPE( \
    WG_PP_TRNSLTR_MARKERS_EATHEADMARKER( \
      BOOST_PP_SEQ_ELEM(0, implicittype_var_2tuple) ))

#define EXTRACT_VAR(implicittype_var_2tuple) \
  BOOST_PP_SEQ_ELEM(1, implicittype_var_2tuple)

#define TEST_DIDBIND_TYPE(expected, actual) \
  TEST_DIDBIND_TYPE2(expected, actual)
#define TEST_DIDBIND_TYPE2(expected, actual) \
  BEGIN \
    ::boost::is_same<expected, actual>::value == true \
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

//------
//Tests.
//------

#define RESCAN_WG_PP_VARDCLN_IMPLICIT_TUPLIZE_BOUNDDCLN(x) \
  WG_PP_VARDCLN_IMPLICIT_TUPLIZE_BOUNDDCLN(x, 0)

void testNoQualBind()
{
  int var1 = 0;

#define RESULT RESCAN_WG_PP_VARDCLN_IMPLICIT_TUPLIZE_BOUNDDCLN(VDI1)
  TEST_DIDBIND_TYPE( BOOST_TYPEOF(var1), EXTRACT_TYPE(RESULT) )
  TEST_DIDBIND_OBJ( var1, EXTRACT_VAR(RESULT) )
#undef RESULT
}

void testConstQualBind()
{
  int var2 = 0;

  using namespace ::boost;
#define RESULT RESCAN_WG_PP_VARDCLN_IMPLICIT_TUPLIZE_BOUNDDCLN(VDI2)
  TEST_DIDBIND_TYPE(
    add_const<BOOST_TYPEOF(var2)>::type, EXTRACT_TYPE(RESULT) )
  TEST_DIDBIND_OBJ( var2, EXTRACT_VAR(RESULT) )
#undef RESULT
}

void testRefQualBind()
{
  int var3 = 0;

  using namespace ::boost;
#define RESULT RESCAN_WG_PP_VARDCLN_IMPLICIT_TUPLIZE_BOUNDDCLN(VDI3)
  TEST_DIDBIND_TYPE(
    add_reference<BOOST_TYPEOF(var3)>::type, EXTRACT_TYPE(RESULT) )
  TEST_DIDBIND_OBJ( var3, EXTRACT_VAR(RESULT) )
#undef RESULT
}

void testConstRefBind()
{
  int var4 = 0;

  using namespace ::boost;
#define RESULT RESCAN_WG_PP_VARDCLN_IMPLICIT_TUPLIZE_BOUNDDCLN(VDI4)
  TEST_DIDBIND_TYPE(
    add_reference<add_const<BOOST_TYPEOF(var4)>::type>::type,
    EXTRACT_TYPE(RESULT) )
  TEST_DIDBIND_OBJ( var4, EXTRACT_VAR(RESULT) )
#undef RESULT
}

struct testNoQualThisUBind
{
  void operator()()
  {
    using namespace ::boost;
#define RESULT RESCAN_WG_PP_VARDCLN_IMPLICIT_TUPLIZE_BOUNDDCLN(VDI5)
    TEST_DIDBIND_TYPE(
      BOOST_TYPEOF(this) const,
      EXTRACT_TYPE(RESULT) )
    TEST_DIDBIND_OBJ( this_, EXTRACT_VAR(RESULT) )
#undef RESULT
  }
};

struct testConstQualThisUBind
{
  void operator()()
  {
    using namespace ::boost;
#define RESULT RESCAN_WG_PP_VARDCLN_IMPLICIT_TUPLIZE_BOUNDDCLN(VDI6)
    TEST_DIDBIND_TYPE(
      add_const<BOOST_TYPEOF(*this)>::type * const,
      EXTRACT_TYPE(RESULT) )
    TEST_DIDBIND_OBJ( this_, EXTRACT_VAR(RESULT) )
#undef RESULT
  }
};

#define RESCAN_WG_PP_VARDCLN_IMPLICIT_TUPLIZE_SETDCLN(x) \
  WG_PP_VARDCLN_IMPLICIT_TUPLIZE_SETDCLN(x, 0)

void testValueExprNoQual()
{
#define RESULT RESCAN_WG_PP_VARDCLN_IMPLICIT_TUPLIZE_SETDCLN(VDI101)
  TEST_DIDBIND_TYPE( int, EXTRACT_TYPE(RESULT) )
  TEST_DIDBIND_OBJ(var1, EXTRACT_VAR(RESULT))
#undef RESULT
}

void testValueExprConstQual()
{
#define RESULT RESCAN_WG_PP_VARDCLN_IMPLICIT_TUPLIZE_SETDCLN(VDI102)
  TEST_DIDBIND_TYPE( BOOST_TYPEOF("Hello World!") const, EXTRACT_TYPE(RESULT) )
  TEST_DIDBIND_OBJ(var2, EXTRACT_VAR(RESULT))
#undef RESULT
}

void testValueExprConstRefQual()
{
#define RESULT RESCAN_WG_PP_VARDCLN_IMPLICIT_TUPLIZE_SETDCLN(VDI104)
  TEST_DIDBIND_TYPE( float const &, EXTRACT_TYPE(RESULT) )
  TEST_DIDBIND_OBJ(var4, EXTRACT_VAR(RESULT))
#undef RESULT
}

struct SomeClass {};

void testValueExprThisUNotSpecialAndCanSetToNonThisNamedVar()
{
  SomeClass * pSomeObj = 0;

#define RESULT RESCAN_WG_PP_VARDCLN_IMPLICIT_TUPLIZE_SETDCLN(VDI105)
  TEST_DIDBIND_TYPE( SomeClass *, EXTRACT_TYPE(RESULT) )
  TEST_DIDBIND_OBJ(this_, EXTRACT_VAR(RESULT))
#undef RESULT
}

void testValueExprThisUNotSpecialAndCanBeRef()
{
  SomeClass someObj;

#define RESULT RESCAN_WG_PP_VARDCLN_IMPLICIT_TUPLIZE_SETDCLN(VDI106)
  TEST_DIDBIND_TYPE( SomeClass &, EXTRACT_TYPE(RESULT) )
  TEST_DIDBIND_OBJ(this_, EXTRACT_VAR(RESULT))
#undef RESULT
}

void testValueExprThisUNotSpecialAndConstOnlyAppliesToOuterType()
{
  SomeClass * pSomeObj = 0;

#define RESULT RESCAN_WG_PP_VARDCLN_IMPLICIT_TUPLIZE_SETDCLN(VDI107)
  TEST_DIDBIND_TYPE( SomeClass * const, EXTRACT_TYPE(RESULT) )
  TEST_DIDBIND_OBJ(this_, EXTRACT_VAR(RESULT))
#undef RESULT
}

void testValueExprThisUNotSpecialAndCanBeConstRef()
{
  SomeClass someObj;

#define RESULT RESCAN_WG_PP_VARDCLN_IMPLICIT_TUPLIZE_SETDCLN(VDI108)
  TEST_DIDBIND_TYPE( SomeClass const &, EXTRACT_TYPE(RESULT) )
  TEST_DIDBIND_OBJ(this_, EXTRACT_VAR(RESULT))
#undef RESULT
}
