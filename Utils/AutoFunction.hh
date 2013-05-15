#ifndef WG_AUTOFUNCTION_HH_
#define WG_AUTOFUNCTION_HH_

#include <boost/preprocessor.hpp>
#include <boost/local_function/detail/preprocessor/keyword/facility/is.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>

//###########
//Public APIs
//###########

#define WG_AUTOFUNCTION_BIND( \
  bound_result_seq, \
  ret_type, \
  function_name, \
  bound_param_seq) \
    WG_AUTOFUNCTION( \
      bound_result_seq, ret_type, function_name, bound_param_seq, (void))

#define WG_AUTOFUNCTION_ASSIGN( \
  bound_result_seq, \
  ret_type, \
  function_name, \
  assigned_param_seq) \
    WG_AUTOFUNCTION( \
      bound_result_seq, ret_type, function_name, (void), assigned_param_seq)
  
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
#define WG_AUTOFUNCTION( \
  bound_result_seq, \
  ret_type, \
  function_name, \
  bound_param_seq, \
  assigned_param_seq) \
    WG_PP_AUTOFUNCTION( \
      function_name, \
      WG_PP_MAKE_PSEQ( \
        bound_result_seq, ret_type, bound_param_seq, assigned_param_seq))
    
#define WG_AUTOFUNCTION_END WG_PP_AUTOFUNCTION_END()

//###########
//Impl Macros
//###########
  
//------------
//Basic Tools.
//------------
  
#define WG_PP_IS_NIL_TOKEN(x) BOOST_PP_LiST_IS_NIL(x)
  
#define WG_PP_IDENTITY(x) x
#define WG_PP_IDENTITY_1(x) WG_PP_IDENTITY(x)
#define WG_PP_IDENTITY_2(x, y) x y
#define WG_PP_IDENTITY_3(x, y, z) x y z

#define WG_PP_FORMAT_NAME(name) \
  BOOST_PP_CAT(WG_PP_IDENTITY(pgcllXXXautofunctionXXX), name)

#define WG_PP_TOKEN_MATCHES1_WG_PP_TRUE (1) /* unary */
#define WG_PP_TOKENS_START_WITH_WG_PP_TRUE(tokens) \
  BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT( \
    tokens, \
    WG_PP_TOKEN_MATCHES1_)

#define WG_PP_TOKEN_MATCHES2_void (1) /* unary */
#define WG_PP_TOKENS_STARTS_WITH_VOID(tokens) \
  BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT( \
    tokens, \
    WG_PP_TOKEN_MATCHES2_)

#define WG_PP_TOKEN_MATCHES3_this_ (1) /* unary */
#define WG_PP_TOKENS_STARTS_WITH_THISU(tokens) \
  BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT( \
    tokens, \
    WG_PP_TOKEN_MATCHES3_)

#define WG_PP_TOKEN_MATCHES4_local (1) /* unary */
#define WG_PP_TOKENS_STARTS_WITH_LOCAL(tokens) \
  BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT( \
    tokens, \
    WG_PP_TOKEN_MATCHES4_)

#define WG_PP_TOKEN_MATCHES5_localref (1) /* unary */
#define WG_PP_TOKENS_STARTS_WITH_LOCALREF(tokens) \
  BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT( \
    tokens, \
    WG_PP_TOKEN_MATCHES5_)
    
#define WG_PP_CAPTUREDTYPE_local(capturedtype) local
#define WG_PP_CAPTUREDTYPE_VALUE_local(value) value
#define WG_PP_CAPTUREDTYPE_LOCAL_VALUE(capturedtype) \
  BOOST_PP_EXPAND( \
    BOOST_PP_CAT(WG_PP_CAPTUREDTYPE_VALUE_, capturedtype))
#define WG_PP_IS_CAPTUREDTYPE_LOCAL(capturedtype) \
  WG_PP_TOKENS_STARTS_WITH_LOCAL( \
    BOOST_PP_EXPAND( \
      BOOST_PP_CAT(WG_PP_CAPTUREDTYPE_,capturedtype)))

#define WG_PP_CAPTUREDTYPE_localref(capturedtype) localref
#define WG_PP_CAPTUREDTYPE_VALUE_localref(value) value
#define WG_PP_CAPTUREDTYPE_LOCALREF_VALUE(capturedtype) \
  BOOST_PP_EXPAND( \
    BOOST_PP_CAT(WG_PP_CAPTUREDTYPE_VALUE_, capturedtype))
