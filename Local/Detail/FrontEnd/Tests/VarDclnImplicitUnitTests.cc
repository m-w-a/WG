#include <WG/Local/Detail/Tests/test.h>
#include <WG/Local/Detail/PP.hh>
#include "../VarDclnImplicit.hh"
#include <boost/preprocessor.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/type_traits/is_same.hpp>

//Unit Tests.
#define VDI1 var1
#define VDI2 ref var2
#define VDI3 const var3
#define VDI4 const ref var4
#define VDI5 this_
#define VDI6 const this_

//WG_PP_VARDCLNIMPLICIT_TUPLIZE(VDI1)
//WG_PP_VARDCLNIMPLICIT_TUPLIZE(VDI2)
//WG_PP_VARDCLNIMPLICIT_TUPLIZE(VDI3)
//WG_PP_VARDCLNIMPLICIT_TUPLIZE(VDI4)
//WG_PP_VARDCLNIMPLICIT_TUPLIZE(VDI5)
//WG_PP_VARDCLNIMPLICIT_TUPLIZE(VDI6)

//EXPECTED:
//( BOOST_TYPEOF(var4) ) (var4)
//( boost::add_reference< BOOST_TYPEOF(var5) >::type ) (var5)
//( boost::add_const< BOOST_TYPEOF(var6) >::type ) (var6)
//( boost::add_reference<boost::add_const< BOOST_TYPEOF(var7) >::type>::type ) (var7)

#define TEST_TYPE(expected, actual) \
  TEST_TYPE2(expected, WG_PP_TOKENS_EATHEADTOKEN_WG_PP_DEDUCEDTYPE(actual))
#define TEST_TYPE2(expected, actual) \
  BEGIN \
    boost::is_same<expected, actual>::value == true \
  END

#define TEST_OBJ(expected, actual) \
  struct BOOST_PP_CAT(test_obj_bound, __LINE__) \
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

#define RESULT WG_PP_VARDCLNIMPLICIT_TUPLIZE(var1)
  TEST_TYPE( BOOST_TYPEOF(var1), BOOST_PP_SEQ_ELEM(0, RESULT) )
  TEST_OBJ( var1, BOOST_PP_SEQ_ELEM(1, RESULT) )
#undef RESULT
}

void testConstQualBind()
{
  int var1 = 0;

  using namespace boost;
#define RESULT WG_PP_VARDCLNIMPLICIT_TUPLIZE(const var1)
  TEST_TYPE(
    add_const<BOOST_TYPEOF(var1)>::type, BOOST_PP_SEQ_ELEM(0, RESULT) )
  TEST_OBJ( var1, BOOST_PP_SEQ_ELEM(1, RESULT) )
#undef RESULT
}

void testRefQualBind()
{
  int var1 = 0;

  using namespace boost;
#define RESULT WG_PP_VARDCLNIMPLICIT_TUPLIZE(ref var1)
  TEST_TYPE(
    add_reference<BOOST_TYPEOF(var1)>::type, BOOST_PP_SEQ_ELEM(0, RESULT) )
  TEST_OBJ( var1, BOOST_PP_SEQ_ELEM(1, RESULT) )
#undef RESULT
}

void testConstRefBind()
{
  int var1 = 0;

  using namespace boost;
#define RESULT WG_PP_VARDCLNIMPLICIT_TUPLIZE(const ref var1)
  TEST_TYPE(
    add_reference<add_const<BOOST_TYPEOF(var1)>::type>::type,
    BOOST_PP_SEQ_ELEM(0, RESULT) )
  TEST_OBJ( var1, BOOST_PP_SEQ_ELEM(1, RESULT) )
#undef RESULT
}

struct testNoQualThisU
{
  void operator()()
  {
    using namespace boost;
#define RESULT WG_PP_VARDCLNIMPLICIT_TUPLIZE(this_)
    TEST_TYPE(
      BOOST_TYPEOF(this),
      BOOST_PP_SEQ_ELEM(0, RESULT) )
    TEST_OBJ( this_, BOOST_PP_SEQ_ELEM(1, RESULT) )
#undef RESULT
  }
};

struct testConstQualThisU
{
  void operator()()
  {
    using namespace boost;
#define RESULT WG_PP_VARDCLNIMPLICIT_TUPLIZE(const this_)
    TEST_TYPE(
      add_const<BOOST_TYPEOF(*this)>::type * const,
      BOOST_PP_SEQ_ELEM(0, RESULT) )
    TEST_OBJ( this_, BOOST_PP_SEQ_ELEM(1, RESULT) )
#undef RESULT
  }
};
