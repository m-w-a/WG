#ifndef WG_AUTOFUNCTION_HH_
#define WG_AUTOFUNCTION_HH_

#include <boost/preprocessor.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <WG/Local/Detail/PP.hh>
#include <WG/Local/Detail/Seq.hh>
#include <WG/Local/Detail/AltSeq.hh>
#include <WG/Local/Detail/Keywords.hh>

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

#define WG_PP_FORMAT_NAME(name) \
  BOOST_PP_CAT(WG_PP_IDENTITY(pgcllXXXautofunctionXXX), name)
    
#define WG_PP_SPECIFIEDTYPE_VALUE(specifiedtype) \
  BOOST_PP_IIF( \
    WG_PP_TOKENS_STARTWITH_LOCAL(specifiedtype), \
    WG_PP_TOKENS_LOCAL_VALUE(specifiedtype), \
    BOOST_PP_IIF( \
      WG_PP_TOKENS_STARTWITH_LOCALREF(specifiedtype), \
      WG_PP_TOKENS_LOCALREF_VALUE(specifiedtype), \
      specifiedtype))
    
#define WG_PP_SPECIFIEDTYPE_ADDCONST(specifiedtype) \
  BOOST_PP_IIF( \
    WG_PP_TOKENS_STARTWITH_LOCALREF(specifiedtype), \
    WG_PP_TOKENS_LOCALREF_VALUE(specifiedtype), \
    BOOST_PP_IIF( \
      WG_PP_TOKENS_STARTWITH_LOCAL(specifiedtype), \
      WG_PP_TOKENS_LOCAL_VALUE(specifiedtype), \
      boost::add_const<WG_PP_IDENTITY(specifiedtype)>::type))

#define WG_PP_SPECIFIEDTYPE_ADDREFERENCE(specifiedtype) \
  BOOST_PP_IIF( \
    WG_PP_TOKENS_STARTWITH_LOCALREF(specifiedtype), \
    WG_PP_TOKENS_LOCALREF_VALUE(specifiedtype), \
    BOOST_PP_IIF( \
      WG_PP_TOKENS_STARTWITH_LOCAL(specifiedtype), \
      WG_PP_TOKENS_LOCAL_VALUE(specifiedtype) &, \
      boost::add_reference<WG_PP_IDENTITY(specifiedtype)>::type))
      
#define WG_PP_SPECIFIEDTYPE_ADDCONST_ADDREF(specifiedtype) \
  BOOST_PP_IIF( \
    WG_PP_TOKENS_STARTWITH_LOCALREF(specifiedtype), \
    WG_PP_TOKENS_LOCALREF_VALUE(specifiedtype), \
    BOOST_PP_IIF( \
      WG_PP_TOKENS_STARTWITH_LOCAL(specifiedtype), \
      WG_PP_TOKENS_LOCAL_VALUE(specifiedtype), \
      boost::add_reference< \
        boost::add_const<WG_PP_IDENTITY(specifiedtype)>::type \
      >::type))

//------------------------
//AssignedPSeq & BoundPSeq
//------------------------

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_SEQUENCE_IF_INDEX(r, CONDITION, indx, elem) \
  BOOST_PP_EXPR_IF( \
    CONDITION(indx), \
    BOOST_PP_LPAREN() elem BOOST_PP_RPAREN())
    
#define WG_PP_BOUNDPSEQ_TO_TYPESEQ(bp_seq) \
  WG_PP_SEQ_FOR_EACH_I( \
    WG_PP_SEQUENCE_IF_INDEX, \
    WG_PP_IS_EVEN, \
    bp_seq)
    
#define WG_PP_BOUNDPSEQ_TO_OBJSEQ(bp_seq) \
  WG_PP_SEQ_FOR_EACH_I( \
    WG_PP_SEQUENCE_IF_INDEX, \
    WG_PP_IS_ODD, \
    bp_seq)

#define WG_PP_ASSIGNEDPSEQ_TO_TYPESEQ(ap_seq) \
  WG_PP_SEQ_FOR_EACH_I( \
    WG_PP_SEQUENCE_IF_INDEX, \
    WG_PP_IS_MOD3_R0, \
    ap_seq)
      
