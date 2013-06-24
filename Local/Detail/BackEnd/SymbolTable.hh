#ifndef WG_PP_SYMBOLTABLE_HH_
#define WG_PP_SYMBOLTABLE_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP.hh>
#include <WG/Local/Detail/Seq.hh>
#include <WG/Local/Detail/Keywords.hh>

//###########
//Public APIs
//###########

//-----
//NOTE:
//-----
//
//What ever terms not defined here are defined in the respective BNF.
//------
//INPUT:
//------
//assignto_nrmlzd_tuple: { BOOST_PP_NIL | normalized-bound-tuple }
//return_nrmlzd_type: { BOOST_PP_NIL | type }
//parambind_nrmlzd_tupleseq: { BOOST_PP_NIL | {normalized-bound-tuple}+ }
//paramset_nrmlzd_tupleseq: { BOOST_PP_NIL | {normalized-set-tuple}+ }
//
//normalized-bound-tuple := (parsed-explicit-or-deduced-type)(var-name)
//normalized-set-tuple := (parsed-explicit-type)(var-name)(value-expr)
//parsed-explicit-or-deduced-type := parsed-explicit-type | parsed-deduced-type
//parsed-explicit-type := parsed-local-type | non-local-type
//parsed-local-type := local(some-token) lib-type-qualifier-seq
//lib-type-qualifier-seq := (const) | (ref) | (const)(ref)
//parsed-deduced-type :=
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

//Returns: { BOOST_PP_NIL | (parsed-explicit-or-deduced-type) }
#define WG_PP_SYMBOLTABLE_TYPESEQ_ASSIGNEE(symbtbl) \
  WG_PP_SYMBOLTABLE_GET(symbtbl, TYPESEQ_ASSIGNEE)

//Returns: { BOOST_PP_NIL | (var-name) }
#define WG_PP_SYMBOLTABLE_OBJSEQ_ASSIGNEE(symbtbl) \
  WG_PP_SYMBOLTABLE_GET(symbtbl, OBJSEQ_ASSIGNEE)

//See WG_PP_SYMBOLTABLE_OBJSEQ_ASSIGNEE.
#define WG_PP_SYMBOLTABLE_VALUESEQ_ASSIGNEE(symbtbl) \
  WG_PP_SYMBOLTABLE_OBJSEQ_ASSIGNEE(symbtbl)

//Returns: { 0 | 1 }
#define WG_PP_SYMBOLTABLE_EXISTS_ASSIGNEE(symbtbl) \
  WG_PP_SYMBOLTABLE_GET(symbtbl, EXISTS_ASSIGNEE)

#define WG_PP_SYMBOLTABLE_XXX_SIZE_ASSIGNEE(symbtbl) \
  WG_PP_SYMBOLTABLE_EXISTS_ASSIGNEE(symbtbl)

//Returns: { BOOST_PP_NIL | return-type  }
#define WG_PP_SYMBOLTABLE_RETTYPE(symbtbl) \
  WG_PP_SYMBOLTABLE_GET(symbtbl, RETTYPE)

//Returns: { 0 | 1 }
#define WG_PP_SYMBOLTABLE_EXISTS_RETTYPE(symbtbl) \
  BOOST_PP_NOT( \
    WG_PP_TOKENS_START_WITH_BOOST_PP_NIL( \
      WG_PP_SYMBOLTABLE_RETTYPE(symbtbl) ))

//Returns: { BOOST_PP_NIL | {(parsed-explicit-or-deduced-type)}+ }
#define WG_PP_SYMBOLTABLE_TYPESEQ_BOUNDPARAM(symbtbl) \
  WG_PP_SYMBOLTABLE_GET(symbtbl, TYPESEQ_BOUNDPARAM)

//Returns: { BOOST_PP_NIL | {(var-name)}+ }
#define WG_PP_SYMBOLTABLE_OBJSEQ_BOUNDPARAM(symbtbl) \
  WG_PP_SYMBOLTABLE_GET(symbtbl, OBJSEQ_BOUNDPARAM)

//See WG_PP_SYMBOLTABLE_OBJSEQ_BOUNDPARAM.
#define WG_PP_SYMBOLTABLE_VALUESEQ_BOUNDPARAM(symbtbl) \
  WG_PP_SYMBOLTABLE_OBJSEQ_BOUNDPARAM(symbtbl)

//Returns: { integer }
#define WG_PP_SYMBOLTABLE_XXX_SIZE_BOUNDPARAM(symbtbl) \
  WG_PP_SYMBOLTABLE_GET(symbtbl, XXX_SIZE_BOUNDPARAM)

//Returns: { BOOST_PP_NIL | integer }
#define WG_PP_SYMBOLTABLE_OBJSEQ_THISU_MARKER_BOUNDPARAM(symbtbl) \
  WG_PP_SYMBOLTABLE_GET(symbtbl, OBJSEQ_THISU_MARKER_BOUNDPARAM)