#define WG_PP_IS_CAPTUREDTYPE_LOCALREF(capturedtype) \
  WG_PP_TOKENS_STARTS_WITH_LOCALREF( \
    BOOST_PP_EXPAND( \
      BOOST_PP_CAT(WG_PP_CAPTUREDTYPE_,capturedtype)))
      
#define WG_PP_CAPTUREDTYPE_VALUE(capturedtype) \
  BOOST_PP_IIF( \
    WG_PP_IS_CAPTUREDTYPE_LOCAL(capturedtype), \
    WG_PP_CAPTUREDTYPE_LOCAL_VALUE(capturedtype), \
    BOOST_PP_IIF( \
      WG_PP_IS_CAPTUREDTYPE_LOCALREF(capturedtype), \
      WG_PP_CAPTUREDTYPE_LOCALREF_VALUE(capturedtype), \
      capturedtype))
    
#define WG_PP_CAPTUREDTYPE_ADDCONST(capturedtype) \
  BOOST_PP_IIF( \
    WG_PP_IS_CAPTUREDTYPE_LOCALREF(capturedtype), \
    WG_PP_CAPTUREDTYPE_LOCALREF_VALUE(capturedtype), \
    BOOST_PP_IIF( \
      WG_PP_IS_CAPTUREDTYPE_LOCAL(capturedtype), \
      WG_PP_CAPTUREDTYPE_LOCAL_VALUE(capturedtype), \
      boost::add_const<WG_PP_IDENTITY(capturedtype)>::type))
/*
namespace WG
{
namespace AutoFunctor
{
namespace Internal
{

template <typename T>
struct AddConstIfNotReference
{
  template <bool> struct AddConst;
  template <> struct AddConst<true>
  { 
    typedef boost::add_const<T>::type type;
  };
  template <> struct AddConst<false>
  {
    typedef T type;
  };
  
  typedef typename AddConst< boost::is_reference<T>::value >::type type;
};

}
}
}
*/
#define WG_PP_CAPTUREDTYPE_ADDREFERENCE(capturedtype) \
  BOOST_PP_IIF( \
    WG_PP_IS_CAPTUREDTYPE_LOCALREF(capturedtype), \
    WG_PP_CAPTUREDTYPE_LOCALREF_VALUE(capturedtype), \
    BOOST_PP_IIF( \
      WG_PP_IS_CAPTUREDTYPE_LOCAL(capturedtype), \
      WG_PP_CAPTUREDTYPE_LOCAL_VALUE(capturedtype) &, \
      boost::add_reference<WG_PP_IDENTITY(capturedtype)>::type))
  
#define WG_PP_IS_ODD(num) BOOST_PP_MOD(num,2)
#define WG_PP_IS_EVEN(num) \
  BOOST_PP_NOT(WG_PP_IS_ODD(num))

#define WG_PP_IS_MOD3_R0(num) \
  BOOST_PP_EQUAL(BOOST_PP_MOD(num,3), 0)
#define WG_PP_IS_MOD3_R1(num) \
  BOOST_PP_EQUAL(BOOST_PP_MOD(num,3), 1)
#define WG_PP_IS_MOD3_R2(num) \
  BOOST_PP_EQUAL(BOOST_PP_MOD(num,3), 2)

#define WG_PP_EXISTS_1TUPLE_IMPL(x) \
  WG_PP_TRUE
#define WG_PP_EXISTS_2TUPLE_IMPL(x, y) \
  WG_PP_TRUE

#define WG_PP_EXISTS_1TUPLE(tuple_seq) \
  WG_PP_TOKENS_START_WITH_WG_PP_TRUE( \
    BOOST_PP_EXPAND( \
      WG_PP_EXISTS_1TUPLE_IMPL \
      tuple_seq))

#define WG_PP_EXISTS_2TUPLE(tuple_seq) \
  WG_PP_TOKENS_START_WITH_WG_PP_TRUE( \
    BOOST_PP_EXPAND( \
      WG_PP_EXISTS_2TUPLE_IMPL \
      tuple_seq))

#define WG_PP_SEQ_IS_NOT_NIL_IMPL(seq) WG_PP_TRUE
// Nil sequences are defined to be empty tokens.
#define WG_PP_SEQ_IS_NOT_NIL(seq) \
  WG_PP_TOKENS_START_WITH_WG_PP_TRUE( \
    BOOST_PP_EXPAND(WG_PP_SEQ_IS_NOT_NIL_IMPL seq))

