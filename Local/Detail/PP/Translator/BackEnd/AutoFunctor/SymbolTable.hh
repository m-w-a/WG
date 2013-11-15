#ifndef WG_PP_AUTOFUNCTOR_SYMBOLTABLE_HH_
#define WG_PP_AUTOFUNCTOR_SYMBOLTABLE_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/Seq.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/SymbolTableUtil.hh>

//################
//Interface Impls.
//################

#define WG_PP_AUTOFUNCTOR_SYMBOLTABLE_ISTPL(symbtbl) \
  WG_PP_AUTOFUNCTOR_ST_GET(symbtbl, ISTPL)

//Returns: { BOOST_PP_NIL | (parsed-explicit-or-deduced-type) }
#define WG_PP_AUTOFUNCTOR_SYMBOLTABLE_TYPESEQ_ASSIGNEE(symbtbl) \
  WG_PP_AUTOFUNCTOR_ST_GET(symbtbl, TYPESEQ_ASSIGNEE)

//Returns: { BOOST_PP_NIL | (var-name) }
#define WG_PP_AUTOFUNCTOR_SYMBOLTABLE_OBJSEQ_ASSIGNEE(symbtbl) \
  WG_PP_AUTOFUNCTOR_ST_GET(symbtbl, OBJSEQ_ASSIGNEE)

//See WG_PP_AUTOFUNCTOR_SYMBOLTABLE_OBJSEQ_ASSIGNEE.
#define WG_PP_AUTOFUNCTOR_SYMBOLTABLE_VALUESEQ_ASSIGNEE(symbtbl) \
  WG_PP_AUTOFUNCTOR_SYMBOLTABLE_OBJSEQ_ASSIGNEE(symbtbl)

//Returns: { 0 | 1 }
#define WG_PP_AUTOFUNCTOR_SYMBOLTABLE_EXISTS_ASSIGNEE(symbtbl) \
  WG_PP_AUTOFUNCTOR_ST_GET(symbtbl, EXISTS_ASSIGNEE)

#define WG_PP_AUTOFUNCTOR_SYMBOLTABLE_XXX_SIZE_ASSIGNEE(symbtbl) \
  WG_PP_AUTOFUNCTOR_SYMBOLTABLE_EXISTS_ASSIGNEE(symbtbl)

//Returns: { BOOST_PP_NIL | return-type  }
#define WG_PP_AUTOFUNCTOR_SYMBOLTABLE_RETTYPE(symbtbl) \
  WG_PP_AUTOFUNCTOR_ST_GET(symbtbl, RETTYPE)

//Returns: { 0 | 1 }
#define WG_PP_AUTOFUNCTOR_SYMBOLTABLE_EXISTS_RETTYPE(symbtbl) \
  BOOST_PP_NOT( \
    WG_PP_STARTSWITH_BOOST_PP_NIL( \
      WG_PP_AUTOFUNCTOR_SYMBOLTABLE_RETTYPE(symbtbl) ))

//Returns: { BOOST_PP_NIL | {(parsed-explicit-or-deduced-type)}+ }
#define WG_PP_AUTOFUNCTOR_SYMBOLTABLE_TYPESEQ_BOUNDPARAM(symbtbl) \
  WG_PP_AUTOFUNCTOR_ST_GET(symbtbl, TYPESEQ_BOUNDPARAM)

//Returns: { BOOST_PP_NIL | {(var-name)}+ }
#define WG_PP_AUTOFUNCTOR_SYMBOLTABLE_OBJSEQ_BOUNDPARAM(symbtbl) \
  WG_PP_AUTOFUNCTOR_ST_GET(symbtbl, OBJSEQ_BOUNDPARAM)

//See WG_PP_AUTOFUNCTOR_SYMBOLTABLE_OBJSEQ_BOUNDPARAM.
#define WG_PP_AUTOFUNCTOR_SYMBOLTABLE_VALUESEQ_BOUNDPARAM(symbtbl) \
  WG_PP_AUTOFUNCTOR_SYMBOLTABLE_OBJSEQ_BOUNDPARAM(symbtbl)

