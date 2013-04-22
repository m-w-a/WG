 #include <boost/preprocessor.hpp>
 #include <boost/local_function/detail/preprocessor/keyword/facility/is.hpp>
//TODO
// #include <boost/type_traits/add_const.hpp>
// #include <boost/type_traits/add_reference.hpp>
// #include <boost/tuple/tuple.hpp>

//###########
//Public APIs
//###########

///@brief bound_param_seq
///@brief   1) an even-numbered sequence of visible unqualified variable names
///@brief   and their associated types that will automatically be bound
///@brief   as parameters to function_name. If said variables should
///@brief   be constant, then their associated types should be declared as 
///@brief   such.
///@brief   Note: variable named "this_" is reserved and is used to auto-bind
///@brief     "this" variable.
///@brief   This param should be specified in the following format:
///@brief     (type1)(var1) (type2)(var2) ... (typeN)(varN)
///@brief   2) or, the token: "(void)", to signify the absence of any variables
///@brief   to bind.
///@brief
///@brief  assigned_param_seq
///@brief   1) an even-numbered sequence of variables, their associated types,
///@brief   and their assigned values which will be passed as additional
///@brief   parameters to function_name. Said triple should be specified in the
///@brief   following format:
///@brief     (type1)(var1, assigned_val1) (type2)(var2, assigned_val2) ...
///@brief   2) or, the token: "(void)", to signify the absence of any additional
///@brief   variables.
#define WG_AUTOFUNCTION(function_name, bound_param_seq, assigned_param_seq) \
  WG_PP_AUTOFUNCTION( \
    function_name, \
    WG_PP_MAKE_PSEQ(bound_param_seq, assigned_param_seq))
    
#define WG_AUTOFUNCTION_END() \
  WG_PP_AUTOFUNCTION_END()

//##########
//Impl Macros
//###########
  
//------------
//Basic Tools.
//------------
  
#define WG_PP_IDENTITY(x) x
#define WG_PP_IDENTITY_1(x) WG_PP_IDENTITY(x)
#define WG_PP_IDENTITY_2(x, y) x y

#define WG_PP_FORMAT_NAME(name) \
  BOOST_PP_CAT(WG_PP_IDENTITY(pgcllXXXautofunctionXXX), name)

#define WG_PP_TOKEN_MATCHES_WG_PP_TRUE (1) /* unary */
#define WG_PP_TOKENS_START_WITH_WG_PP_TRUE(tokens) \
  BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT( \
    tokens, \
    WG_PP_TOKEN_MATCHES_)

#define WG_PP_TOKEN_MATCHES_this_ (1) /* unary */
#define WG_PP_TOKENS_STARTS_WITH_THISU(tokens) \
  BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT( \
    tokens, \
    WG_PP_TOKEN_MATCHES_)

#define WG_PP_ADDCONST(sometype) \
  boost::add_const<WG_PP_IDENTITY(sometype)>::type
#define WG_PP_ADDREFERENCE(sometype) \
  boost::add_reference<WG_PP_IDENTITY(sometype)>::type
  
#define WG_PP_IS_ODD(num) BOOST_PP_MOD(num,2)
#define WG_PP_IS_EVEN(num) \
  BOOST_PP_NOT(WG_PP_IS_ODD(num))

#define WG_PP_IS_MOD3_R0(num) \
  BOOST_PP_EQUAL(BOOST_PP_MOD(num,3), 0)
#define WG_PP_IS_MOD3_R1(num) \
  BOOST_PP_EQUAL(BOOST_PP_MOD(num,3), 1)
#define WG_PP_IS_MOD3_R2(num) \
  BOOST_PP_EQUAL(BOOST_PP_MOD(num,3), 2)

#define WG_PP_SEQ_IS_NOT_NIL_IMPL(seq) WG_PP_TRUE
#define WG_PP_SEQ_IS_NOT_NIL(seq) \
  WG_PP_TOKENS_START_WITH_WG_PP_TRUE( \
    BOOST_PP_EXPAND(WG_PP_SEQ_IS_NOT_NIL_IMPL seq))

#define WG_PP_SEQ_ENUM_0(seq)
#define WG_PP_SEQ_ENUM_1(seq) BOOST_PP_SEQ_ENUM(seq)
#define WG_PP_SEQ_ENUM(seq) \
  BOOST_PP_EXPAND( \
    BOOST_PP_CAT(WG_PP_SEQ_ENUM_, WG_PP_SEQ_IS_NOT_NIL(seq)))(seq)

#define WG_PP_SEQ_REPLACE_0(seq, indx, elem)
#define WG_PP_SEQ_REPLACE_1(seq, indx, elem) \
  BOOST_PP_SEQ_REPLACE(seq, indx, elem)