#define WG_PP_SEQ_ENUM_0(seq)
#define WG_PP_SEQ_ENUM_1(seq) BOOST_PP_SEQ_ENUM(seq)
// Handles empty sequences.
#define WG_PP_SEQ_ENUM(seq) \
  BOOST_PP_EXPAND( \
    BOOST_PP_CAT(WG_PP_SEQ_ENUM_, WG_PP_SEQ_IS_NOT_NIL(seq)))(seq)

#define WG_PP_SEQ_REPLACE_00(seq, indx, elem)
#define WG_PP_SEQ_REPLACE_01(seq, indx, elem)
#define WG_PP_SEQ_REPLACE_10(seq, indx, elem) seq
#define WG_PP_SEQ_REPLACE_11(seq, indx, elem) \
  BOOST_PP_SEQ_REPLACE(seq, BOOST_PP_SEQ_ELEM(0,indx), elem)
// Handles empty sequences.
// Handles empty token as indx.
#define WG_PP_SEQ_REPLACE(seq, indx, elem) \
  BOOST_PP_EXPAND( \
    BOOST_PP_CAT( \
      BOOST_PP_CAT( \
        WG_PP_SEQ_REPLACE_, \
        WG_PP_SEQ_IS_NOT_NIL(seq)), \
      WG_PP_SEQ_IS_NOT_NIL(indx))) \
    (seq, indx, elem)

#define WG_PP_IS_SEQ_COUNT_EVEN(seq) \
  BOOST_PP_NOT(BOOST_PP_MOD(BOOST_PP_SEQ_SIZE(seq), 2))

#define WG_PP_IS_SEQ_COUNT_ODD(seq) \
  BOOST_PP_NOT(WG_PP_IS_SEQ_COUNT_EVEN(seq))
  
#define WG_PP_IS_SEQ_INDEX_LAST(seq_count, indx) \
  BOOST_PP_EQUAL(seq_count, BOOST_PP_INC(indx))

#define WG_PP_TUPLIZE(x) (x)
#define WG_PP_TUPLIZE_1(x) WG_PP_TUPLIZE(x)
#define WG_PP_TUPLIZE_2(x, y) (x, y)

#define WG_PP_1TUPLIZE(x) (x)
#define WG_PP_1TUPLIZE_1(x) WG_PP_1TUPLIZE(x)
#define WG_PP_1TUPLIZE_2(x, y) (x)(y)

//------
//ALTSEQ
//------

//----------------
//ALTSEQ Transform
//----------------

#define WG_PP_ALTSEQ_APPEND_COMMA_TO_HEAD_1(x) \
  WG_PP_TUPLIZE_1(x) BOOST_PP_COMMA()

#define WG_PP_ALTSEQ_APPEND_COMMA_TO_HEAD_2(x, y) \
  WG_PP_TUPLIZE_2(x, y) BOOST_PP_COMMA()

#define WG_PP_ALTSEQ_TRANSFORM_HEAD_IMPL( \
  head_tuple, \
  tuple_seq_rest, \
  TRANSFORM, \
  TRANSFORM_REST) \
    WG_PP_IDENTITY(TRANSFORM head_tuple)TRANSFORM_REST(tuple_seq_rest)
///@brief head_tuple_kind
///@brief   an unsigned integer representing the kind of tuple the head tuple
///@brief   is, i.e., 1-tuple, 2-tuple, etc.
///@brief TRANSFORM
///@brief   the name of a one or two parameter macro to apply to
///@brief   the head of tuple_seq
///@brief TRANSFORM_REST
///@brief   the name of a single parameter macro to apply to the rest of
///@brief   tuple_seq.
#define WG_PP_ALTSEQ_TRANSFORM( \
  head_tuple_kind, \
  tuple_seq, \
  TRANSFORM, \
  TRANSFORM_REST) \
    BOOST_PP_EXPAND( \
      WG_PP_ALTSEQ_TRANSFORM_HEAD_IMPL \
        BOOST_PP_LPAREN() \
          BOOST_PP_CAT( \
            WG_PP_ALTSEQ_APPEND_COMMA_TO_HEAD_, head_tuple_kind) \
          tuple_seq BOOST_PP_COMMA() \
          TRANSFORM BOOST_PP_COMMA() \
          TRANSFORM_REST \
        BOOST_PP_RPAREN() )