//Returns: { BOOST_PP_NIL | {(parsed-explicit-type)}+ }
#define WG_PP_SYMBOLTABLE_TYPESEQ_SETPARAM(symbtbl) \
  WG_PP_SYMBOLTABLE_GET(symbtbl, TYPESEQ_SETPARAM)

//Returns: { BOOST_PP_NIL | {(var-name)}+ }
#define WG_PP_SYMBOLTABLE_OBJSEQ_SETPARAM(symbtbl) \
  WG_PP_SYMBOLTABLE_GET(symbtbl, OBJSEQ_SETPARAM)

//Returns: { BOOST_PP_NIL | {(value-expr)}+ }
#define WG_PP_SYMBOLTABLE_VALUESEQ_SETPARAM(symbtbl) \
  WG_PP_SYMBOLTABLE_GET(symbtbl, VALUESEQ_SETPARAM)

//Returns: { BOOST_PP_NIL | integer }
#define WG_PP_SYMBOLTABLE_XXX_SIZE_SETPARAM(symbtbl) \
  WG_PP_SYMBOLTABLE_GET(symbtbl, XXX_SIZE_SETPARAM)

//Returns: { BOOST_PP_NIL | integer }
#define WG_PP_SYMBOLTABLE_TOTALXXX_SIZE(symbtbl) \
  WG_PP_SYMBOLTABLE_GET(symbtbl, TOTALXXX_SIZE)

//###########
//Impl Macros
//###########

#define WG_PP_SYMBOLTABLE_INDX_TYPESEQ_ASSIGNEE 0
#define WG_PP_SYMBOLTABLE_INDX_OBJSEQ_ASSIGNEE 1
#define WG_PP_SYMBOLTABLE_INDX_EXISTS_ASSIGNEE 2
#define WG_PP_SYMBOLTABLE_INDX_RETTYPE 3
#define WG_PP_SYMBOLTABLE_INDX_TYPESEQ_BOUNDPARAM 4
#define WG_PP_SYMBOLTABLE_INDX_OBJSEQ_BOUNDPARAM 5
#define WG_PP_SYMBOLTABLE_INDX_XXX_SIZE_BOUNDPARAM 6
#define WG_PP_SYMBOLTABLE_INDX_OBJSEQ_THISU_MARKER_BOUNDPARAM 7
#define WG_PP_SYMBOLTABLE_INDX_TYPESEQ_SETPARAM 8
#define WG_PP_SYMBOLTABLE_INDX_OBJSEQ_SETPARAM 9
#define WG_PP_SYMBOLTABLE_INDX_VALUESEQ_SETPARAM 10
#define WG_PP_SYMBOLTABLE_INDX_XXX_SIZE_SETPARAM 11
#define WG_PP_SYMBOLTABLE_INDX_TOTALXXX_SIZE 12

// suffix: must match one of the following: WG_PP_SYMBOLTABLE_INDX_<suffix>
#define WG_PP_SYMBOLTABLE_GET(symbtbl, suffix) \
  BOOST_PP_ARRAY_ELEM( \
    BOOST_PP_CAT(WG_PP_SYMBOLTABLE_INDX_, suffix), \
    symbtbl)

//---------------
//Creation Macros
//---------------

#define WG_PP_ST_CREATE_IMPL1( \
  assignto_nrmlzd_tuple, \
  return_type, \
  parambind_nrmlzd_tupleseq, \
  paramset_nrmlzd_tupleseq) \
    WG_PP_ST_CREATE_IMPL2( \
      WG_PP_STUTIL_BOUNDTUPLESEQ_TO_TYPESEQ(assignto_nrmlzd_tuple), \
      WG_PP_STUTIL_BOUNDTUPLESEQ_TO_OBJSEQ(assignto_nrmlzd_tuple), \
      return_type, \
      WG_PP_STUTIL_BOUNDTUPLESEQ_TO_TYPESEQ(parambind_nrmlzd_tupleseq), \
      WG_PP_STUTIL_BOUNDTUPLESEQ_TO_OBJSEQ(parambind_nrmlzd_tupleseq), \
      WG_PP_STUTIL_SETTUPLESEQ_TO_TYPESEQ(paramset_nrmlzd_tupleseq), \
      WG_PP_STUTIL_SETTUPLESEQ_TO_OBJSEQ(paramset_nrmlzd_tupleseq), \
      WG_PP_STUTIL_SETTUPLESEQ_TO_VALUESEQ(paramset_nrmlzd_tupleseq))

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
        WG_PP_STUTIL_THISU_INDX(parambind_obj_seq), \
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
        WG_PP_SYMBOLTABLE_XXX_SIZE_BOUNDPARAM(wiparray), \
        WG_PP_SYMBOLTABLE_XXX_SIZE_SETPARAM(wiparray)), \
        WG_PP_SYMBOLTABLE_XXX_SIZE_ASSIGNEE(wiparray)))

#endif //WG_PP_SYMBOLTABLE_HH_
