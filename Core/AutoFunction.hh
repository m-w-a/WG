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

#define WG_INTERNAL_IDENTITY(x) x

#define WG_INTERNAL_FORMAT_NAME(name) \
  BOOST_PP_CAT(WG_INTERNAL_IDENTITY(pgcllXXXautofunctionXXX), name)

#define WG_INTERNAL_TOKEN_MATCHES_this_ (1) /* unary */
#define WG_INTERNAL_TOKEN_IS_THISU(tokens) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            WG_INTERNAL_TOKEN_MATCHES_)

#define WG_INTERNAL_IS_SEQ_COUNT_EVEN(seq) \
  BOOST_PP_NOT(BOOST_PP_MOD(BOOST_PP_SEQ_SIZE(seq), 2))

#define WG_INTERNAL_IS_INDEX_ODD(indx) BOOST_PP_MOD(indx,2)
#define WG_INTERNAL_IS_INDEX_EVEN(indx) \
  BOOST_PP_NOT(WG_INTERNAL_IS_INDEX_ODD(indx))

#define WG_INTERNAL_IS_SEQ_INDEX_LAST(seq_count, indx) \
  BOOST_PP_EQUAL(seq_count, BOOST_PP_INC(indx))

// BOOST_PP_SEQ_FOR_EACH_I functor.
#define WG_INTERNAL_SEQUENCE_IF_EVEN(r, data, indx, elem) \
  BOOST_PP_IF( \
    WG_INTERNAL_IS_INDEX_EVEN(indx), \
    BOOST_PP_LPAREN() elem BOOST_PP_RPAREN(), \
    BOOST_PP_EMPTY())

// BOOST_PP_SEQ_FOR_EACH_I functor.
#define WG_INTERNAL_SEQUENCE_IF_ODD(r, data, indx, elem) \
  BOOST_PP_IF( \
    WG_INTERNAL_IS_INDEX_ODD(indx), \
    BOOST_PP_LPAREN() elem BOOST_PP_RPAREN(), \
    BOOST_PP_EMPTY())
    
#define \
  WG_INTERNAL_BPSEQ_TO_TYPESEQ(bp_seq) \
    BOOST_PP_SEQ_FOR_EACH_I(WG_INTERNAL_SEQUENCE_IF_EVEN, ~, bp_seq)
    
#define \
  WG_INTERNAL_BPSEQ_TO_OBJSEQ(bp_seq) \
    BOOST_PP_SEQ_FOR_EACH_I(WG_INTERNAL_SEQUENCE_IF_ODD, ~, bp_seq)

#define WG_INTERNAL_ADDREFERENCE(sometype) \
  boost::add_reference<WG_INTERNAL_IDENTITY(sometype)>::type
#define WG_INTERNAL_ADDCONST(sometype) \
  boost::add_const<WG_INTERNAL_IDENTITY(sometype)>::type

// BOOST_PP_SEQ_FOR_EACH_I functor.
#define \
  WG_INTERNAL_FORM_PARAM_ENTRY( \
    r, obj_seq, indx, elem) \
      BOOST_PP_IF( \
        WG_INTERNAL_TOKEN_IS_THISU(BOOST_PP_SEQ_ELEM(indx, obj_seq)), \
        WG_INTERNAL_ADDCONST(elem), \
        WG_INTERNAL_IDENTITY(elem)) \
      BOOST_PP_SEQ_ELEM(indx, obj_seq) \
      BOOST_PP_COMMA_IF( \
        BOOST_PP_NOT(WG_INTERNAL_IS_SEQ_INDEX_LAST( \
          BOOST_PP_SEQ_SIZE(obj_seq), \
          indx)))

#define WG_INTERNAL_BPSEQ_TO_PARAMLIST(bp_seq) \
  BOOST_PP_LPAREN() \
    BOOST_PP_SEQ_FOR_EACH_I( \
      WG_INTERNAL_FORM_PARAM_ENTRY, \
      WG_INTERNAL_BPSEQ_TO_OBJSEQ(bp_seq), \
      WG_INTERNAL_BPSEQ_TO_TYPESEQ(bp_seq)) \
  BOOST_PP_RPAREN()
  
// BOOST_PP_SEQ_FOR_EACH_I functor.
#define \
  WG_INTERNAL_QUALIFY_TYPE(r, obj_seq, indx, elem) \
    BOOST_PP_IF( \
      WG_INTERNAL_TOKEN_IS_THISU(BOOST_PP_SEQ_ELEM(indx, obj_seq)), \
      WG_INTERNAL_ADDREFERENCE(WG_INTERNAL_ADDCONST(elem)), \
      WG_INTERNAL_ADDREFERENCE(elem)) \
    BOOST_PP_COMMA_IF( \
      BOOST_PP_NOT( \
        WG_INTERNAL_IS_SEQ_INDEX_LAST(BOOST_PP_SEQ_SIZE(obj_seq), indx)))

