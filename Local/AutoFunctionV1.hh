#ifndef WG_AUTOFUNCTIONV1_HH_
#define WG_AUTOFUNCTIONV1_HH_

#include <WG/Local/Detail/FrontEnd/AutoFunctionV1/SpecNormalize.hh>
#include <WG/Local/Detail/BackEnd/AutoFunction/CodeGen.hh>

//###########
//Public APIs
//###########

#define WG_AUTOFUNCTION_BIND( \
  bound_result_seq, \
  ret_type, \
  function_name, \
  bound_param_seq) \
    WG_AUTOFUNCTIONV1( \
      bound_result_seq, ret_type, function_name, bound_param_seq, (void))

#define WG_AUTOFUNCTION_ASSIGN( \
  bound_result_seq, \
  ret_type, \
  function_name, \
  assigned_param_seq) \
    WG_AUTOFUNCTIONV1( \
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
#define WG_AUTOFUNCTIONV1( \
  bound_result_seq, ret_type, function_name, bound_param_seq, assigned_param_seq) \
    WG_PP_AUTOFUNCTOR_CODEGEN_START( \
      function_name, \
      WG_PP_AUTOFUNCTIONV1_SPECNORMALIZE( \
        bound_result_seq, ret_type, bound_param_seq, assigned_param_seq))
    
#define WG_AUTOFUNCTION_END WG_PP_AUTOFUNCTOR_CODEGEN_END()

//###########
//Impl Macros
//###########



#endif //WG_AUTOFUNCTIONV1_HH_