//---------------
//ALTSEQ_EAT_HEAD
//---------------

///@brief head_tuple_kind
///@brief   an unsigned integer representing the arity of the head tuple
#define WG_PP_ALTSEQ_EAT_HEAD(head_tuple_kind, tuple_seq) \
  WG_PP_ALTSEQ_TRANSFORM( \
    head_tuple_kind, \
    tuple_seq, \
    BOOST_PP_TUPLE_EAT(head_tuple_kind), \
    WG_PP_IDENTITY)

//--------------------
//ALTSEQ_1TUPLIZE_HEAD
//--------------------

///@brief head_tuple_kind
///@brief   an unsigned integer representing the arity of the head tuple
///@brief 1-tuplizes the head of tuple_seq, and discards the rest.
#define WG_PP_ALTSEQ_1TUPLIZE_HEAD(head_tuple_kind, tuple_seq) \
  WG_PP_ALTSEQ_TRANSFORM( \
    head_tuple_kind, \
    tuple_seq, \
    BOOST_PP_CAT(WG_PP_1TUPLIZE_, head_tuple_kind), \
    BOOST_PP_TUPLE_EAT(1))

//----------------
//ALTSEQ_LINEARIZE
//----------------

#define WG_PP_ALTSEQ_LINEARIZE_MAKE_INITIAL_STATE(tuple_seq) \
  (0, tuple_seq)
#define WG_PP_ALTSEQ_LINEARIZE_GET_HEAD_INDEX(state) \
  BOOST_PP_TUPLE_ELEM(2, 0, state)
#define WG_PP_ALTSEQ_LINEARIZE_GET_HEAD_ARITY(state) \
  BOOST_PP_INC( \
    BOOST_PP_MOD( \
      WG_PP_ALTSEQ_LINEARIZE_GET_HEAD_INDEX(state), \
      2))
#define WG_PP_ALTSEQ_LINEARIZE_GET_SEQ(state) \
  BOOST_PP_TUPLE_ELEM(2, 1, state)

#define WG_PP_ALTSEQ_LINEARIZE_PRED_1(state) \
  WG_PP_EXISTS_1TUPLE( \
    WG_PP_ALTSEQ_LINEARIZE_GET_SEQ(state))
#define WG_PP_ALTSEQ_LINEARIZE_PRED_2(state) \
  WG_PP_EXISTS_2TUPLE( \
    WG_PP_ALTSEQ_LINEARIZE_GET_SEQ(state))

#define WG_PP_ALTSEQ_LINEARIZE_PRED(r, state) \
  BOOST_PP_CAT( \
    WG_PP_ALTSEQ_LINEARIZE_PRED_, \
    WG_PP_ALTSEQ_LINEARIZE_GET_HEAD_ARITY(state)) (state)

#define WG_PP_ALTSEQ_LINEARIZE_INC_OP(r, state) \
  ( \
    BOOST_PP_INC(BOOST_PP_TUPLE_ELEM(2, 0, state)), \
    WG_PP_ALTSEQ_EAT_HEAD( \
      WG_PP_ALTSEQ_LINEARIZE_GET_HEAD_ARITY(state), \
      WG_PP_ALTSEQ_LINEARIZE_GET_SEQ(state)) \
  )

#define WG_PP_ALTSEQ_LINEARIZE_HEAD(r, state) \
    WG_PP_ALTSEQ_1TUPLIZE_HEAD( \
      WG_PP_ALTSEQ_LINEARIZE_GET_HEAD_ARITY(state), \
      WG_PP_ALTSEQ_LINEARIZE_GET_SEQ(state))

#define WG_PP_ALTSEQ_LINEARIZE(tuple_seq) \
  BOOST_PP_FOR( \
    WG_PP_ALTSEQ_LINEARIZE_MAKE_INITIAL_STATE(tuple_seq), \
    WG_PP_ALTSEQ_LINEARIZE_PRED, \
    WG_PP_ALTSEQ_LINEARIZE_INC_OP, \
    WG_PP_ALTSEQ_LINEARIZE_HEAD)

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

#define WG_PP_MAKE_PSEQ_IMPL3(wiparray) \
  BOOST_PP_ARRAY_PUSH_BACK( \
    wiparray, \
    BOOST_PP_ADD( \
      BOOST_PP_ADD( \
        WG_PP_PSEQ_BOUNDXXX_SIZE(wiparray), \
        WG_PP_PSEQ_ASSIGNEDXXX_SIZE(wiparray)), \
        WG_PP_PSEQ_BOUNDRESULTEXISTS(wiparray)))
    