//Returns: { integer }
#define WG_PP_AUTOFUNCTOR_SYMBOLTABLE_XXX_SIZE_BOUNDPARAM(symbtbl) \
  WG_PP_AUTOFUNCTOR_ST_GET(symbtbl, XXX_SIZE_BOUNDPARAM)

//Returns: { BOOST_PP_NIL | integer }
#define WG_PP_AUTOFUNCTOR_SYMBOLTABLE_OBJSEQ_THISU_MARKER_BOUNDPARAM(symbtbl) \
  WG_PP_AUTOFUNCTOR_ST_GET(symbtbl, OBJSEQ_THISU_MARKER_BOUNDPARAM)

//Returns: { BOOST_PP_NIL | {(parsed-explicit-type-or-deduced-type)}+ }
#define WG_PP_AUTOFUNCTOR_SYMBOLTABLE_TYPESEQ_SETPARAM(symbtbl) \
  WG_PP_AUTOFUNCTOR_ST_GET(symbtbl, TYPESEQ_SETPARAM)

//Returns: { BOOST_PP_NIL | {(var-name)}+ }
#define WG_PP_AUTOFUNCTOR_SYMBOLTABLE_OBJSEQ_SETPARAM(symbtbl) \
  WG_PP_AUTOFUNCTOR_ST_GET(symbtbl, OBJSEQ_SETPARAM)

//Returns: { BOOST_PP_NIL | {(value-expr)}+ }
#define WG_PP_AUTOFUNCTOR_SYMBOLTABLE_VALUESEQ_SETPARAM(symbtbl) \
  WG_PP_AUTOFUNCTOR_ST_GET(symbtbl, VALUESEQ_SETPARAM)

//Returns: { integer }
#define WG_PP_AUTOFUNCTOR_SYMBOLTABLE_XXX_SIZE_SETPARAM(symbtbl) \
  WG_PP_AUTOFUNCTOR_ST_GET(symbtbl, XXX_SIZE_SETPARAM)

//Returns: { BOOST_PP_NIL | {(parsed-explicit-or-deduced-type)}+ }
#define WG_PP_AUTOFUNCTOR_SYMBOLTABLE_TYPESEQ_BOUNDMEM(symbtbl) \
  WG_PP_AUTOFUNCTOR_ST_GET(symbtbl, TYPESEQ_BOUNDMEM)

//Returns: { BOOST_PP_NIL | {(var-name)}+ }
#define WG_PP_AUTOFUNCTOR_SYMBOLTABLE_OBJSEQ_BOUNDMEM(symbtbl) \
  WG_PP_AUTOFUNCTOR_ST_GET(symbtbl, OBJSEQ_BOUNDMEM)

//Returns: { integer }
#define WG_PP_AUTOFUNCTOR_SYMBOLTABLE_XXX_SIZE_BOUNDMEM(symbtbl) \
  WG_PP_AUTOFUNCTOR_ST_GET(symbtbl, XXX_SIZE_BOUNDMEM)

//Returns: { BOOST_PP_NIL | integer }
#define WG_PP_AUTOFUNCTOR_SYMBOLTABLE_OBJSEQ_THISU_MARKER_BOUNDMEM(symbtbl) \
  WG_PP_AUTOFUNCTOR_ST_GET(symbtbl, OBJSEQ_THISU_MARKER_BOUNDMEM)

//Returns: { BOOST_PP_NIL | {(parsed-explicit-type-or-deduced-type)}+ }
#define WG_PP_AUTOFUNCTOR_SYMBOLTABLE_TYPESEQ_SETMEM(symbtbl) \
  WG_PP_AUTOFUNCTOR_ST_GET(symbtbl, TYPESEQ_SETMEM)