#define WG_PP_SEQ_REPLACE(seq, indx, elem) \
  BOOST_PP_EXPAND( \
    BOOST_PP_CAT( \
      WG_PP_SEQ_REPLACE_, \
      WG_PP_SEQ_IS_NOT_NIL(seq)) \
    (seq, indx, elem))

#define WG_PP_IS_SEQ_COUNT_EVEN(seq) \
  BOOST_PP_NOT(BOOST_PP_MOD(BOOST_PP_SEQ_SIZE(seq), 2))

#define WG_PP_IS_SEQ_COUNT_ODD(seq) \
  BOOST_PP_NOT(WG_PP_IS_SEQ_COUNT_EVEN(seq))
  
#define WG_PP_IS_SEQ_INDEX_LAST(seq_count, indx) \
  BOOST_PP_EQUAL(seq_count, BOOST_PP_INC(indx))

//------------------------
//AssignedPSeq & BoundPSeq
//------------------------

// BOOST_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_SEQUENCE_IF_INDEX(r, CONDITION, indx, elem) \
  BOOST_PP_EXPR_IF( \
    CONDITION(indx), \
    BOOST_PP_LPAREN() elem BOOST_PP_RPAREN())
    
#define \
  WG_PP_BOUNDPSEQ_TO_TYPESEQ(bp_seq) \
    BOOST_PP_SEQ_FOR_EACH_I( \
      WG_PP_SEQUENCE_IF_INDEX, \
      WG_PP_IS_EVEN, \
      bp_seq)
    
#define \
  WG_PP_BOUNDPSEQ_TO_OBJSEQ(bp_seq) \
    BOOST_PP_SEQ_FOR_EACH_I( \
      WG_PP_SEQUENCE_IF_INDEX, \
      WG_PP_IS_ODD, \
      bp_seq)

#define \
  WG_PP_ASSIGNEDPSEQ_TO_TYPESEQ(ap_seq) \
    BOOST_PP_SEQ_FOR_EACH_I( \
      WG_PP_SEQUENCE_IF_INDEX, \
      WG_PP_IS_MOD3_R0, \
      ap_seq)
      
#define \
  WG_PP_ASSIGNEDPSEQ_TO_OBJSEQ(ap_seq) \
    BOOST_PP_SEQ_FOR_EACH_I( \
      WG_PP_SEQUENCE_IF_INDEX, \
      WG_PP_IS_MOD3_R1, \
      ap_seq)

#define \
  WG_PP_ASSIGNEDPSEQ_TO_VALUESEQ(ap_seq) \
    BOOST_PP_SEQ_FOR_EACH_I( \
      WG_PP_SEQUENCE_IF_INDEX, \
      WG_PP_IS_MOD3_R2, \
      ap_seq)

// BOOST_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_MARK_THISU_INDX(r, data, indx, elem) \
  BOOST_PP_EXPR_IF( \
    WG_PP_TOKENS_STARTS_WITH_THISU(elem), \
    (indx))

#define WG_PP_MAKE_PSEQ_IMPL2( \
  bp_type_seq, bp_obj_seq, ap_type_seq, ap_obj_seq, ap_value_seq) \
    (8, \
      (bp_type_seq, \
      bp_obj_seq, \
      BOOST_PP_SEQ_SIZE(bp_type_seq), \
      BOOST_PP_SEQ_TO_LIST( \
        BOOST_PP_SEQ_FOR_EACH_I(WG_PP_MARK_THISU_INDX, ~, bp_obj_seq)), \
      ap_type_seq, \
      ap_obj_seq, \
      ap_value_seq, \
      BOOST_PP_SEQ_SIZE(ap_type_seq)))

#define WG_PP_MAKE_PSEQ_IMPL1(bp_seq, ap_seq) \
  WG_PP_MAKE_PSEQ_IMPL2( \
    WG_PP_BOUNDPSEQ_TO_TYPESEQ(bp_seq), \
    WG_PP_BOUNDPSEQ_TO_OBJSEQ(bp_seq), \
    WG_PP_ASSIGNEDPSEQ_TO_TYPESEQ(ap_seq), \
    WG_PP_ASSIGNEDPSEQ_TO_OBJSEQ(ap_seq), \
    WG_PP_ASSIGNEDPSEQ_TO_VALUESEQ(ap_seq))

