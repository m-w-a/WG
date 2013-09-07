#include <WG/Local/Tests/test.h>
#include <WG/Local/Tests/TestHelper.hh>
#include <WG/Local/Detail/PP.hh>
#include <WG/Local/Detail/BackEnd/TypeExtractor.hh>
#include "../VarDclnExplicit.hh"
#include <boost/preprocessor.hpp>
#include <boost/typeof/typeof.hpp>

//Unit Tests.
#define SG1 (SomeGlobalType const *) sgvar1
#define SL1 local(SomeLocalType *) slvar1
#define SL2 local(SomeLocalType *) const slvar2
#define SL3 local(SomeLocalType *) ref slvar3
#define SL4 local(SomeLocalType *) const ref slvar4
/*
WG_PP_VARDCLN_EXPLICIT_TUPLIZE(SG1)
WG_PP_VARDCLN_EXPLICIT_TUPLIZE(SL1)
WG_PP_VARDCLN_EXPLICIT_TUPLIZE(SL2)
WG_PP_VARDCLN_EXPLICIT_TUPLIZE(SL3)
WG_PP_VARDCLN_EXPLICIT_TUPLIZE(SL4)

//EXPECTED:
//(SomeGlobalType const) (sgvar1)
//( local(SomeLocalType *) ) (slvar1)
//( local(SomeLocalType *) (const) ) (slvar2)
//( local(SomeLocalType *) (ref) ) (slvar3)
//( local(SomeLocalType *) (const)(ref) ) (slvar4)
*/

//-----
//Utils
//-----

#define EXTRACT_PARSEDTYPE(explicittype_var_2tuple) \
  BOOST_PP_SEQ_ELEM(0, explicittype_var_2tuple)

#define EXTRACT_VAR(explicittype_var_2tuple) \
  BOOST_PP_SEQ_ELEM(1, explicittype_var_2tuple)

#define TEST_DIDCAPTURE_TYPE(expected, actual) \
  WG_PP_TESTHELPER_IS_SAME_TYPE(expected, WG_PP_PARSEDTYPE_EXTRACTCPPTYPE(actual))

#define TEST_DIDCAPTURE_OBJ(expected, actual) \
  WG_PP_TESTHELPER_IS_SAME_OBJ_NAME(expected, actual)

//-----
//Tests
//-----

struct SomeGlobalType {};
void testNonLocal()
{
  SomeGlobalType * sgvar1;

#define RESULT WG_PP_VARDCLN_EXPLICIT_TUPLIZE(SG1)
  TEST_DIDCAPTURE_TYPE(BOOST_TYPEOF(*sgvar1) const *, EXTRACT_PARSEDTYPE(RESULT))
  TEST_DIDCAPTURE_OBJ(sgvar1, EXTRACT_VAR(RESULT))
#undef RESULT
}

void testLocalNoQual()
{
  struct SomeLocalType {} slvar1;
  (void)slvar1;

#define RESULT WG_PP_VARDCLN_EXPLICIT_TUPLIZE(SL1)
  TEST_DIDCAPTURE_TYPE(SomeLocalType *, EXTRACT_PARSEDTYPE(RESULT))
  TEST_DIDCAPTURE_OBJ(slvar1, EXTRACT_VAR(RESULT))
#undef RESULT
}

void testConstQual()
{
  struct SomeLocalType {} slvar2;
  (void)slvar2;

#define RESULT WG_PP_VARDCLN_EXPLICIT_TUPLIZE(SL2)
  TEST_DIDCAPTURE_TYPE(SomeLocalType * const, EXTRACT_PARSEDTYPE(RESULT))
  TEST_DIDCAPTURE_OBJ(slvar2, EXTRACT_VAR(RESULT))
#undef RESULT
}

void testLocalRefQual()
{
  struct SomeLocalType {} slvar3;
  (void)slvar3;

#define RESULT WG_PP_VARDCLN_EXPLICIT_TUPLIZE(SL3)
  TEST_DIDCAPTURE_TYPE(SomeLocalType * &, EXTRACT_PARSEDTYPE(RESULT))
  TEST_DIDCAPTURE_OBJ(slvar3, EXTRACT_VAR(RESULT))
#undef RESULT
}

void testLocalConstRefQual()
{
  struct SomeLocalType {} slvar4;
  (void)slvar4;

#define RESULT WG_PP_VARDCLN_EXPLICIT_TUPLIZE(SL4)
  TEST_DIDCAPTURE_TYPE(SomeLocalType * const &, EXTRACT_PARSEDTYPE(RESULT))
  TEST_DIDCAPTURE_OBJ(slvar4, EXTRACT_VAR(RESULT))
#undef RESULT
}