#define WG_PP_MAKE_PSEQ_IMPL2( \
  bresult_type_seq, bresult_obj_seq, \
  ret_type, \
  bp_type_seq, bp_obj_seq, \
  ap_type_seq, ap_obj_seq, ap_value_seq) \
    WG_PP_MAKE_PSEQ_IMPL3( \
      (12, \
        (bresult_type_seq, \
        bresult_obj_seq, \
        BOOST_PP_SEQ_SIZE(bresult_type_seq), \
        ret_type, \
        bp_type_seq, \
        bp_obj_seq, \
        BOOST_PP_SEQ_SIZE(bp_type_seq), \
        BOOST_PP_SEQ_FOR_EACH_I(WG_PP_MARK_THISU_INDX, ~, bp_obj_seq), \
        ap_type_seq, \
        ap_obj_seq, \
        ap_value_seq, \
        BOOST_PP_SEQ_SIZE(ap_type_seq))) \
    )

#define WG_PP_MAKE_PSEQ_IMPL1(bresult_seq, ret_type, bp_seq, ap_seq) \
  WG_PP_MAKE_PSEQ_IMPL2( \
    WG_PP_BOUNDPSEQ_TO_TYPESEQ(bresult_seq), \
    WG_PP_BOUNDPSEQ_TO_OBJSEQ(bresult_seq), \
    ret_type, \
    WG_PP_BOUNDPSEQ_TO_TYPESEQ(bp_seq), \
    WG_PP_BOUNDPSEQ_TO_OBJSEQ(bp_seq), \
    WG_PP_ASSIGNEDPSEQ_TO_TYPESEQ(ap_seq), \
    WG_PP_ASSIGNEDPSEQ_TO_OBJSEQ(ap_seq), \
    WG_PP_ASSIGNEDPSEQ_TO_VALUESEQ(ap_seq))

#define WG_PP_BOUND_PSEQ_IS_VOID(bp_seq) \
  BOOST_PP_IF( \
    WG_PP_EXISTS_1TUPLE(BOOST_PP_TUPLE_EAT(1) bp_seq), \
    0, \
    BOOST_PP_IF( \
      WG_PP_TOKENS_STARTS_WITH_VOID(BOOST_PP_SEQ_ELEM(0, bp_seq)), \
      1, \
      0))

#define WG_PP_ASSIGNED_PSEQ_IS_VOID(ap_alt_seq) \
  BOOST_PP_IF( \
    WG_PP_EXISTS_2TUPLE(BOOST_PP_TUPLE_EAT(1) ap_alt_seq), \
    0, \
    BOOST_PP_IF( \
      BOOST_PP_EXPAND( \
        WG_PP_TOKENS_STARTS_WITH_VOID WG_PP_ALTSEQ_1TUPLIZE_HEAD( \
          1, ap_alt_seq)), \
      1, \
      0))

//TODO
//BOOST_PP_EXPR_IF( \
//  BOOST_PP_AND( \
//    BOOST_PP_NOT(WG_PP_BOUND_PSEQ_IS_VOID(bp_seq)), \
//    BOOST_PP_NOT(WG_PP_IS_EVEN(BOOST_PP_SEQ_SIZE(bp_seq)))), \
//  BOOST_PP_ASSERT_MSG( \
//    0, "The second parameter to WG_AUTOFUNCTION is malformed.")) \
//\
//BOOST_PP_EXPR_IF( \
//  BOOST_PP_AND( \
//    BOOST_PP_NOT(WG_PP_ASSIGNED_PSEQ_IS_VOID(ap_alt_seq)), \
//    BOOST_PP_NOT(WG_PP_IS_MOD3_R0(BOOST_PP_SEQ_SIZE(ap_alt_seq)))), \
//  BOOST_PP_ASSERT_MSG( \
//    0, "The third parameter to WG_AUTOFUNCTION is malformed.")) \
//\
//
//PSEQ:
//  is a PP_ARRAY of following types:
//  (9, (PP_SEQ, PP_SEQ, INT, BPSEQ_THISU_MARKER, PP_SEQ, PP_SEQ, PP_SEQ, INT, INT))
//  BPSEQ_THISU_MARKER:
//    is a PP_SEQ of size at most 1.
#define WG_PP_MAKE_PSEQ(bresult_seq, ret_type, bp_seq, ap_alt_seq) \
  WG_PP_MAKE_PSEQ_IMPL1( \
    BOOST_PP_EXPR_IF( \
      BOOST_PP_NOT(WG_PP_BOUND_PSEQ_IS_VOID(bresult_seq)), \
      bresult_seq), \
    ret_type, \
    BOOST_PP_EXPR_IF( \
      BOOST_PP_NOT(WG_PP_BOUND_PSEQ_IS_VOID(bp_seq)), \
      bp_seq), \
    BOOST_PP_EXPR_IF( \
      BOOST_PP_NOT(WG_PP_ASSIGNED_PSEQ_IS_VOID(ap_alt_seq)), \
      WG_PP_ALTSEQ_LINEARIZE(ap_alt_seq)))

