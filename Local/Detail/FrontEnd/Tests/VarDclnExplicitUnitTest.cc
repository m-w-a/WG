#include <WG/Local/Detail/Tests/test.h>
#include <WG/Local/Detail/PP.hh>
#include <WG/Local/Detail/BackEnd/Type.hh>
#include "../VarDclnExplicit.hh"
#include <boost/preprocessor.hpp>
#include <boost/typeof/typeof.hpp>

/*
//Unit Tests.
#define VDE1 (T const * ) var1
#define VDE2 local(U) var2
#define VDE3 localref(Callback &) var3

WG_PP_VARDCLNEXPLICIT_TUPLIZE(VDE1)
WG_PP_VARDCLNEXPLICIT_TUPLIZE(VDE2)
WG_PP_VARDCLNEXPLICIT_TUPLIZE(VDE3)

//EXPECTED:
//(T const *) (var1)
//(local(U) (var2)
//(localref(Callback &)) (var3)
*/

#define EXTRACT_PARSEDTYPE(explicit_var_dcln) \
  BOOST_PP_SEQ_ELEM(0, explicit_var_dcln)
#define EXTRACT_VAR(explicit_var_dcln) \
  BOOST_PP_SEQ_ELEM(1, explicit_var_dcln)

#define TEST_DIDCAPTURE_TYPE(expected, actual) \
  TEST_TYPE_IS_SAME(expected, WG_PP_PARSEDTYPE_EXTRACTCPPTYPE(actual))
#define TEST_TYPE_IS_SAME(expected, actual) \
  struct BOOST_PP_CAT(test_type_did_bind, __LINE__) \
  { \
    void test() \
    { \
      typedef void (*expected_fptr_type)(expected param1); \
      typedef void (*actual_fptr_type)(actual param1); \
      expected_fptr_type expected_fptr = 0; \
      actual_fptr_type actual_fptr = 0; \
      expected_fptr = actual_fptr; \
    } \
  };

#define TEST_DIDCAPTURE_OBJ(expected, actual) \
  TEST_OBJNAME_IS_SAME(expected, actual)
#define TEST_OBJNAME_IS_SAME(expected, actual) \
  struct BOOST_PP_CAT(test_obj_did_bind, __LINE__) \
  { \
    int expected; \
    void operator()() \
    { \
      (void)actual; \
    } \
  };

struct SomeGlobalType {};
void testNonLocal()
{
  SomeGlobalType * obj;

#define RESULT WG_PP_VARDCLNEXPLICIT_TUPLIZE((SomeGlobalType const *) obj)
  TEST_DIDCAPTURE_TYPE(BOOST_TYPEOF(*obj) const *, EXTRACT_PARSEDTYPE(RESULT))
  TEST_DIDCAPTURE_OBJ(obj, EXTRACT_VAR(RESULT))
#undef RESULT
}

void testLocalNonRef()
{
  struct SomeLocalType {} obj;
  (void)obj;

#define RESULT WG_PP_VARDCLNEXPLICIT_TUPLIZE(local(SomeLocalType) obj)
  TEST_DIDCAPTURE_TYPE(SomeLocalType, EXTRACT_PARSEDTYPE(RESULT))
  TEST_DIDCAPTURE_OBJ(obj, EXTRACT_VAR(RESULT))
#undef RESULT
}

void testLocalRef()
{
  struct SomeLocalType {} obj;
  (void)obj;

#define RESULT WG_PP_VARDCLNEXPLICIT_TUPLIZE(localref(SomeLocalType const &) obj)
  TEST_DIDCAPTURE_TYPE(SomeLocalType const &, EXTRACT_PARSEDTYPE(RESULT))
  TEST_DIDCAPTURE_OBJ(obj, EXTRACT_VAR(RESULT))
#undef RESULT
}
