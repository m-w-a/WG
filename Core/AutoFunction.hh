/*
#define ... BOOST_PP_IF( \
    ..., \
    (x)BOOST_PP_COMMA, \
    y)()
*/


#include <boost/preprocessor.hpp>
#include <boost/local_function/detail/preprocessor/keyword/facility/is.hpp>
//#include <boost/type_traits/add_reference.hpp> //TODO
//#include <boost/type_traits/add_const.hpp> //TODO
//#include <boost/tuple/tuple.hpp> //TODO

#define PGCLL_INTERNAL_IDENTITY(x) x

#define PGCLL_INTERNAL_FORMAT_NAME(name) \
  BOOST_PP_CAT(PGCLL_INTERNAL_IDENTITY(pgcllXXXautofunctionXXX), name)

#define PGCLL_INTERNAL_TOKEN_MATCHES_this_ (1) /* unary */
#define PGCLL_INTERNAL_TOKEN_IS_THISU(tokens) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            PGCLL_INTERNAL_TOKEN_MATCHES_)

#define PGCLL_INTERNAL_IS_SEQ_COUNT_EVEN(seq) \
  BOOST_PP_NOT(BOOST_PP_MOD(BOOST_PP_SEQ_SIZE(seq), 2))

#define PGCLL_INTERNAL_IS_INDEX_ODD(indx) BOOST_PP_MOD(indx,2)
#define PGCLL_INTERNAL_IS_INDEX_EVEN(indx) \
  BOOST_PP_NOT(PGCLL_INTERNAL_IS_INDEX_ODD(indx))

#define PGCLL_INTERNAL_IS_SEQ_INDEX_LAST(seq_count, indx) \
  BOOST_PP_EQUAL(seq_count, BOOST_PP_INC(indx))

// BOOST_PP_SEQ_FOR_EACH_I functor.
#define \
  PGCLL_INTERNAL_APPEND_COMMA_IF_INDEXODD_AND_NOTLAST( \
    r, seq_count, indx, elem) \
      elem \
      BOOST_PP_COMMA_IF( \
        BOOST_PP_AND( \
          BOOST_PP_NOT(PGCLL_INTERNAL_IS_INDEX_EVEN(indx)), \
          BOOST_PP_NOT(PGCLL_INTERNAL_IS_SEQ_INDEX_LAST(seq_count, indx))))

#define PGCLL_INTERNAL_SEQ_TO_PARAMLIST(bp_seq) \
  BOOST_PP_LPAREN() \
    BOOST_PP_SEQ_FOR_EACH_I( \
      PGCLL_INTERNAL_APPEND_COMMA_IF_INDEXODD_AND_NOTLAST, \
      BOOST_PP_SEQ_SIZE(bp_seq), \
      bp_seq) \
  BOOST_PP_RPAREN()

// BOOST_PP_SEQ_FOR_EACH_I functor.
#define PGCLL_INTERNAL_SEQUENCE_IF_EVEN(r, data, indx, elem) \
  BOOST_PP_IF( \
    PGCLL_INTERNAL_IS_INDEX_EVEN(indx), \
    BOOST_PP_LPAREN() elem BOOST_PP_RPAREN(), \
    BOOST_PP_EMPTY())

// BOOST_PP_SEQ_FOR_EACH_I functor.
#define PGCLL_INTERNAL_SEQUENCE_IF_ODD(r, data, indx, elem) \
  BOOST_PP_IF( \
    PGCLL_INTERNAL_IS_INDEX_ODD(indx), \
    BOOST_PP_LPAREN() elem BOOST_PP_RPAREN(), \
    BOOST_PP_EMPTY())
    
#define \
  PGCLL_INTERNAL_SEQ_TO_TYPESEQ(bp_seq) \
    BOOST_PP_SEQ_FOR_EACH_I(PGCLL_INTERNAL_SEQUENCE_IF_EVEN, ~, bp_seq)
    
#define \
  PGCLL_INTERNAL_SEQ_TO_OBJSEQ(bp_seq) \
    BOOST_PP_SEQ_FOR_EACH_I(PGCLL_INTERNAL_SEQUENCE_IF_ODD, ~, bp_seq)

#define PGCLL_INTERNAL_ADDREFERENCE(sometype) \
  boost::add_reference<PGCLL_INTERNAL_IDENTITY(sometype)>::type
#define PGCLL_INTERNAL_ADDCONST(sometype) \
  boost::add_const<PGCLL_INTERNAL_IDENTITY(sometype)>::type

// BOOST_PP_SEQ_FOR_EACH_I functor.
#define \
  PGCLL_INTERNAL_QUALIFY_TYPE(r, obj_seq, indx, elem) \
    BOOST_PP_IF( \
      PGCLL_INTERNAL_TOKEN_IS_THISU(BOOST_PP_SEQ_ELEM(indx, obj_seq)), \
      PGCLL_INTERNAL_ADDREFERENCE(PGCLL_INTERNAL_ADDCONST(elem)), \
      PGCLL_INTERNAL_ADDREFERENCE(elem)) \
    BOOST_PP_COMMA_IF( \
      BOOST_PP_NOT( \
        PGCLL_INTERNAL_IS_SEQ_INDEX_LAST(BOOST_PP_SEQ_SIZE(obj_seq), indx)))

// BOOST_PP_SEQ_FOR_EACH_I functor
#define \
  PGCLL_INTERNAL_APPEND_COMMA_AND_REPLACE_KEYWORDS(r, seq_count, indx, elem) \
    BOOST_PP_IF( \
      PGCLL_INTERNAL_TOKEN_IS_THISU(elem), \
      PGCLL_INTERNAL_IDENTITY(this), \
      elem) \
    BOOST_PP_COMMA_IF( \
      BOOST_PP_NOT( \
        PGCLL_INTERNAL_IS_SEQ_INDEX_LAST(seq_count, indx)))