#define WG_PP_PSEQ_BOUNDRESULTTYPE(pseq) \
  BOOST_PP_ARRAY_ELEM(0, pseq)
#define WG_PP_PSEQ_BOUNDRESULTOBJECT(pseq) \
  BOOST_PP_ARRAY_ELEM(1, pseq)
#define WG_PP_PSEQ_BOUNDRESULTEXISTS(pseq) \
  BOOST_PP_ARRAY_ELEM(2, pseq)
#define WG_PP_PSEQ_RETTYPE(pseq) \
  BOOST_PP_ARRAY_ELEM(3, pseq)
#define WG_PP_PSEQ_BOUNDTYPES(pseq) \
  BOOST_PP_ARRAY_ELEM(4, pseq)
#define WG_PP_PSEQ_BOUNDOBJECTS(pseq) \
  BOOST_PP_ARRAY_ELEM(5, pseq)
#define WG_PP_PSEQ_BOUNDXXX_SIZE(pseq) \
  BOOST_PP_ARRAY_ELEM(6, pseq)
#define WG_PP_PSEQ_BOUNDOBJECTS_THISU_MARKER(pseq) \
  BOOST_PP_ARRAY_ELEM(7, pseq)
#define WG_PP_PSEQ_ASSIGNEDTYPES(pseq) \
  BOOST_PP_ARRAY_ELEM(8, pseq)
#define WG_PP_PSEQ_ASSIGNEDOBJECTS(pseq) \
  BOOST_PP_ARRAY_ELEM(9, pseq)
#define WG_INERNAL_PSEQ_ASSIGNEDVALUES(pseq) \
  BOOST_PP_ARRAY_ELEM(10, pseq)
#define WG_PP_PSEQ_ASSIGNEDXXX_SIZE(pseq) \
  BOOST_PP_ARRAY_ELEM(11, pseq)
#define WG_PP_PSEQ_TOTALXXX_SiZE(pseq) \
  BOOST_PP_ARRAY_ELEM(12, pseq)

// BOOST_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_PARAMPROXY_TYPE_MEMBER(r, offset, indx, elem) \
  WG_PP_CAPTUREDTYPE_ADDREFERENCE( \
    WG_PP_CAPTUREDTYPE_ADDCONST(elem)) \
      BOOST_PP_CAT(m, BOOST_PP_ADD(indx,offset)) WG_PP_IDENTITY(;)

#define WG_PP_PARAMPROXY_TYPE_MEMBERDECLNS(pseq) \
  BOOST_PP_EXPR_IIF( \
    WG_PP_PSEQ_BOUNDRESULTEXISTS(pseq), \
    WG_PP_CAPTUREDTYPE_ADDREFERENCE( \
      BOOST_PP_SEQ_HEAD(WG_PP_PSEQ_BOUNDRESULTTYPE(pseq))) \
    m0;) \
  BOOST_PP_SEQ_FOR_EACH_I( \
    WG_PP_PARAMPROXY_TYPE_MEMBER, \
    WG_PP_PSEQ_BOUNDRESULTEXISTS(pseq), \
    WG_PP_IDENTITY_2( \
      WG_PP_PSEQ_BOUNDTYPES(pseq), \
      WG_PP_PSEQ_ASSIGNEDTYPES(pseq)))

