#ifndef WG_AUTOFUNCTION_HH_
#define WG_AUTOFUNCTION_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP.hh>
#include <WG/Local/Detail/Seq.hh>
#include <WG/Local/Detail/AltSeq.hh>
#include <WG/Local/Detail/Keywords.hh>

#include <WG/Local/Detail/BackEnd/AutoFunction/CodeGen.hh>
#include <WG/Local/Detail/BackEnd/SymbolTable.hh>
#include <WG/Local/Detail/BackEnd/Type.hh>

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

//------------------------
//AssignedPSeq & BoundPSeq
//------------------------

#define WG_PP_BOUND_PSEQ_IS_VOID(bp_seq) \
  BOOST_PP_IIF( \
    BOOST_PP_AND( \
      BOOST_PP_EQUAL(BOOST_PP_SEQ_SIZE(bp_seq), 1), \
      WG_PP_TOKENS_STARTWITH_VOID( \
        BOOST_PP_EXPAND(WG_PP_IDENTITY bp_seq BOOST_PP_NIL))), \
      1, \
      0)

#define WG_PP_ASSIGNED_PSEQ_IS_VOID(ap_alt_seq) \
  BOOST_PP_IIF( \
    WG_PP_ISNEXTTOKEN_A_TUPLE( \
      2, BOOST_PP_TUPLE_EAT(1) ap_alt_seq BOOST_PP_NIL), \
    0, \
    BOOST_PP_IIF( \
      WG_PP_TOKENS_STARTWITH_VOID( \
        BOOST_PP_EXPAND(WG_PP_IDENTITY ap_alt_seq BOOST_PP_NIL)), \
      1, \
      0))

#define WG_PP_MAKE_PSEQ(bresult_seq, ret_type, bp_seq, ap_alt_seq) \
  WG_PP_SYMBOLTABLE_CREATE( \
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


#define WG_PP_PARAMPROXY_TYPE_NAME() \
  WG_PP_AUTOFUNCTION_CG_FORMATNAME(param_proxy_type)
#define WG_PP_PARAMPROXY_OBJ_NAME() \
  WG_PP_AUTOFUNCTION_CG_FORMATNAME(param_proxy)

//// BOOST_PP_ENUM functor.
//#define WG_PP_PARAMPROXY_OBJ_ELEMACCESS(z, n, obj_name) \
//  WG_PP_IDENTITY(obj_name).BOOST_PP_CAT(get,n)()
//
//#define WG_PP_PARAMPROXY_OBJ_ELEMACCESSLIST(pseq, obj_name) \
//  BOOST_PP_IIF( \
//    WG_PP_SYMBOLTABLE_ASSIGNEDTO_EXISTS(pseq), \
//    BOOST_PP_ENUM_SHIFTED, \
//    BOOST_PP_ENUM) \
//    ( \
//      WG_PP_SYMBOLTABLE_TOTALXXX_SIZE(pseq), \
//      WG_PP_PARAMPROXY_OBJ_ELEMACCESS, \
//      obj_name \
//    )
    
// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_CALL_PARAM_ENTRY(r, obj_seq, indx, elem) \
  BOOST_PP_LPAREN() \
    BOOST_PP_IIF( \
      WG_PP_TOKENS_STARTWITH_THISU(WG_PP_SEQ_ELEM(indx, obj_seq)), \
      WG_PP_PARSEDTYPE_IFNONLOCAL_ADDCONST(elem), \
      WG_PP_PARSEDTYPE_EXTRACTCPPTYPE(elem)) \
    WG_PP_SEQ_ELEM(indx, obj_seq) \
  BOOST_PP_RPAREN()

#define WG_PP_CALL_PARAMLIST(pseq) \
  BOOST_PP_LPAREN() \
    WG_PP_SEQ_ENUM( \
      WG_PP_SEQ_FOR_EACH_I( \
        WG_PP_CALL_PARAM_ENTRY, \
        WG_PP_SEQ_JOIN( \
          WG_PP_SYMBOLTABLE_PARAMBIND_OBJS(pseq), \
          WG_PP_SYMBOLTABLE_PARAMSET_OBJS(pseq)), \
        WG_PP_SEQ_JOIN( \
          WG_PP_SYMBOLTABLE_PARAMBIND_TYPES(pseq), \
          WG_PP_SYMBOLTABLE_PARAMSET_TYPES(pseq)))) \
  BOOST_PP_RPAREN()

#define WG_PP_AUTOFUNCTOR_START(function_name, pseq) \
  struct BOOST_PP_CAT(function_name, XXXwgautofunctor) \
  { \
    void operator()(WG_PP_PARAMPROXY_TYPE_NAME() const & param_proxy) \
    { \
      static_cast<void>(param_proxy); \
      BOOST_PP_EXPR_IIF( \
        WG_PP_SYMBOLTABLE_ASSIGNEDTO_EXISTS(pseq), \
        param_proxy.get0() = ) \
      this->function_name( \
        WG_PP_PARAMPROXY_OBJ_ELEMACCESSLIST(pseq, param_proxy)); \
    } \
    BOOST_PP_EXPAND(WG_PP_IDENTITY WG_PP_SYMBOLTABLE_RETTYPE(pseq)) \
      function_name WG_PP_CALL_PARAMLIST(pseq)
    
#define WG_PP_AUTOFUNCTOR_END() \
  } WG_PP_AUTOFUNCTION_CG_FORMATNAME(auto_functor); \
  WG_PP_AUTOFUNCTION_CG_FORMATNAME(auto_functor) \
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
