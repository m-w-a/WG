#ifndef WG_PP_SYMBOLTABLE_HH_
#define WG_PP_SYMBOLTABLE_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP.hh>
#include <WG/Local/Detail/Seq.hh>
#include <WG/Local/Detail/Keywords.hh>

//###########
//Public APIs
//###########

//------
//INPUT:
//------
//assignto_nrmlzd_tuple: { BOOST_PP_NIL | normalized-bound-tuple }
//return_nrmlzd_type: { void | some-token }
//parambind_nrmlzd_tupleseq: { BOOST_PP_NIL | {normalized-bound-tuple}+ }
//paramset_nrmlzd_tupleseq: { BOOST_PP_NIL | {normalized-set-tuple}+ }
//
//normalized-bound-tuple := (explicit-or-deduced-type)(var-name)
//normalized-set-tuple := (explicit-type)(var-name)(value-expr)
//explicit-or-deduced-type := explicit-type | deduced-type
//explicit-type := local(some-token) | localref(some-tokens) | some-token
//deduced-type :=
//  WG_PP_DEDUCEDTYPE
//  { BT | add_const<BT> | add_ref<BT> | add_ref< add_const<BT> > }
//BT := BOOST_TYPEOF(some-token)
//
//-------
//OUTPUT:
//-------
//A SymbolTable whose values are accessible using the below macros.
#define WG_PP_SYMBOLTABLE_CREATE( \
  assignto_nrmlzd_tuple, \
  return_type, \
  parambind_nrmlzd_tupleseq, \
  paramset_nrmlzd_tupleseq) \
    WG_PP_ST_CREATE_IMPL1( \
      assignto_nrmlzd_tuple, \
      return_type, \
      parambind_nrmlzd_tupleseq, \
      paramset_nrmlzd_tupleseq)

//Returns: { BOOST_PP_NIL | (explicit-or-deduced-type) }
#define WG_PP_SYMBOLTABLE_ASSIGNEDTO_TYPE(symtbl) \
  BOOST_PP_ARRAY_ELEM(0, symtbl)

//Returns: { BOOST_PP_NIL | (var-name) }
#define WG_PP_SYMBOLTABLE_ASSIGNEDTO_OBJ(symtbl) \
  BOOST_PP_ARRAY_ELEM(1, symtbl)

//Returns: { 0 | 1 }
#define WG_PP_SYMBOLTABLE_ASSIGNEDTO_EXISTS(symtbl) \
  BOOST_PP_ARRAY_ELEM(2, symtbl)

//Returns: { BOOST_PP_NIL | return-type  }
#define WG_PP_SYMBOLTABLE_RETTYPE(symtbl) \
  BOOST_PP_ARRAY_ELEM(3, symtbl)

//Returns: { BOOST_PP_NIL | {(explicit-or-deduced-type)}+ }
#define WG_PP_SYMBOLTABLE_PARAMBIND_TYPES(symtbl) \
  BOOST_PP_ARRAY_ELEM(4, symtbl)

//Returns: { BOOST_PP_NIL | {(var-name)}+ }
#define WG_PP_SYMBOLTABLE_PARAMBIND_OBJS(symtbl) \
  BOOST_PP_ARRAY_ELEM(5, symtbl)

//Returns: { integer }
#define WG_PP_SYMBOLTABLE_PARAMBIND_XXX_SIZE(symtbl) \
  BOOST_PP_ARRAY_ELEM(6, symtbl)

//Returns: { BOOST_PP_NIL | integer }
#define WG_PP_SYMBOLTABLE_PARAMBIND_OBJS_THISU_MARKER(symtbl) \
  BOOST_PP_ARRAY_ELEM(7, symtbl)

//Returns: { BOOST_PP_NIL | {(explicit-type)}+ }
#define WG_PP_SYMBOLTABLE_PARAMSET_TYPES(symtbl) \
  BOOST_PP_ARRAY_ELEM(8, symtbl)

//Returns: { BOOST_PP_NIL | {(var-name)}+ }
#define WG_PP_SYMBOLTABLE_PARAMSET_OBJS(symtbl) \
  BOOST_PP_ARRAY_ELEM(9, symtbl)

//Returns: { BOOST_PP_NIL | {(value-expr)}+ }
#define WG_PP_SYMBOLTABLE_PARAMSET_VALUES(symtbl) \
  BOOST_PP_ARRAY_ELEM(10, symtbl)

//Returns: { BOOST_PP_NIL | integer }
#define WG_PP_SYMBOLTABLE_PARAMSET_XXX_SIZE(symtbl) \
  BOOST_PP_ARRAY_ELEM(11, symtbl)

//Returns: { BOOST_PP_NIL | integer }
#define WG_PP_SYMBOLTABLE_TOTALXXX_SIZE(symtbl) \
  BOOST_PP_ARRAY_ELEM(12, symtbl)

//###########
//Impl Macros
//###########
  