// BOOST_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_PARAMPROXY_TYPE_CTORPARAM(r, offset, indx, elem) \
  BOOST_PP_LPAREN() \
    WG_PP_CAPTUREDTYPE_ADDREFERENCE(WG_PP_CAPTUREDTYPE_ADDCONST(elem)) \
      BOOST_PP_CAT(p, BOOST_PP_ADD(indx,offset)) \
  BOOST_PP_RPAREN()

#define WG_PP_PARAMPROXY_TYPE_CTORPARAMLIST(pseq) \
  BOOST_PP_EXPR_IIF( \
    WG_PP_PSEQ_BOUNDRESULTEXISTS(pseq), \
    WG_PP_CAPTUREDTYPE_ADDREFERENCE( \
      BOOST_PP_SEQ_HEAD(WG_PP_PSEQ_BOUNDRESULTTYPE(pseq))) \
    p0 \
    BOOST_PP_IIF( \
      BOOST_PP_GREATER(WG_PP_PSEQ_TOTALXXX_SiZE(pseq), 1), \
      BOOST_PP_COMMA, \
      BOOST_PP_EMPTY))() \
  WG_PP_SEQ_ENUM( \
    BOOST_PP_SEQ_FOR_EACH_I( \
      WG_PP_PARAMPROXY_TYPE_CTORPARAM, \
      WG_PP_PSEQ_BOUNDRESULTEXISTS(pseq), \
      WG_PP_IDENTITY_2( \
        WG_PP_PSEQ_BOUNDTYPES(pseq), \
        WG_PP_PSEQ_ASSIGNEDTYPES(pseq))))
  
// BOOST_PP_ENUM functor.
#define WG_PP_PARAMPROXY_TYPE_CTORINITENTRY(z, indx, data) \
  BOOST_PP_CAT(m, indx)BOOST_PP_LPAREN()BOOST_PP_CAT(p, indx)BOOST_PP_RPAREN()
  
#define WG_PP_PARAMPROXY_TYPE_CTORINITLIST(pseq) \
  BOOST_PP_ENUM( \
    WG_PP_PSEQ_TOTALXXX_SiZE(pseq), \
    WG_PP_PARAMPROXY_TYPE_CTORINITENTRY, \
    ~)
  
#define WG_PP_PARAMPROxY_TYPE_CTORDCNL(pseq) \
  WG_PP_PARAMPROXY_TYPE_NAME() \
    BOOST_PP_LPAREN() \
      WG_PP_PARAMPROXY_TYPE_CTORPARAMLIST(pseq) \
    BOOST_PP_RPAREN() \
      BOOST_PP_EXPR_IF(WG_PP_PSEQ_TOTALXXX_SiZE(pseq), WG_PP_IDENTITY(:)) \
      WG_PP_PARAMPROXY_TYPE_CTORINITLIST(pseq) \
    {}

// BOOST_PP_ENUM functor.
#define WG_PP_PARAMPROXY_TYPE_ACCESSORDCLN(r, offset, indx, elem) \
  WG_PP_CAPTUREDTYPE_ADDREFERENCE(WG_PP_CAPTUREDTYPE_ADDCONST(elem)) \
    BOOST_PP_CAT(get, BOOST_PP_ADD(indx,offset)) () const \
  { \
    return BOOST_PP_CAT(m, BOOST_PP_ADD(indx,offset)); \
  }
    
#define WG_PP_PARAMPROXY_TYPE_ACCESSORS(pseq) \
  BOOST_PP_EXPR_IIF( \
    WG_PP_PSEQ_BOUNDRESULTEXISTS(pseq), \
    WG_PP_CAPTUREDTYPE_ADDREFERENCE( \
      BOOST_PP_SEQ_HEAD(WG_PP_PSEQ_BOUNDRESULTTYPE(pseq)))) \
    get0() const { return m0; } \
  BOOST_PP_SEQ_FOR_EACH_I( \
    WG_PP_PARAMPROXY_TYPE_ACCESSORDCLN, \
    WG_PP_PSEQ_BOUNDRESULTEXISTS(pseq), \
    WG_PP_IDENTITY_2( \
      WG_PP_PSEQ_BOUNDTYPES(pseq), \
      WG_PP_PSEQ_ASSIGNEDTYPES(pseq)))
    
#define WG_PP_PARAMPROXY_OBJ_INITLIST( \
  bound_objs_seq, assigned_values_seq, thisu_marker) \
    WG_PP_SEQ_ENUM( \
      WG_PP_SEQ_REPLACE( \
        bound_objs_seq, \
        thisu_marker, \
        this) \
      assigned_values_seq)