// BOOST_PP_SEQ_FOR_EACH_I functor
#define \
  WG_INTERNAL_APPEND_COMMA_AND_REPLACE_KEYWORDS(r, seq_count, indx, elem) \
    BOOST_PP_IF( \
      WG_INTERNAL_TOKEN_IS_THISU(elem), \
      WG_INTERNAL_IDENTITY(this), \
      elem) \
    BOOST_PP_COMMA_IF( \
      BOOST_PP_NOT( \
        WG_INTERNAL_IS_SEQ_INDEX_LAST(seq_count, indx)))

#define WG_INTERNAL_PARAMPROXYTYPE() \
  WG_INTERNAL_FORMAT_NAME(param_proxy_type)
#define WG_INTERNAL_PARAMPROXYOBJ() \
  WG_INTERNAL_FORMAT_NAME(param_proxy)
#define WG_INTERNAL_BPSEQ_TO_PARAMPROXYDCLN(bp_seq) \
  typedef boost::tuple< \
    BOOST_PP_SEQ_FOR_EACH_I( \
      WG_INTERNAL_QUALIFY_TYPE, \
      WG_INTERNAL_BPSEQ_TO_OBJSEQ(bp_seq), \
      WG_INTERNAL_BPSEQ_TO_TYPESEQ(bp_seq)) \
  > WG_INTERNAL_PARAMPROXYTYPE() WG_INTERNAL_IDENTITY(;) \
  WG_INTERNAL_PARAMPROXYTYPE() WG_INTERNAL_PARAMPROXYOBJ() \
    BOOST_PP_LPAREN() \
      BOOST_PP_SEQ_FOR_EACH_I( \
        WG_INTERNAL_APPEND_COMMA_AND_REPLACE_KEYWORDS, \
        BOOST_PP_SEQ_SIZE(WG_INTERNAL_BPSEQ_TO_OBJSEQ(bp_seq)), \
        WG_INTERNAL_BPSEQ_TO_OBJSEQ(bp_seq)) \
    BOOST_PP_RPAREN() WG_INTERNAL_IDENTITY(;)

#define WG_INTERNAL_AUTOFUNCTOR_PARAMPROXYOBJ() param_proxy
    
// BOOST_PP_SEQ_FOR_EACH_I functor
#define \
  WG_INTERNAL_ELEM_ACCESS_VIA_PARAMPROXYOBJ(r, seq_count, indx, elem) \
    WG_INTERNAL_AUTOFUNCTOR_PARAMPROXYOBJ()WG_INTERNAL_IDENTITY(.)WG_INTERNAL_IDENTITY(elem) \
    BOOST_PP_COMMA_IF( \
      BOOST_PP_NOT( \
        WG_INTERNAL_IS_SEQ_INDEX_LAST(seq_count, indx)))
        
#define WG_INTERNAL_BPSEQ_TO_PARAMPROXYACCESSLIST(obj_seq) \
  BOOST_PP_SEQ_FOR_EACH_I( \
    WG_INTERNAL_ELEM_ACCESS_VIA_PARAMPROXYOBJ, \
    BOOST_PP_SEQ_SIZE(obj_seq), \
    obj_seq)
    
#define WG_INTERNAL_AUTOFUNCTOR_START(function_name, bp_seq) \
  struct WG_INTERNAL_IDENTITY(function_name) \
  { \
    void operator()( \
      WG_INTERNAL_PARAMPROXYTYPE() & \
        WG_INTERNAL_AUTOFUNCTOR_PARAMPROXYOBJ()) \
    { \
      this->call( \
        WG_INTERNAL_BPSEQ_TO_PARAMPROXYACCESSLIST( \
          WG_INTERNAL_BPSEQ_TO_OBJSEQ(bp_seq)) \
            ); \
    } \
    void WG_INTERNAL_IDENTITY(call) WG_INTERNAL_BPSEQ_TO_PARAMLIST(bp_seq)
    
#define WG_INTERNAL_AUTOFUNCTOR_END() \
  } WG_INTERNAL_FORMAT_NAME(auto_functor)() \
    BOOST_PP_LPAREN() \
      WG_INTERNAL_PARAMPROXYOBJ() \
    BOOST_PP_RPAREN() WG_INTERNAL_IDENTITY(;)

//-----------
//Public APIs
//-----------
    
#define WG_AUTOFUNCTION(function_name, bound_param_seq) \
  { \
    WG_INTERNAL_BPSEQ_TO_PARAMPROXYDCLN(bound_param_seq) \
    WG_INTERNAL_AUTOFUNCTOR_START(function_name, bound_param_seq)
    
#define WG_AUTOFUNCTION_END() \
  WG_INTERNAL_AUTOFUNCTOR_END() \
  }
    

//TESTS Begin
    
#define TEST_SEQ (w)(x)(y)(z)(a)(b)(c)(d)(class)(this_)

WG_AUTOFUNCTION(foo, TEST_SEQ)
{
}
WG_AUTOFUNCTION_END()

//TODO
//1) Add ASSERT_MSG for even sized sequences.

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