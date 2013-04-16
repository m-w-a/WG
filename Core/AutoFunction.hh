 #include <boost/preprocessor.hpp>
 #include <boost/local_function/detail/preprocessor/keyword/facility/is.hpp>
// #include <boost/type_traits/add_reference.hpp> //TODO
// #include <boost/type_traits/add_const.hpp> //TODO
// #include <boost/tuple/tuple.hpp> //TODO

//-----------
//Public APIs
//-----------

///@brief bound_param_seq
///@brief   an even-numbered sequence of visible unqualified variable names and
///@brief   their associated types that will automatically be bound via 
///@brief   reference as parameters to function_name. If said variables should
///@brief   be constant, then their associated types should be declared as 
///@brief   such.
///@brief   Note: variable named "this_" is reserved and is used to auto-bind
///@brief     "this" variable.
///@brief   This param should be specified in the following format:
///@brief     (type1)(var1) (type2)(var2) ... (typeN)(varN)
#define WG_AUTOFUNCTION(function_name, bound_param_seq) \
  BOOST_PP_ASSERT_MSG( \
    WG_INTERNAL_IS_SEQ_COUNT_EVEN(bound_param_seq), \
    "Error: 2nd parameter to WG_AUTOFUNCTION should be even numbered sequence.") \
  { \
    WG_INTERNAL_BPSEQ_TO_PARAMPROXYDCLN(bound_param_seq) \
    WG_INTERNAL_AUTOFUNCTOR_START(function_name, bound_param_seq)
    
#define WG_AUTOFUNCTION_END() \
  WG_INTERNAL_AUTOFUNCTOR_END() \
  }

//-----------
//Impl Macros
//-----------
  
#define WG_INTERNAL_IDENTITY(x) x

#define WG_INTERNAL_FORMAT_NAME(name) \
  BOOST_PP_CAT(WG_INTERNAL_IDENTITY(pgcllXXXautofunctionXXX), name)

#define WG_INTERNAL_TOKEN_MATCHES_this_ (1) /* unary */
#define WG_INTERNAL_TOKENS_STARTS_WITH_THISU(tokens) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            WG_INTERNAL_TOKEN_MATCHES_)

#define WG_INTERNAL_IS_SEQ_COUNT_EVEN(seq) \
  BOOST_PP_NOT(BOOST_PP_MOD(BOOST_PP_SEQ_SIZE(seq), 2))
#define WG_INTERNAL_IS_SEQ_COUNT_ODD(seq) \
  BOOST_PP_NOT(WG_INTERNAL_IS_SEQ_COUNT_EVEN(seq))

#define WG_INTERNAL_IS_ODD(num) BOOST_PP_MOD(num,2)
#define WG_INTERNAL_IS_EVEN(num) \
  BOOST_PP_NOT(WG_INTERNAL_IS_ODD(num))

#define WG_INTERNAL_IS_SEQ_INDEX_LAST(seq_count, indx) \
  BOOST_PP_EQUAL(seq_count, BOOST_PP_INC(indx))

// BOOST_PP_SEQ_FOR_EACH_I functor.
#define WG_INTERNAL_SEQUENCE_IF_INDEX_EVEN(r, data, indx, elem) \
  BOOST_PP_IF( \
    WG_INTERNAL_IS_EVEN(indx), \
    BOOST_PP_LPAREN() elem BOOST_PP_RPAREN(), \
    BOOST_PP_EMPTY())

// BOOST_PP_SEQ_FOR_EACH_I functor.
#define WG_INTERNAL_SEQUENCE_IF_INDEX_ODD(r, data, indx, elem) \
  BOOST_PP_IF( \
    WG_INTERNAL_IS_ODD(indx), \
    BOOST_PP_LPAREN() elem BOOST_PP_RPAREN(), \
    BOOST_PP_EMPTY())
    
#define \
  WG_INTERNAL_BPSEQ_TO_TYPESEQ(bp_seq) \
    BOOST_PP_SEQ_FOR_EACH_I(WG_INTERNAL_SEQUENCE_IF_INDEX_EVEN, ~, bp_seq)
    
#define \
  WG_INTERNAL_BPSEQ_TO_OBJSEQ(bp_seq) \
    BOOST_PP_SEQ_FOR_EACH_I(WG_INTERNAL_SEQUENCE_IF_INDEX_ODD, ~, bp_seq)

#define WG_INTERNAL_ADDREFERENCE(sometype) \
  boost::add_reference<WG_INTERNAL_IDENTITY(sometype)>::type
#define WG_INTERNAL_ADDCONST(sometype) \
  boost::add_const<WG_INTERNAL_IDENTITY(sometype)>::type

// BOOST_PP_SEQ_FOR_EACH_I functor.
#define \
  WG_INTERNAL_FORM_PARAM_ENTRY( \
    r, obj_seq, indx, elem) \
      BOOST_PP_IF( \
        WG_INTERNAL_TOKENS_STARTS_WITH_THISU(BOOST_PP_SEQ_ELEM(indx, obj_seq)), \
        WG_INTERNAL_ADDREFERENCE(WG_INTERNAL_ADDCONST(elem)), \
        WG_INTERNAL_ADDREFERENCE(elem)) \
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
      WG_INTERNAL_TOKENS_STARTS_WITH_THISU(BOOST_PP_SEQ_ELEM(indx, obj_seq)), \
      WG_INTERNAL_ADDREFERENCE(WG_INTERNAL_ADDCONST(elem)), \
      WG_INTERNAL_ADDREFERENCE(elem)) \
    BOOST_PP_COMMA_IF( \
      BOOST_PP_NOT( \
        WG_INTERNAL_IS_SEQ_INDEX_LAST(BOOST_PP_SEQ_SIZE(obj_seq), indx)))

// BOOST_PP_SEQ_FOR_EACH_I functor
#define \
  WG_INTERNAL_APPEND_COMMA_AND_REPLACE_KEYWORDS(r, seq_count, indx, elem) \
    BOOST_PP_IF( \
      WG_INTERNAL_TOKENS_STARTS_WITH_THISU(elem), \
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
    WG_INTERNAL_AUTOFUNCTOR_PARAMPROXYOBJ().get<WG_INTERNAL_IDENTITY(indx)>() \
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
    

//TESTS Begin

#define TEST_SEQ (w)(x)(y)(z)(a)(b)(c)(d)(class)(this_)

WG_AUTOFUNCTION(foo, TEST_SEQ)
{
}
WG_AUTOFUNCTION_END()