#define WG_PP_PARAMPROXY_TYPE_NAME() \
  WG_PP_FORMAT_NAME(param_proxy_type)
#define WG_PP_PARAMPROXY_OBJ_NAME() \
  WG_PP_FORMAT_NAME(param_proxy)

#define WG_PP_PARAMPROXY_DCLN(pseq) \
  struct WG_PP_PARAMPROXY_TYPE_NAME() \
  { \
    WG_PP_PARAMPROXY_TYPE_MEMBERDECLNS(pseq) \
    WG_PP_PARAMPROxY_TYPE_CTORDCNL(pseq) \
    WG_PP_PARAMPROXY_TYPE_ACCESSORS(pseq) \
  } WG_PP_IDENTITY(;) \
  WG_PP_PARAMPROXY_TYPE_NAME() const & WG_PP_PARAMPROXY_OBJ_NAME() = \
    WG_PP_PARAMPROXY_TYPE_NAME() \
    BOOST_PP_LPAREN() \
      WG_PP_PARAMPROXY_OBJ_INITLIST( \
        WG_PP_PSEQ_BOUNDRESULTOBJECT(pseq)WG_PP_PSEQ_BOUNDOBJECTS(pseq), \
        WG_INERNAL_PSEQ_ASSIGNEDVALUES(pseq), \
        WG_PP_PSEQ_BOUNDOBJECTS_THISU_MARKER(pseq)) \
    BOOST_PP_RPAREN() WG_PP_IDENTITY(;)
    
// BOOST_PP_ENUM functor.
#define WG_PP_PARAMPROXY_OBJ_ELEMACCESS(z, n, obj_name) \
  WG_PP_IDENTITY(obj_name).BOOST_PP_CAT(get,n)()

#define WG_PP_PARAMPROXY_OBJ_ELEMACCESSLIST(pseq, obj_name) \
  BOOST_PP_IIF( \
    WG_PP_PSEQ_BOUNDRESULTEXISTS(pseq), \
    BOOST_PP_ENUM_SHIFTED, \
    BOOST_PP_ENUM) \
    ( \
      WG_PP_PSEQ_TOTALXXX_SiZE(pseq), \
      WG_PP_PARAMPROXY_OBJ_ELEMACCESS, \
      obj_name \
    )
    
// BOOST_PP_SEQ_FOR_EACH_I functor.
#define \
  WG_PP_CALL_PARAM_ENTRY( \
    r, obj_seq, indx, elem) \
      BOOST_PP_IF( \
        WG_PP_TOKENS_STARTS_WITH_THISU( \
          BOOST_PP_SEQ_ELEM(indx, obj_seq)), \
        WG_PP_CAPTUREDTYPE_ADDCONST(elem), \
        WG_PP_CAPTUREDTYPE_VALUE(elem)) \
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
  struct BOOST_PP_CAT(function_name, XXXwgautofunctor) \
  { \
    void operator()(WG_PP_PARAMPROXY_TYPE_NAME() const & param_proxy) \
    { \
      static_cast<void>(param_proxy); \
      BOOST_PP_EXPR_IIF( \
        WG_PP_PSEQ_BOUNDRESULTEXISTS(pseq), \
        param_proxy.get0() = ) \
      this->function_name( \
        WG_PP_PARAMPROXY_OBJ_ELEMACCESSLIST(pseq, param_proxy)); \
    } \
    BOOST_PP_SEQ_HEAD(WG_PP_PSEQ_RETTYPE(pseq)) \
      WG_PP_IDENTITY(function_name) WG_PP_CALL_PARAMLIST(pseq)
    
#define WG_PP_AUTOFUNCTOR_END() \
  } WG_PP_FORMAT_NAME(auto_functor); \
  WG_PP_FORMAT_NAME(auto_functor) \
    BOOST_PP_LPAREN() \
      WG_PP_PARAMPROXY_OBJ_NAME() \
    BOOST_PP_RPAREN() WG_PP_IDENTITY(;)

#define WG_PP_AUTOFUNCTION(function_name, pseq) \
  { \
    WG_PP_PARAMPROXY_DCLN(pseq) \
    WG_PP_AUTOFUNCTOR_START(function_name, pseq)

#define WG_PP_AUTOFUNCTION_END() \
  WG_PP_AUTOFUNCTOR_END() \
  }

#endif //WG_AUTOFUNCTION_HH_