//PSEQ:
//  is a PP_ARRAY of following types:
//  (8, (PP_SEQ, PP_SEQ, INT, BPSEQ_THISU_MARKER, PP_SEQ, PP_SEQ, PP_SEQ, INT))
//  BPSEQ_THISU_MARKER:
//    is a PP_LIST of size at most 1.
#define WG_PP_MAKE_PSEQ(bp_seq, ap_seq) \
  BOOST_PP_EXPR_IF( \
    BOOST_PP_AND( \
      BOOST_PP_NOT(BOOST_PP_EQUAL(BOOST_PP_SEQ_SIZE(bp_seq), 1)), \
      BOOST_PP_NOT(WG_PP_IS_EVEN(BOOST_PP_SEQ_SIZE(bp_seq)))), \
    BOOST_PP_ASSERT_MSG( \
      0, "The second parameter to WG_SCOPEFUNCTION is malformed.")) \
  \
  BOOST_PP_EXPR_IF( \
    BOOST_PP_AND( \
      BOOST_PP_NOT(BOOST_PP_EQUAL(BOOST_PP_SEQ_SIZE(ap_seq), 1)), \
      BOOST_PP_NOT(WG_PP_IS_MOD3_R0(BOOST_PP_SEQ_SIZE(ap_seq)))), \
    BOOST_PP_ASSERT_MSG( \
      0, "The third parameter to WG_SCOPEFUNCTION is malformed.")) \
  \
  WG_PP_MAKE_PSEQ_IMPL1( \
    BOOST_PP_EXPR_IF( \
      BOOST_PP_NOT(BOOST_PP_EQUAL(BOOST_PP_SEQ_SIZE(bp_seq), 1)), \
      bp_seq), \
    BOOST_PP_EXPR_IF( \
      BOOST_PP_NOT(BOOST_PP_EQUAL(BOOST_PP_SEQ_SIZE(ap_seq), 1)), \
      ap_seq))

#define WG_PP_PSEQ_BOUNDTYPES(pseq) \
  BOOST_PP_ARRAY_ELEM(0, pseq)
#define WG_PP_PSEQ_BOUNDOBJECTS(pseq) \
  BOOST_PP_ARRAY_ELEM(1, pseq)
#define WG_PP_PSEQ_BOUNDXXX_SIZE(pseq) \
  BOOST_PP_ARRAY_ELEM(2, pseq)
#define WG_PP_PSEQ_BOUNDOBJECTS_THISU_MARKER(pseq) \
  BOOST_PP_ARRAY_ELEM(3, pseq)
#define WG_PP_PSEQ_ASSIGNEDTYPES(pseq) \
  BOOST_PP_ARRAY_ELEM(4, pseq)
#define WG_PP_PSEQ_ASSIGNEDOBJECTS(pseq) \
  BOOST_PP_ARRAY_ELEM(5, pseq)
#define WG_INERNAL_PSEQ_ASSIGNEDVALUES(pseq) \
  BOOST_PP_ARRAY_ELEM(6, pseq)
#define WG_PP_PSEQ_ASSIGNEDXXX_SIZE(pseq) \
  BOOST_PP_ARRAY_ELEM(7, pseq)

// BOOST_PP_SEQ_FOR_EACH_I functor.
#define \
  WG_PP_PARAMPROXY_SEQUENCETYPE(r, data, indx, elem) \
    BOOST_PP_LPAREN() WG_PP_ADDREFERENCE(elem) BOOST_PP_RPAREN()

#define WG_PP_PARAMPROXY_TYPE_TEMPLATEPARAMLIST(pseq) \
  WG_PP_SEQ_ENUM( \
    BOOST_PP_SEQ_FOR_EACH_I( \
      WG_PP_PARAMPROXY_SEQUENCETYPE, \
      ~, \
      WG_PP_PSEQ_BOUNDTYPES(pseq)WG_PP_PSEQ_ASSIGNEDTYPES(pseq)))

#define WG_PP_PARAMPROXY_OBJ_INITLIST( \
  bound_objs_seq, assigned_objs_seq, thisu_marker) \
    WG_PP_SEQ_ENUM( \
      BOOST_PP_IF( \
        BOOST_PP_NOT(BOOST_PP_LIST_IS_NIL(thisu_marker)), \
        WG_PP_SEQ_REPLACE( \
          bound_objs_seq, \
          BOOST_PP_LIST_FIRST(thisu_marker), \
          this), \
        bound_objs_seq) \
      assigned_objs_seq)

#define WG_PP_PARAMPROXY_TYPE_NAME() \
  WG_PP_FORMAT_NAME(param_proxy_type)
#define WG_PP_PARAMPROXY_OBJ_NAME() \
  WG_PP_FORMAT_NAME(param_proxy)

#define WG_PP_PSEQ_TO_PARAMPROXYDCLN(pseq) \
    typedef boost::tuple< \
      WG_PP_PARAMPROXY_TYPE_TEMPLATEPARAMLIST(pseq) \
    > WG_PP_PARAMPROXY_TYPE_NAME() WG_PP_IDENTITY(;) \
    WG_PP_PARAMPROXY_TYPE_NAME() WG_PP_PARAMPROXY_OBJ_NAME() \
      BOOST_PP_LPAREN() \
        WG_PP_PARAMPROXY_OBJ_INITLIST( \
          WG_PP_PSEQ_BOUNDOBJECTS(pseq), \
          WG_PP_PSEQ_ASSIGNEDOBJECTS(pseq), \
          WG_PP_PSEQ_BOUNDOBJECTS_THISU_MARKER(pseq)) \
      BOOST_PP_RPAREN() WG_PP_IDENTITY(;)
    