#define WG_PP_ST_CREATE_IMPL1( \
  assignto_nrmlzd_tuple, \
  return_type, \
  parambind_nrmlzd_tupleseq, \
  paramset_nrmlzd_tupleseq) \
    WG_PP_ST_CREATE_IMPL2( \
      WG_PP_ST_NBOUNDTUPLESEQ_TO_TYPESEQ(assignto_nrmlzd_tuple), \
      WG_PP_ST_NBOUNDTUPLESEQ_TO_OBJSEQ(assignto_nrmlzd_tuple), \
      return_type, \
      WG_PP_ST_NBOUNDTUPLESEQ_TO_TYPESEQ(parambind_nrmlzd_tupleseq), \
      WG_PP_ST_NBOUNDTUPLESEQ_TO_OBJSEQ(parambind_nrmlzd_tupleseq), \
      WG_PP_ST_NSETTUPLESEQ_TO_TYPESEQ(paramset_nrmlzd_tupleseq), \
      WG_PP_ST_NSETTUPLESEQ_TO_OBJSEQ(paramset_nrmlzd_tupleseq), \
      WG_PP_ST_NSETTUPLESEQ_TO_VALUESEQ(paramset_nrmlzd_tupleseq))

#define WG_PP_ST_CREATE_IMPL2( \
  assignto_type_seq, assignto_ob_seq, \
  return_type, \
  parambind_type_seq, parambind_obj_seq, \
  paramset_type_seq, paramset_obj_seq, paramset_value_seq) \
    WG_PP_ST_CREATE_IMPL3( \
      (12, \
        (assignto_type_seq, \
        assignto_ob_seq, \
        WG_PP_SEQ_SIZE(assignto_type_seq), \
        return_type, \
        parambind_type_seq, \
        parambind_obj_seq, \
        WG_PP_SEQ_SIZE(parambind_type_seq), \
        WG_PP_ST_THISU_INDX(parambind_obj_seq), \
        paramset_type_seq, \
        paramset_obj_seq, \
        paramset_value_seq, \
        WG_PP_SEQ_SIZE(paramset_type_seq))) \
    )

#define WG_PP_ST_CREATE_IMPL3(wiparray) \
  BOOST_PP_ARRAY_PUSH_BACK( \
    wiparray, \
    BOOST_PP_ADD( \
      BOOST_PP_ADD( \
        WG_PP_SYMBOLTABLE_PARAMBIND_XXX_SIZE(wiparray), \
        WG_PP_SYMBOLTABLE_PARAMSET_XXX_SIZE(wiparray)), \
        WG_PP_SYMBOLTABLE_ASSIGNEDTO_EXISTS(wiparray)))

//------------------------
//Partitioning Operations.
//------------------------

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_ST_SEQUENCE_IF_INDEX(r, CONDITION, indx, elem) \
  BOOST_PP_EXPR_IF( \
    CONDITION(indx), \
    BOOST_PP_LPAREN() elem BOOST_PP_RPAREN())
    
#define WG_PP_ST_NBOUNDTUPLESEQ_TO_TYPESEQ(nrmlzd_bound_tuple_seq) \
  WG_PP_SEQ_FOR_EACH_I( \
    WG_PP_ST_SEQUENCE_IF_INDEX, \
    WG_PP_IS_EVEN, \
    nrmlzd_bound_tuple_seq)
    
#define WG_PP_ST_NBOUNDTUPLESEQ_TO_OBJSEQ(nrmlzd_bound_tuple_seq) \
  WG_PP_SEQ_FOR_EACH_I( \
    WG_PP_ST_SEQUENCE_IF_INDEX, \
    WG_PP_IS_ODD, \
    nrmlzd_bound_tuple_seq)

#define WG_PP_ST_NSETTUPLESEQ_TO_TYPESEQ(nrmlzd_set_tuple_seq) \
  WG_PP_SEQ_FOR_EACH_I( \
    WG_PP_ST_SEQUENCE_IF_INDEX, \
    WG_PP_IS_MOD3_R0, \
    nrmlzd_set_tuple_seq)
      
#define WG_PP_ST_NSETTUPLESEQ_TO_OBJSEQ(nrmlzd_set_tuple_seq) \
  WG_PP_SEQ_FOR_EACH_I( \
    WG_PP_ST_SEQUENCE_IF_INDEX, \
    WG_PP_IS_MOD3_R1, \
    nrmlzd_set_tuple_seq)

#define WG_PP_ST_NSETTUPLESEQ_TO_VALUESEQ(nrmlzd_set_tuple_seq) \
  WG_PP_SEQ_FOR_EACH_I( \
    WG_PP_ST_SEQUENCE_IF_INDEX, \
    WG_PP_IS_MOD3_R2, \
    nrmlzd_set_tuple_seq)

//----------------------
//Calculate this_ index.
//----------------------

//Returns: { BOOST_PP_NIL | integer }
#define WG_PP_ST_THISU_INDX(bound_obj_seq) \
  WG_PP_ST_THISU_INDX_IMPL( \
    (BOOST_PP_NIL) \
    WG_PP_SEQ_FOR_EACH_I(WG_PP_ST_THISU_MARK_INDX, ~, bound_obj_seq))

#define WG_PP_ST_THISU_INDX_IMPL_0 BOOST_PP_NIL
#define WG_PP_ST_THISU_INDX_IMPL_1(indx) indx
#define WG_PP_ST_THISU_INDX_IMPL(seq) \
  BOOST_PP_CAT( \
    WG_PP_ST_THISU_INDX_IMPL_, \
    WG_PP_ISNEXTTOKEN_A_TUPLE( \
      1, BOOST_PP_TUPLE_EAT(1)seq BOOST_PP_NIL)) BOOST_PP_TUPLE_EAT(1)seq

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_ST_THISU_MARK_INDX(r, data, indx, elem) \
  BOOST_PP_EXPR_IIF( \
    WG_PP_TOKENS_STARTWITH_THISU(elem), \
    (indx))

#endif //WG_PP_SYMBOLTABLE_HH_