//Returns: { BOOST_PP_NIL | {(var-name)}+ }
#define WG_PP_AUTOFUNCTOR_SYMBOLTABLE_OBJSEQ_SETMEM(symbtbl) \
  WG_PP_AUTOFUNCTOR_ST_GET(symbtbl, OBJSEQ_SETMEM)

//Returns: { BOOST_PP_NIL | {(value-expr)}+ }
#define WG_PP_AUTOFUNCTOR_SYMBOLTABLE_VALUESEQ_SETMEM(symbtbl) \
  WG_PP_AUTOFUNCTOR_ST_GET(symbtbl, VALUESEQ_SETMEM)

//Returns: { integer }
#define WG_PP_AUTOFUNCTOR_SYMBOLTABLE_XXX_SIZE_SETMEM(symbtbl) \
  WG_PP_AUTOFUNCTOR_ST_GET(symbtbl, XXX_SIZE_SETMEM)

//Returns: { integer }
#define WG_PP_AUTOFUNCTOR_SYMBOLTABLE_TOTALXXX_SIZE(symbtbl) \
  WG_PP_AUTOFUNCTOR_ST_GET(symbtbl, TOTALXXX_SIZE)

//#######################
//STUTIL Interface Impls.
//#######################

#define WG_PP_AUTOFUNCTOR_SYMBOLTABLE_INDX_TYPESEQ_ASSIGNEE \
  WG_PP_AUTOFUNCTOR_ST_INDX_TYPESEQ_ASSIGNEE
#define WG_PP_AUTOFUNCTOR_SYMBOLTABLE_INDX_TYPESEQ_BOUNDPARAM \
  WG_PP_AUTOFUNCTOR_ST_INDX_TYPESEQ_BOUNDPARAM
#define WG_PP_AUTOFUNCTOR_SYMBOLTABLE_INDX_TYPESEQ_SETPARAM \
  WG_PP_AUTOFUNCTOR_ST_INDX_TYPESEQ_SETPARAM
#define WG_PP_AUTOFUNCTOR_SYMBOLTABLE_INDX_TYPESEQ_BOUNDMEM \
  WG_PP_AUTOFUNCTOR_ST_INDX_TYPESEQ_BOUNDMEM
#define WG_PP_AUTOFUNCTOR_SYMBOLTABLE_INDX_TYPESEQ_SETMEM \
  WG_PP_AUTOFUNCTOR_ST_INDX_TYPESEQ_SETMEM

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
//return_type: { BOOST_PP_NIL | type }
//parambind_nrmlzd_tupleseq: { BOOST_PP_NIL | {normalized-bound-tuple}+ }
//paramset_nrmlzd_tupleseq: { BOOST_PP_NIL | {normalized-set-tuple}+ }
//membind_nrmlzd_tupleseq: { BOOST_PP_NIL | {normalized-bound-tuple}+ }
//memset_nrmlzd_tupleseq: { BOOST_PP_NIL | {normalized-set-tuple}+ }
//
//normalized-bound-tuple := (parsed-explicit-or-deduced-type)(var-name)
//normalized-set-tuple :=
//  (parsed-explicit-type-or-deduced-type)(var-name)(value-expr)
//parsed-explicit-or-deduced-type :=
//    WG_PP_NOOP parsed-explicit-type
//  | WG_PP_DEDUCEDTYPE parsed-deduced-type
//parsed-explicit-type := parsed-local-type | non-local-type
//parsed-local-type := local(some-token) lib-type-qualifier-seq
//lib-type-qualifier-seq := (const) | (ref) | (const)(ref)
//parsed-deduced-type :=
//  { BT | add_const<BT> | add_ref<BT> | add_ref< add_const<BT> > }
//BT := BOOST_TYPEOF(some-token)
//
//-------
//OUTPUT:
//-------
//A SymbolTable whose values are accessible using the public API.
#define WG_PP_AUTOFUNCTOR_SYMBOLTABLE_CREATE( \
  istpl, \
  assignto_nrmlzd_tuple, \
  return_type, \
  parambind_nrmlzd_tupleseq, \
  paramset_nrmlzd_tupleseq, \
  membind_nrmlzd_tupleseq, \
  memset_nrmlzd_tupleseq) \
    WG_PP_AUTOFUNCTOR_ST_CREATE_IMPL1( \
      istpl, \
      assignto_nrmlzd_tuple, \
      return_type, \
      parambind_nrmlzd_tupleseq, \
      paramset_nrmlzd_tupleseq, \
      membind_nrmlzd_tupleseq, \
      memset_nrmlzd_tupleseq)

