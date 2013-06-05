#include <WG/Local/Detail/Tests/test.h>
#include <WG/Local/Detail/Tests/TestHelper.hh>
#include <WG/Local/Detail/PP.hh>
#include <WG/Local/Detail/BackEnd/Type.hh>
#include "../VarDclnExplicit.hh"
#include <boost/preprocessor.hpp>
#include <boost/typeof/typeof.hpp>


//Unit Tests.
#define VDE1 (SomeGlobalType const *) var1
#define VDE2 local(SomeLocalType) var2
#define VDE3 localref(SomeLocalType const &) var3
/*
WG_PP_VARDCLNEXPLICIT_TUPLIZE(VDE1)
WG_PP_VARDCLNEXPLICIT_TUPLIZE(VDE2)
WG_PP_VARDCLNEXPLICIT_TUPLIZE(VDE3)

//EXPECTED:
//(SomeGlobalType const *) (var1)
//(local(SomeLocalType) (var2)
//(localref(SomeLocalType const &)) (var3)
*/

#define EXTRACT_PARSEDTYPE(explicittype_var_2tuple) \
  BOOST_PP_SEQ_ELEM(0, explicittype_var_2tuple)

#define EXTRACT_VAR(explicittype_var_2tuple) \
  BOOST_PP_SEQ_ELEM(1, explicittype_var_2tuple)

#define TEST_DIDCAPTURE_TYPE(expected, actual) \
  WG_PP_TESTHELPER_IS_SAME_TYPE(expected, WG_PP_PARSEDTYPE_EXTRACTCPPTYPE(actual))

#define TEST_DIDCAPTURE_OBJ(expected, actual) \
  WG_PP_TESTHELPER_IS_SAME_OBJ_NAME(expected, actual)

struct SomeGlobalType {};
void testNonLocal()
{
  SomeGlobalType * var1;

#define RESULT WG_PP_VARDCLNEXPLICIT_TUPLIZE(VDE1)
  TEST_DIDCAPTURE_TYPE(BOOST_TYPEOF(*var1) const *, EXTRACT_PARSEDTYPE(RESULT))
  TEST_DIDCAPTURE_OBJ(var1, EXTRACT_VAR(RESULT))
#undef RESULT
}

void testLocalNonRef()
{
  struct SomeLocalType {} var2;
  (void)var2;

#define RESULT WG_PP_VARDCLNEXPLICIT_TUPLIZE(VDE2)
  TEST_DIDCAPTURE_TYPE(SomeLocalType, EXTRACT_PARSEDTYPE(RESULT))
  TEST_DIDCAPTURE_OBJ(var2, EXTRACT_VAR(RESULT))
#undef RESULT
}

void testLocalRef()
{
  struct SomeLocalType {} var3;
  (void)var3;

#define RESULT WG_PP_VARDCLNEXPLICIT_TUPLIZE(VDE3)
  TEST_DIDCAPTURE_TYPE(SomeLocalType const &, EXTRACT_PARSEDTYPE(RESULT))
  TEST_DIDCAPTURE_OBJ(var3, EXTRACT_VAR(RESULT))
#undef RESULT
}
