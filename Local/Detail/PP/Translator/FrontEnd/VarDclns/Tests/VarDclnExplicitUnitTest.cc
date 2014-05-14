#include <WG/Local/Tests/Utils/PreprocessorUnitTester.hh>
#include <WG/Local/Detail/PP/Tests/Util.hh>
#include <WG/Local/Detail/PP/PP.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/TypeExtractor.hh>
#include "../VarDclnExplicit.hh"
#include <boost/preprocessor.hpp>
#include <boost/typeof/typeof.hpp>
#include <WG/Local/Detail/PP/Translator/Markers.hh>

//Unit Tests.
#define SG1 type(SomeGlobalType const *) sgvar1
#define SL1 lcltype(SomeLocalType *) slvar1
#define SL2 lcltype(SomeLocalType *) const slvar2
#define SL3 lcltype(SomeLocalType *) ref slvar3
#define SL4 lcltype(SomeLocalType *) const ref slvar4
/*
WG_PP_VARDCLN_EXPLICIT_TUPLIZE(SG1, 0)
WG_PP_VARDCLN_EXPLICIT_TUPLIZE(SL1, 0)
WG_PP_VARDCLN_EXPLICIT_TUPLIZE(SL2, 0)
WG_PP_VARDCLN_EXPLICIT_TUPLIZE(SL3, 0)
WG_PP_VARDCLN_EXPLICIT_TUPLIZE(SL4, 0)
WG_PP_VARDCLN_EXPLICIT_TUPLIZE(SPE1, 0)
WG_PP_VARDCLN_EXPLICIT_TUPLIZE(SPE2, 0)
WG_PP_VARDCLN_EXPLICIT_TUPLIZE(SPE3, 1)

//EXPECTED:
//(WG_PP_NOOP type(SomeGlobalType const) ) (sgvar1)
//(WG_PP_NOOP lcltype(SomeLocalType *) ) (slvar1)
//(WG_PP_NOOP lcltype(SomeLocalType *) ) (const) ) (slvar2)
//(WG_PP_NOOP lcltype(SomeLocalType *) ) (ref) ) (slvar3)
//(WG_PP_NOOP lcltype(SomeLocalType *) ) (const)(ref) ) (slvar4)
//(WG_PP_NOOP type(int)) (spevar1)
*/

//-----
//Utils
//-----

#define EXTRACT_PARSEDTYPE(explicittype_var_2tuple) \
  WG_PP_TRNSLTR_MARKERS_EATHEADMARKER( \
    BOOST_PP_SEQ_ELEM(0, explicittype_var_2tuple) )

#define EXTRACT_VAR(explicittype_var_2tuple) \
  BOOST_PP_SEQ_ELEM(1, explicittype_var_2tuple)

#define TEST_DIDCAPTURE_TYPE(expected, actual) \
  WG_PP_TESTS_UTIL_ISSAMETYPE(expected, WG_PP_PARSEDTYPE_EXTRACTCPPTYPE(actual))

#define TEST_DIDCAPTURE_OBJ(expected, actual) \
  WG_PP_TESTS_UTIL_ISSAMEOBJNAME(expected, actual)

//-----
//Tests
//-----

struct SomeGlobalType {};
void testNonLocal()
{
  SomeGlobalType * sgvar1;

#define RESULT WG_PP_VARDCLN_EXPLICIT_TUPLIZE(SG1, 0)
  TEST_DIDCAPTURE_TYPE(BOOST_TYPEOF(*sgvar1) const *, EXTRACT_PARSEDTYPE(RESULT))
  TEST_DIDCAPTURE_OBJ(sgvar1, EXTRACT_VAR(RESULT))
#undef RESULT
}

void testLocalNoQual()
{
  struct SomeLocalType {} slvar1;
  (void)slvar1;

#define RESULT WG_PP_VARDCLN_EXPLICIT_TUPLIZE(SL1, 0)
  TEST_DIDCAPTURE_TYPE(SomeLocalType *, EXTRACT_PARSEDTYPE(RESULT))
  TEST_DIDCAPTURE_OBJ(slvar1, EXTRACT_VAR(RESULT))
#undef RESULT
}

void testConstQual()
{
  struct SomeLocalType {} slvar2;
  (void)slvar2;

#define RESULT WG_PP_VARDCLN_EXPLICIT_TUPLIZE(SL2, 0)
  TEST_DIDCAPTURE_TYPE(SomeLocalType * const, EXTRACT_PARSEDTYPE(RESULT))
  TEST_DIDCAPTURE_OBJ(slvar2, EXTRACT_VAR(RESULT))
#undef RESULT
}

void testLocalRefQual()
{
  struct SomeLocalType {} slvar3;
  (void)slvar3;

#define RESULT WG_PP_VARDCLN_EXPLICIT_TUPLIZE(SL3, 0)
  TEST_DIDCAPTURE_TYPE(SomeLocalType * &, EXTRACT_PARSEDTYPE(RESULT))
  TEST_DIDCAPTURE_OBJ(slvar3, EXTRACT_VAR(RESULT))
#undef RESULT
}

void testLocalConstRefQual()
{
  struct SomeLocalType {} slvar4;
  (void)slvar4;

#define RESULT WG_PP_VARDCLN_EXPLICIT_TUPLIZE(SL4, 0)
  TEST_DIDCAPTURE_TYPE(SomeLocalType * const &, EXTRACT_PARSEDTYPE(RESULT))
  TEST_DIDCAPTURE_OBJ(slvar4, EXTRACT_VAR(RESULT))
#undef RESULT
}