//###########
//Impl Macros
//###########

#define WG_PP_AUTOFUNCTOR_ST_INDX_MODULEID 0

#define WG_PP_AUTOFUNCTOR_ST_INDX_ISTPL 1

#define WG_PP_AUTOFUNCTOR_ST_INDX_TYPESEQ_ASSIGNEE 2
#define WG_PP_AUTOFUNCTOR_ST_INDX_OBJSEQ_ASSIGNEE 3
#define WG_PP_AUTOFUNCTOR_ST_INDX_EXISTS_ASSIGNEE 4

#define WG_PP_AUTOFUNCTOR_ST_INDX_RETTYPE 5

#define WG_PP_AUTOFUNCTOR_ST_INDX_TYPESEQ_BOUNDPARAM 6
#define WG_PP_AUTOFUNCTOR_ST_INDX_OBJSEQ_BOUNDPARAM 7
#define WG_PP_AUTOFUNCTOR_ST_INDX_XXX_SIZE_BOUNDPARAM 8
#define WG_PP_AUTOFUNCTOR_ST_INDX_OBJSEQ_THISU_MARKER_BOUNDPARAM 9

#define WG_PP_AUTOFUNCTOR_ST_INDX_TYPESEQ_SETPARAM 10
#define WG_PP_AUTOFUNCTOR_ST_INDX_OBJSEQ_SETPARAM 11
#define WG_PP_AUTOFUNCTOR_ST_INDX_VALUESEQ_SETPARAM 12
#define WG_PP_AUTOFUNCTOR_ST_INDX_XXX_SIZE_SETPARAM 13

#define WG_PP_AUTOFUNCTOR_ST_INDX_TYPESEQ_BOUNDMEM 14
#define WG_PP_AUTOFUNCTOR_ST_INDX_OBJSEQ_BOUNDMEM 15
#define WG_PP_AUTOFUNCTOR_ST_INDX_XXX_SIZE_BOUNDMEM 16
#define WG_PP_AUTOFUNCTOR_ST_INDX_OBJSEQ_THISU_MARKER_BOUNDMEM 17

#define WG_PP_AUTOFUNCTOR_ST_INDX_TYPESEQ_SETMEM 18
#define WG_PP_AUTOFUNCTOR_ST_INDX_OBJSEQ_SETMEM 19
#define WG_PP_AUTOFUNCTOR_ST_INDX_VALUESEQ_SETMEM 20
#define WG_PP_AUTOFUNCTOR_ST_INDX_XXX_SIZE_SETMEM 21

#define WG_PP_AUTOFUNCTOR_ST_INDX_TOTALXXX_SIZE 22

// suffix: must match one of the following: WG_PP_AUTOFUNCTOR_ST_INDX_<suffix>
#define WG_PP_AUTOFUNCTOR_ST_GET(symbtbl, suffix) \
  BOOST_PP_ARRAY_ELEM( \
    BOOST_PP_CAT(WG_PP_AUTOFUNCTOR_ST_INDX_, suffix), \
    symbtbl)

//---------------
//Creation Macros
//---------------

