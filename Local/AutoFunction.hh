#ifndef WG_AUTOFUNCTION_HH_
#define WG_AUTOFUNCTION_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP.hh>
#include <WG/Local/Detail/Seq.hh>
#include <WG/Local/Detail/AltSeq.hh>
#include <WG/Local/Detail/Keywords.hh>
#include <WG/Local/Detail/BackEnd/AutoFunction/CodeGen.hh>

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
    WG_PP_AUTOFUNCTOR_CODEGEN_START( \
      function_name, \
      WG_PP_MAKE_PSEQ( \
        bound_result_seq, ret_type, bound_param_seq, assigned_param_seq))
    
#define WG_AUTOFUNCTION_END WG_PP_AUTOFUNCTOR_CODEGEN_END()

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
    BOOST_PP_SEQ_ELEM(0, ret_type), \
    BOOST_PP_IIF( \
      WG_PP_BOUND_PSEQ_IS_VOID(bp_seq), \
      BOOST_PP_NIL, \
      bp_seq), \
    BOOST_PP_IIF( \
      WG_PP_ASSIGNED_PSEQ_IS_VOID(ap_alt_seq), \
      BOOST_PP_NIL, \
      WG_PP_ALTSEQ_LINEARIZE(ap_alt_seq)))

#endif //WG_AUTOFUNCTION_HH_