// BOOST_PP_ENUM functor.
#define WG_PP_PARAMPROXY_OBJ_ELEMACCESS(z, n, obj_name) \
  WG_PP_IDENTITY(obj_name).get<WG_PP_IDENTITY(n)>()

#define WG_PP_PARAMPROXY_OBJ_ELEMACCESSLIST(pseq, obj_name) \
    BOOST_PP_ENUM( \
      BOOST_PP_ADD( \
        WG_PP_PSEQ_BOUNDXXX_SIZE(pseq), \
        WG_PP_PSEQ_ASSIGNEDXXX_SIZE(pseq)), \
      WG_PP_PARAMPROXY_OBJ_ELEMACCESS, \
      obj_name)
    
// BOOST_PP_SEQ_FOR_EACH_I functor.
#define \
  WG_PP_CALL_PARAM_ENTRY( \
    r, obj_seq, indx, elem) \
      BOOST_PP_IF( \
        WG_PP_TOKENS_STARTS_WITH_THISU( \
          BOOST_PP_SEQ_ELEM(indx, obj_seq)), \
        WG_PP_ADDCONST(elem), \
        elem) \
      BOOST_PP_SEQ_ELEM(indx, obj_seq) \
      BOOST_PP_COMMA_IF( \
        BOOST_PP_NOT(WG_PP_IS_SEQ_INDEX_LAST( \
          BOOST_PP_SEQ_SIZE(obj_seq), \
          indx)))

#define WG_PP_CALL_PARAMLIST(pseq) \
  BOOST_PP_LPAREN() \
    BOOST_PP_SEQ_FOR_EACH_I( \
      WG_PP_CALL_PARAM_ENTRY, \
      WG_PP_IDENTITY_2( \
        WG_PP_PSEQ_BOUNDOBJECTS(pseq), \
        WG_PP_PSEQ_ASSIGNEDOBJECTS(pseq)), \
      WG_PP_IDENTITY_2( \
        WG_PP_PSEQ_BOUNDTYPES(pseq), \
        WG_PP_PSEQ_ASSIGNEDTYPES(pseq))) \
  BOOST_PP_RPAREN()

#define WG_PP_AUTOFUNCTOR_START(function_name, pseq) \
  struct WG_PP_IDENTITY(function_name) \
  { \
    void operator()(WG_PP_PARAMPROXY_TYPE_NAME() & param_proxy) \
    { \
      static_cast<void>(param_proxy); \
      this->call(WG_PP_PARAMPROXY_OBJ_ELEMACCESSLIST(pseq, param_proxy)); \
    } \
    void WG_PP_IDENTITY(call) WG_PP_CALL_PARAMLIST(pseq)
    
#define WG_PP_AUTOFUNCTOR_END() \
  } WG_PP_FORMAT_NAME(auto_functor)() \
    BOOST_PP_LPAREN() \
      WG_PP_PARAMPROXY_OBJ_NAME() \
    BOOST_PP_RPAREN() WG_PP_IDENTITY(;)

#define WG_PP_AUTOFUNCTION(function_name, pseq) \
  { \
    WG_PP_PSEQ_TO_PARAMPROXYDCLN(pseq) \
    WG_PP_AUTOFUNCTOR_START(function_name, pseq)

#define WG_PP_AUTOFUNCTION_END() \
  WG_PP_AUTOFUNCTOR_END() \
  }

//TESTS Begin

#define TEST_SEQ (w)(x)(y)(z)(a)(b)(c)(d)(class)(this_)
#define ASEQ (T1)(T2)(T3)

//WG_PP_BOUNDPSEQ_TO_TYPESEQ(TEST_SEQ)
//WG_PP_BOUNDPSEQ_TO_OBJSEQ(TEST_SEQ)
//WG_PP_ASSIGNEDPSEQ_TO_TYPESEQ(ASEQ)
//WG_PP_ASSIGNEDPSEQ_TO_OBJSEQ(ASEQ)
//WG_PP_ASSIGNEDPSEQ_TO_VALUESEQ(ASEQ)
//BOOST_PP_SEQ_FOR_EACH_I(WG_PP_MARK_THISU_INDX, ~, (x)(z)(b)(d)(this_))


WG_AUTOFUNCTION(foo, TEST_SEQ, ASEQ)
//WG_AUTOFUNCTION(foo, (void), (void))
{
}
WG_AUTOFUNCTION_END()