#define WG_PP_ASSIGNEDPSEQ_TO_OBJSEQ(ap_seq) \
  WG_PP_SEQ_FOR_EACH_I( \
    WG_PP_SEQUENCE_IF_INDEX, \
    WG_PP_IS_MOD3_R1, \
    ap_seq)

#define WG_PP_ASSIGNEDPSEQ_TO_VALUESEQ(ap_seq) \
  WG_PP_SEQ_FOR_EACH_I( \
    WG_PP_SEQUENCE_IF_INDEX, \
    WG_PP_IS_MOD3_R2, \
    ap_seq)

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_MARK_THISU_INDX(r, data, indx, elem) \
  BOOST_PP_EXPR_IF( \
    WG_PP_TOKENS_STARTWITH_THISU(elem), \
    (indx))
    
#define WG_PP_THISU_INDX_IMPL_0 BOOST_PP_NIL
#define WG_PP_THISU_INDX_IMPL_1(indx) indx
#define WG_PP_THISU_INDX_IMPL(seq) \
  BOOST_PP_CAT( \
    WG_PP_THISU_INDX_IMPL_, \
    WG_PP_ISNEXTTOKEN_A_TUPLE( \
      1, BOOST_PP_TUPLE_EAT(1)seq BOOST_PP_NIL)) BOOST_PP_TUPLE_EAT(1)seq
  
#define WG_PP_THISU_INDX(bp_obj_seq) \
  WG_PP_THISU_INDX_IMPL( \
    (BOOST_PP_NIL) WG_PP_SEQ_FOR_EACH_I(WG_PP_MARK_THISU_INDX, ~, bp_obj_seq))

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
        WG_PP_SEQ_SIZE(bresult_type_seq), \
        ret_type, \
        bp_type_seq, \
        bp_obj_seq, \
        WG_PP_SEQ_SIZE(bp_type_seq), \
        WG_PP_THISU_INDX(bp_obj_seq), \
        ap_type_seq, \
        ap_obj_seq, \
        ap_value_seq, \
        WG_PP_SEQ_SIZE(ap_type_seq))) \
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
  BOOST_PP_IIF( \
    BOOST_PP_AND( \
      BOOST_PP_EQUAL(BOOST_PP_SEQ_SIZE(bp_seq), 1), \
      WG_PP_TOKENS_STARTWITH_VOID( \
        BOOST_PP_EXPAND(WG_PP_IDENTITY bp_seq BOOST_PP_NIL))), \
      1, \
      0)

#define WG_PP_ASSIGNED_PSEQ_IS_VOID(ap_alt_seq) \
  BOOST_PP_IF( \
    WG_PP_ISNEXTTOKEN_A_TUPLE( \
      2, BOOST_PP_TUPLE_EAT(1) ap_alt_seq BOOST_PP_NIL), \
    0, \
    BOOST_PP_IF( \
      WG_PP_TOKENS_STARTWITH_VOID( \
        BOOST_PP_EXPAND(WG_PP_IDENTITY ap_alt_seq BOOST_PP_NIL)), \
      1, \
      0))