#define PGCLL_INTERNAL_PARAMPROXYTYPE() \
  PGCLL_INTERNAL_FORMAT_NAME(param_proxy_type)
#define PGCLL_INTERNAL_PARAMPROXYOBJ() \
  PGCLL_INTERNAL_FORMAT_NAME(param_proxy)
#define PGCLL_INTERNAL_SEQ_TO_PARAMPROXYDCLN(bp_seq) \
  typedef boost::tuple< \
    BOOST_PP_SEQ_FOR_EACH_I( \
      PGCLL_INTERNAL_QUALIFY_TYPE, \
      PGCLL_INTERNAL_SEQ_TO_OBJSEQ(bp_seq), \
      PGCLL_INTERNAL_SEQ_TO_TYPESEQ(bp_seq)) \
  > PGCLL_INTERNAL_PARAMPROXYTYPE() PGCLL_INTERNAL_IDENTITY(;) \
  PGCLL_INTERNAL_PARAMPROXYTYPE() PGCLL_INTERNAL_PARAMPROXYOBJ() \
    BOOST_PP_LPAREN() \
      BOOST_PP_SEQ_FOR_EACH_I( \
        PGCLL_INTERNAL_APPEND_COMMA_AND_REPLACE_KEYWORDS, \
        BOOST_PP_SEQ_SIZE(PGCLL_INTERNAL_SEQ_TO_OBJSEQ(bp_seq)), \
        PGCLL_INTERNAL_SEQ_TO_OBJSEQ(bp_seq)) \
    BOOST_PP_RPAREN() PGCLL_INTERNAL_IDENTITY(;)

#define PGCLL_INTERNAL_AUTOFUNCTOR_PARAMPROXYOBJ() param_proxy
    
// BOOST_PP_SEQ_FOR_EACH_I functor
#define \
  PGCLL_INTERNAL_ELEM_ACCESS_VIA_PARAMPROXYOBJ(r, seq_count, indx, elem) \
    PGCLL_INTERNAL_AUTOFUNCTOR_PARAMPROXYOBJ()PGCLL_INTERNAL_IDENTITY(.)PGCLL_INTERNAL_IDENTITY(elem) \
    BOOST_PP_COMMA_IF( \
      BOOST_PP_NOT( \
        PGCLL_INTERNAL_IS_SEQ_INDEX_LAST(seq_count, indx)))
        
#define PGCLL_INTERNAL_SEQ_TO_PARAMPROXYACCESSLIST(obj_seq) \
  BOOST_PP_SEQ_FOR_EACH_I( \
    PGCLL_INTERNAL_ELEM_ACCESS_VIA_PARAMPROXYOBJ, \
    BOOST_PP_SEQ_SIZE(obj_seq), \
    obj_seq)
    
#define PGCLL_INTERNAL_AUTOFUNCTOR_START(function_name, bp_seq) \
  struct PGCLL_INTERNAL_IDENTITY(function_name) \
  { \
    void operator()( \
      PGCLL_INTERNAL_PARAMPROXYTYPE() & \
        PGCLL_INTERNAL_AUTOFUNCTOR_PARAMPROXYOBJ()) \
    { \
      this->call( \
        PGCLL_INTERNAL_SEQ_TO_PARAMPROXYACCESSLIST( \
          PGCLL_INTERNAL_SEQ_TO_OBJSEQ(bp_seq)) \
            ); \
    } \
    void PGCLL_INTERNAL_IDENTITY(call) PGCLL_INTERNAL_SEQ_TO_PARAMLIST(bp_seq)
    
#define PGCLL_INTERNAL_AUTOFUNCTOR_END() \
  } PGCLL_INTERNAL_FORMAT_NAME(auto_functor)() \
    BOOST_PP_LPAREN() \
      PGCLL_INTERNAL_PARAMPROXYOBJ() \
    BOOST_PP_RPAREN() PGCLL_INTERNAL_IDENTITY(;)

//-----------
//Public APIs
//-----------
    
#define PGCLL_AUTOFUNCTION(function_name, bound_param_seq) \
  { \
    PGCLL_INTERNAL_SEQ_TO_PARAMPROXYDCLN(bound_param_seq) \
    PGCLL_INTERNAL_AUTOFUNCTOR_START(function_name, bound_param_seq)
    
#define PGCLL_AUTOFUNCTION_END() \
  PGCLL_INTERNAL_AUTOFUNCTOR_END() \
  }
    

//TESTS Begin
    
#define TEST_SEQ (w)(x)(y)(z)(a)(b)(c)(d)(class)(this_)

PGCLL_AUTOFUNCTION(foo, TEST_SEQ)
{
}
PGCLL_AUTOFUNCTION_END()

//#define MACRO(z, n, text) z n text - 
//BOOST_PP_REPEAT(3, MACRO, class)

/*
#define EVEN_INDEX(indx) BOOST_PP_MOD(BOOST_PP_DEC(indx),2)
#define WRAP(r, data, elem) \
  BOOST_PP_LPAREN_IF(EVEN_INDEX(r)) \
  elem \
  BOOST_PP_COMMA_IF(EVEN_INDEX(r)) \
  BOOST_PP_RPAREN_IF(BOOST_PP_NOT(EVEN_INDEX(r)))

BOOST_PP_SEQ_FOR_EACH(WRAP, ~, SEQ)
*/

int main()
{  
  return 0;
}