#define WG_PP_AUTOFUNCTOR_ST_CREATE_IMPL1( \
  istpl, \
  assignto_nrmlzd_tuple, \
  return_type, \
  parambind_nrmlzd_tupleseq, \
  paramset_nrmlzd_tupleseq, \
  membind_nrmlzd_tupleseq, \
  memset_nrmlzd_tupleseq) \
    WG_PP_AUTOFUNCTOR_ST_CREATE_IMPL2( \
      istpl, \
      WG_PP_STUTIL_BOUNDTUPLESEQ_TO_TYPESEQ(assignto_nrmlzd_tuple), \
      WG_PP_STUTIL_BOUNDTUPLESEQ_TO_OBJSEQ(assignto_nrmlzd_tuple), \
      return_type, \
      WG_PP_STUTIL_BOUNDTUPLESEQ_TO_TYPESEQ(parambind_nrmlzd_tupleseq), \
      WG_PP_STUTIL_BOUNDTUPLESEQ_TO_OBJSEQ(parambind_nrmlzd_tupleseq), \
      WG_PP_STUTIL_SETTUPLESEQ_TO_TYPESEQ(paramset_nrmlzd_tupleseq), \
      WG_PP_STUTIL_SETTUPLESEQ_TO_OBJSEQ(paramset_nrmlzd_tupleseq), \
      WG_PP_STUTIL_SETTUPLESEQ_TO_VALUESEQ(paramset_nrmlzd_tupleseq), \
      WG_PP_STUTIL_BOUNDTUPLESEQ_TO_TYPESEQ(membind_nrmlzd_tupleseq), \
      WG_PP_STUTIL_BOUNDTUPLESEQ_TO_OBJSEQ(membind_nrmlzd_tupleseq), \
      WG_PP_STUTIL_SETTUPLESEQ_TO_TYPESEQ(memset_nrmlzd_tupleseq), \
      WG_PP_STUTIL_SETTUPLESEQ_TO_OBJSEQ(memset_nrmlzd_tupleseq), \
      WG_PP_STUTIL_SETTUPLESEQ_TO_VALUESEQ(memset_nrmlzd_tupleseq))

#define WG_PP_AUTOFUNCTOR_ST_CREATE_IMPL2( \
  istpl, \
  assignto_type_seq, assignto_ob_seq, \
  return_type, \
  parambind_type_seq, parambind_obj_seq, \
  paramset_type_seq, paramset_obj_seq, paramset_value_seq, \
  membind_type_seq, membind_obj_seq, \
  memset_type_seq, memset_obj_seq, memset_value_seq) \
    WG_PP_AUTOFUNCTOR_ST_CREATE_IMPL3( \
      (22, \
        (WG_PP_AUTOFUNCTOR_SYMBOLTABLE, \
        istpl, \
        assignto_type_seq, \
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
        WG_PP_SEQ_SIZE(paramset_type_seq), \
        membind_type_seq, \
        membind_obj_seq, \
        WG_PP_SEQ_SIZE(membind_type_seq), \
        WG_PP_STUTIL_THISU_INDX(membind_obj_seq), \
        memset_type_seq, \
        memset_obj_seq, \
        memset_value_seq, \
        WG_PP_SEQ_SIZE(memset_type_seq) )) \
    )

#define WG_PP_AUTOFUNCTOR_ST_CREATE_IMPL3(wiparray) \
  BOOST_PP_ARRAY_PUSH_BACK( \
    wiparray, \
    BOOST_PP_ADD( \
      BOOST_PP_ADD( \
        BOOST_PP_ADD( \
          BOOST_PP_ADD( \
            WG_PP_AUTOFUNCTOR_SYMBOLTABLE_XXX_SIZE_BOUNDPARAM(wiparray), \
            WG_PP_AUTOFUNCTOR_SYMBOLTABLE_XXX_SIZE_SETPARAM(wiparray)), \
          WG_PP_AUTOFUNCTOR_SYMBOLTABLE_XXX_SIZE_BOUNDMEM(wiparray)), \
        WG_PP_AUTOFUNCTOR_SYMBOLTABLE_XXX_SIZE_SETMEM(wiparray)), \
      WG_PP_AUTOFUNCTOR_SYMBOLTABLE_XXX_SIZE_ASSIGNEE(wiparray)))

#endif //WG_PP_AUTOFUNCTOR_SYMBOLTABLE_HH_