//TODO
//BOOST_PP_EXPR_IF( \
//  BOOST_PP_AND( \
//    BOOST_PP_NOT(WG_PP_BOUND_PSEQ_IS_VOID(bp_seq)), \
//    BOOST_PP_NOT(WG_PP_IS_EVEN(WG_PP_SEQ_SIZE(bp_seq)))), \
//  BOOST_PP_ASSERT_MSG( \
//    0, "The second parameter to WG_AUTOFUNCTION is malformed.")) \
//\
//BOOST_PP_EXPR_IF( \
//  BOOST_PP_AND( \
//    BOOST_PP_NOT(WG_PP_ASSIGNED_PSEQ_IS_VOID(ap_alt_seq)), \
//    BOOST_PP_NOT(WG_PP_IS_MOD3_R0(WG_PP_SEQ_SIZE(ap_alt_seq)))), \
//  BOOST_PP_ASSERT_MSG( \
//    0, "The third parameter to WG_AUTOFUNCTION is malformed.")) \
//\
//
//PSEQ:
//  See below for detail of PSEQ structure access.
#define WG_PP_MAKE_PSEQ(bresult_seq, ret_type, bp_seq, ap_alt_seq) \
  WG_PP_MAKE_PSEQ_IMPL1( \
    BOOST_PP_IIF( \
      WG_PP_BOUND_PSEQ_IS_VOID(bresult_seq), \
      BOOST_PP_NIL, \
      bresult_seq), \
    ret_type, \
    BOOST_PP_IIF( \
      WG_PP_BOUND_PSEQ_IS_VOID(bp_seq), \
      BOOST_PP_NIL, \
      bp_seq), \
    BOOST_PP_IIF( \
      WG_PP_ASSIGNED_PSEQ_IS_VOID(ap_alt_seq), \
      BOOST_PP_NIL, \
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
#define WG_PP_PSEQ_TOTALXXX_SIZE(pseq) \
  BOOST_PP_ARRAY_ELEM(12, pseq)

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_PARAMPROXY_TYPE_MEMBER(r, offset, indx, elem) \
  WG_PP_SPECIFIEDTYPE_ADDCONST_ADDREF(elem) \
      BOOST_PP_CAT(m, BOOST_PP_ADD(indx,offset)) WG_PP_IDENTITY(;)

#define WG_PP_PARAMPROXY_TYPE_MEMBERDECLNS(pseq) \
  BOOST_PP_EXPR_IIF( \
    WG_PP_PSEQ_BOUNDRESULTEXISTS(pseq), \
    WG_PP_SPECIFIEDTYPE_ADDREFERENCE( \
      BOOST_PP_EXPAND(WG_PP_IDENTITY WG_PP_PSEQ_BOUNDRESULTTYPE(pseq))) \
    m0;) \
  WG_PP_SEQ_IFNIL_THENCLEAR( \
    WG_PP_SEQ_FOR_EACH_I( \
      WG_PP_PARAMPROXY_TYPE_MEMBER, \
      WG_PP_PSEQ_BOUNDRESULTEXISTS(pseq), \
      WG_PP_SEQ_CAT( \
        WG_PP_PSEQ_BOUNDTYPES(pseq), \
        WG_PP_PSEQ_ASSIGNEDTYPES(pseq))))

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_PARAMPROXY_TYPE_CTORPARAM(r, offset, indx, elem) \
  BOOST_PP_LPAREN() \
    WG_PP_SPECIFIEDTYPE_ADDCONST_ADDREF(elem) \
      BOOST_PP_CAT(p, BOOST_PP_ADD(indx,offset)) \
  BOOST_PP_RPAREN()

#define WG_PP_PARAMPROXY_TYPE_CTORPARAMLIST(pseq) \
  BOOST_PP_IIF( \
    WG_PP_PSEQ_BOUNDRESULTEXISTS(pseq), \
    WG_PP_SPECIFIEDTYPE_ADDREFERENCE( \
      BOOST_PP_EXPAND(WG_PP_IDENTITY WG_PP_PSEQ_BOUNDRESULTTYPE(pseq))) \
    p0 \
    BOOST_PP_IIF( \
      BOOST_PP_GREATER(WG_PP_PSEQ_TOTALXXX_SIZE(pseq), 1), \
      BOOST_PP_COMMA, \
      BOOST_PP_EMPTY), \
    BOOST_PP_EMPTY)() \
  WG_PP_SEQ_ENUM( \
    WG_PP_SEQ_FOR_EACH_I( \
      WG_PP_PARAMPROXY_TYPE_CTORPARAM, \
      WG_PP_PSEQ_BOUNDRESULTEXISTS(pseq), \
      WG_PP_SEQ_CAT( \
        WG_PP_PSEQ_BOUNDTYPES(pseq), \
        WG_PP_PSEQ_ASSIGNEDTYPES(pseq))))
  
// BOOST_PP_ENUM functor.
#define WG_PP_PARAMPROXY_TYPE_CTORINITENTRY(z, indx, data) \
  BOOST_PP_CAT(m, indx)BOOST_PP_LPAREN()BOOST_PP_CAT(p, indx)BOOST_PP_RPAREN()
  
#define WG_PP_PARAMPROXY_TYPE_CTORINITLIST(pseq) \
  BOOST_PP_ENUM( \
    WG_PP_PSEQ_TOTALXXX_SIZE(pseq), \
    WG_PP_PARAMPROXY_TYPE_CTORINITENTRY, \
    ~)
  
#define WG_PP_PARAMPROxY_TYPE_CTORDCNL(pseq) \
  WG_PP_PARAMPROXY_TYPE_NAME() \
    BOOST_PP_LPAREN() \
      WG_PP_PARAMPROXY_TYPE_CTORPARAMLIST(pseq) \
    BOOST_PP_RPAREN() \
      BOOST_PP_EXPR_IF(WG_PP_PSEQ_TOTALXXX_SIZE(pseq), WG_PP_IDENTITY(:)) \
      WG_PP_PARAMPROXY_TYPE_CTORINITLIST(pseq) \
    {}

// BOOST_PP_ENUM functor.
#define WG_PP_PARAMPROXY_TYPE_ACCESSORDCLN(r, offset, indx, elem) \
  WG_PP_SPECIFIEDTYPE_ADDCONST_ADDREF(elem) \
    BOOST_PP_CAT(get, BOOST_PP_ADD(indx,offset)) () const \
  { \
    return BOOST_PP_CAT(m, BOOST_PP_ADD(indx,offset)); \
  }
    
#define WG_PP_PARAMPROXY_TYPE_ACCESSORS(pseq) \
  BOOST_PP_EXPR_IIF( \
    WG_PP_PSEQ_BOUNDRESULTEXISTS(pseq), \
    WG_PP_SPECIFIEDTYPE_ADDREFERENCE( \
      BOOST_PP_EXPAND(WG_PP_IDENTITY WG_PP_PSEQ_BOUNDRESULTTYPE(pseq))) \
    get0() const { return m0; }) \
  WG_PP_SEQ_IFNIL_THENCLEAR( \
    WG_PP_SEQ_FOR_EACH_I( \
      WG_PP_PARAMPROXY_TYPE_ACCESSORDCLN, \
      WG_PP_PSEQ_BOUNDRESULTEXISTS(pseq), \
      WG_PP_SEQ_CAT( \
        WG_PP_PSEQ_BOUNDTYPES(pseq), \
        WG_PP_PSEQ_ASSIGNEDTYPES(pseq))))
    
#define WG_PP_PARAMPROXY_OBJ_INITLIST( \
  bound_objs_seq, assigned_values_seq, thisu_marker) \
    WG_PP_SEQ_ENUM( \
      WG_PP_SEQ_CAT( \
        WG_PP_SEQ_REPLACE( \
          bound_objs_seq, \
          thisu_marker, \
          this), \
        assigned_values_seq))

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
        WG_PP_SEQ_CAT( \
          WG_PP_PSEQ_BOUNDRESULTOBJECT(pseq), \
          WG_PP_PSEQ_BOUNDOBJECTS(pseq)), \
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
      WG_PP_PSEQ_TOTALXXX_SIZE(pseq), \
      WG_PP_PARAMPROXY_OBJ_ELEMACCESS, \
      obj_name \
    )
    
// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_CALL_PARAM_ENTRY(r, obj_seq, indx, elem) \
  BOOST_PP_LPAREN() \
    BOOST_PP_IF( \
      WG_PP_TOKENS_STARTWITH_THISU(WG_PP_SEQ_ELEM(indx, obj_seq)), \
      WG_PP_SPECIFIEDTYPE_ADDCONST(elem), \
      WG_PP_SPECIFIEDTYPE_VALUE(elem)) \
    WG_PP_SEQ_ELEM(indx, obj_seq) \
  BOOST_PP_RPAREN()

#define WG_PP_CALL_PARAMLIST(pseq) \
  BOOST_PP_LPAREN() \
    WG_PP_SEQ_ENUM( \
      WG_PP_SEQ_FOR_EACH_I( \
        WG_PP_CALL_PARAM_ENTRY, \
        WG_PP_SEQ_CAT( \
          WG_PP_PSEQ_BOUNDOBJECTS(pseq), \
          WG_PP_PSEQ_ASSIGNEDOBJECTS(pseq)), \
        WG_PP_SEQ_CAT( \
          WG_PP_PSEQ_BOUNDTYPES(pseq), \
          WG_PP_PSEQ_ASSIGNEDTYPES(pseq)))) \
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
    BOOST_PP_EXPAND(WG_PP_IDENTITY WG_PP_PSEQ_RETTYPE(pseq)) \
      function_name WG_PP_CALL_PARAMLIST(pseq)
    
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
