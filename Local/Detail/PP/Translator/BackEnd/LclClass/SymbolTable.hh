#ifndef WG_PP_LCLCLASS_SYMBOLTABLE_HH_
#define WG_PP_LCLCLASS_SYMBOLTABLE_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/Seq.hh>
#include <WG/Local/Detail/PP/PP.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/SymbolTableUtil.hh>

//################
//Interface Impls.
//  (Implements interfaces required by external macros.)
//################

#define WG_PP_LCLCLASS_SYMBOLTABLE_ISTPL(symbtbl) \
  WG_PP_LCLCLASS_ST_GET(symbtbl, ISTPL)

//Returns: { BOOST_PP_NIL | derives-tuple-seq }
#define WG_PP_LCLCLASS_SYMBOLTABLE_DERIVESSEQ(symbtbl) \
  WG_PP_LCLCLASS_ST_GET(symbtbl, DERIVESSEQ)

//Returns: { BOOST_PP_NIL | {(parsed-explicit-type)}+ }
#define WG_PP_LCLCLASS_SYMBOLTABLE_TYPESEQ_MEMDECL(symbtbl) \
  WG_PP_LCLCLASS_ST_GET(symbtbl, TYPESEQ_MEMDECL)

//Returns: { BOOST_PP_NIL | {(var-name)}+ }
#define WG_PP_LCLCLASS_SYMBOLTABLE_OBJSEQ_MEMDECL(symbtbl) \
  WG_PP_LCLCLASS_ST_GET(symbtbl, OBJSEQ_MEMDECL)

//Returns: { integer }
#define WG_PP_LCLCLASS_SYMBOLTABLE_XXX_SIZE_MEMDECL(symbtbl) \
  WG_PP_LCLCLASS_ST_GET(symbtbl, XXX_SIZE_MEMDECL)

//Returns: { BOOST_PP_NIL | {(parsed-explicit-or-deduced-type)}+ }
#define WG_PP_LCLCLASS_SYMBOLTABLE_TYPESEQ_MEMLIKE(symbtbl) \
  WG_PP_LCLCLASS_ST_GET(symbtbl, TYPESEQ_MEMLIKE)

//Returns: { BOOST_PP_NIL | {(var-name)}+ }
#define WG_PP_LCLCLASS_SYMBOLTABLE_OBJSEQ_MEMLIKE(symbtbl) \
  WG_PP_LCLCLASS_ST_GET(symbtbl, OBJSEQ_MEMLIKE)

//See WG_PP_LCLCLASS_SYMBOLTABLE_OBJSEQ_MEMLIKE.
#define WG_PP_LCLCLASS_SYMBOLTABLE_VALUESEQ_MEMLIKE(symbtbl) \
  WG_PP_LCLCLASS_SYMBOLTABLE_OBJSEQ_MEMLIKE(symbtbl)

//Returns: { integer }
#define WG_PP_LCLCLASS_SYMBOLTABLE_XXX_SIZE_MEMLIKE(symbtbl) \
  WG_PP_LCLCLASS_ST_GET(symbtbl, XXX_SIZE_MEMLIKE)

//Returns: { BOOST_PP_NIL | integer }
#define WG_PP_LCLCLASS_SYMBOLTABLE_OBJSEQ_THISU_MARKER_MEMLIKE(symbtbl) \
  WG_PP_LCLCLASS_ST_GET(symbtbl, OBJSEQ_THISU_MARKER_MEMLIKE)

//Returns: { BOOST_PP_NIL | {(parsed-explicit-type-or-deduced-type)}+ }
#define WG_PP_LCLCLASS_SYMBOLTABLE_TYPESEQ_MEMSET(symbtbl) \
  WG_PP_LCLCLASS_ST_GET(symbtbl, TYPESEQ_MEMSET)

//Returns: { BOOST_PP_NIL | {(var-name)}+ }
#define WG_PP_LCLCLASS_SYMBOLTABLE_OBJSEQ_MEMSET(symbtbl) \
  WG_PP_LCLCLASS_ST_GET(symbtbl, OBJSEQ_MEMSET)

//Returns: { BOOST_PP_NIL | {(value-expr)}+ }
#define WG_PP_LCLCLASS_SYMBOLTABLE_VALUESEQ_MEMSET(symbtbl) \
  WG_PP_LCLCLASS_ST_GET(symbtbl, VALUESEQ_MEMSET)

//Returns: { integer }
#define WG_PP_LCLCLASS_SYMBOLTABLE_XXX_SIZE_MEMSET(symbtbl) \
  WG_PP_LCLCLASS_ST_GET(symbtbl, XXX_SIZE_MEMSET)

//Returns: { integer }
#define WG_PP_LCLCLASS_SYMBOLTABLE_TOTALXXX_SIZE(symbtbl) \
  WG_PP_LCLCLASS_ST_GET(symbtbl, TOTALXXX_SIZE)

//#######################
//STUTIL Interface Impls.
//#######################

#define WG_PP_LCLCLASS_SYMBOLTABLE_INDX_TYPESEQ_MEMDECL \
  WG_PP_LCLCLASS_ST_INDX_TYPESEQ_MEMDECL
#define WG_PP_LCLCLASS_SYMBOLTABLE_INDX_TYPESEQ_MEMLIKE \
  WG_PP_LCLCLASS_ST_INDX_TYPESEQ_MEMLIKE
#define WG_PP_LCLCLASS_SYMBOLTABLE_INDX_TYPESEQ_MEMSET \
  WG_PP_LCLCLASS_ST_INDX_TYPESEQ_MEMSET

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
//derives_nrmlzd_tuple: { BOOST_PP_NIL | derives-tuple-seq }
//memdecl_nrmlzd_tupleseq: { BOOST_PP_NIL | {normalized-explicit-tuple}+ }
//memlike_nrmlzd_tupleseq: { BOOST_PP_NIL | {normalized-bound-tuple}+ }
//memset_nrmlzd_tupleseq: { BOOST_PP_NIL | {normalized-set-tuple}+ }
//
//normalized-explicit-tuple :=
//  (parsed-explicit-type)(var-name)
//normalized-bound-tuple := (deduced-type)(var-name)
//normalized-set-tuple :=
//  (parsed-explicit-type-or-deduced-type)(var-name)(value-expr)
//parsed-explicit-or-deduced-type :=
//    WG_PP_NOOP parsed-explicit-type
//  | WG_PP_DEDUCEDTYPE parsed-deduced-type
//parsed-explicit-type := parsed-local-type | explicit-non-local-type
//parsed-local-type := local(some-token) lib-type-qualifier-seq
//lib-type-qualifier-seq := (const) | (ref) | (const)(ref)
//parsed-deduced-type :=
//  ( { BT | add_const<BT> | add_ref<BT> | add_ref< add_const<BT> > } )
//BT := BOOST_TYPEOF(some-token)
//
//-------
//OUTPUT:
//-------
//A SymbolTable whose values are accessible using the public API.
#define WG_PP_LCLCLASS_SYMBOLTABLE_CREATE( \
  istpl, \
  derives_nrmlzd_tuple, \
  memdecl_nrmlzd_tupleseq, \
  memlike_nrmlzd_tupleseq, \
  memset_nrmlzd_tupleseq) \
    WG_PP_LCLCLASS_SYMBOLTABLE_CREATE_IMPL1( \
      istpl, \
      derives_nrmlzd_tuple, \
      memdecl_nrmlzd_tupleseq, \
      memlike_nrmlzd_tupleseq, \
      memset_nrmlzd_tupleseq)

//###########
//Impl Macros
//###########

#define WG_PP_LCLCLASS_ST_INDX_MODULEID 0

#define WG_PP_LCLCLASS_ST_INDX_ISTPL 1

#define WG_PP_LCLCLASS_ST_INDX_DERIVESSEQ 2

#define WG_PP_LCLCLASS_ST_INDX_TYPESEQ_MEMDECL 3
#define WG_PP_LCLCLASS_ST_INDX_OBJSEQ_MEMDECL 4
#define WG_PP_LCLCLASS_ST_INDX_XXX_SIZE_MEMDECL 5

#define WG_PP_LCLCLASS_ST_INDX_TYPESEQ_MEMLIKE 6
#define WG_PP_LCLCLASS_ST_INDX_OBJSEQ_MEMLIKE 7
#define WG_PP_LCLCLASS_ST_INDX_XXX_SIZE_MEMLIKE 8
#define WG_PP_LCLCLASS_ST_INDX_OBJSEQ_THISU_MARKER_MEMLIKE 9

#define WG_PP_LCLCLASS_ST_INDX_TYPESEQ_MEMSET 10
#define WG_PP_LCLCLASS_ST_INDX_OBJSEQ_MEMSET 11
#define WG_PP_LCLCLASS_ST_INDX_VALUESEQ_MEMSET 12
#define WG_PP_LCLCLASS_ST_INDX_XXX_SIZE_MEMSET 13

#define WG_PP_LCLCLASS_ST_INDX_TOTALXXX_SIZE 14

// suffix: must match one of the following: WG_PP_LCLCLASS_ST_INDX_<suffix>
#define WG_PP_LCLCLASS_ST_GET(symbtbl, suffix) \
  BOOST_PP_ARRAY_ELEM( \
    BOOST_PP_CAT(WG_PP_LCLCLASS_ST_INDX_, suffix), \
    symbtbl)

//---------------
//Creation Macros
//---------------

#define WG_PP_LCLCLASS_SYMBOLTABLE_CREATE_IMPL1( \
  istpl, \
  derives_nrmlzd_tuple, \
  memdecl_nrmlzd_tupleseq, \
  memlike_nrmlzd_tupleseq, \
  memset_nrmlzd_tupleseq) \
    WG_PP_LCLCLASS_SYMBOLTABLE_CREATE_IMPL2( \
      istpl, \
      derives_nrmlzd_tuple, \
      WG_PP_STUTIL_BOUNDTUPLESEQ_TO_TYPESEQ(memdecl_nrmlzd_tupleseq), \
      WG_PP_STUTIL_BOUNDTUPLESEQ_TO_OBJSEQ(memdecl_nrmlzd_tupleseq), \
      WG_PP_STUTIL_BOUNDTUPLESEQ_TO_TYPESEQ(memlike_nrmlzd_tupleseq), \
      WG_PP_STUTIL_BOUNDTUPLESEQ_TO_OBJSEQ(memlike_nrmlzd_tupleseq), \
      WG_PP_STUTIL_SETTUPLESEQ_TO_TYPESEQ(memset_nrmlzd_tupleseq), \
      WG_PP_STUTIL_SETTUPLESEQ_TO_OBJSEQ(memset_nrmlzd_tupleseq), \
      WG_PP_STUTIL_SETTUPLESEQ_TO_VALUESEQ(memset_nrmlzd_tupleseq) )

#define WG_PP_LCLCLASS_SYMBOLTABLE_CREATE_IMPL2( \
  istpl, \
  derives_seq, \
  memdecl_type_seq, memdecl_obj_seq, \
  memlike_type_seq, memlike_obj_seq, \
  memset_type_seq, memset_obj_seq, memset_value_seq) \
    WG_PP_LCLCLASS_SYMBOLTABLE_CREATE_IMPL3( \
      (14, \
        (WG_PP_LCLCLASS_SYMBOLTABLE, \
        istpl, \
        derives_seq, \
        memdecl_type_seq, \
        memdecl_obj_seq, \
        WG_PP_SEQ_SIZE(memdecl_type_seq), \
        memlike_type_seq, \
        memlike_obj_seq, \
        WG_PP_SEQ_SIZE(memlike_type_seq), \
        WG_PP_STUTIL_THISU_INDX(memlike_obj_seq), \
        memset_type_seq, \
        memset_obj_seq, \
        memset_value_seq, \
        WG_PP_SEQ_SIZE(memset_type_seq) )) \
    )

#define WG_PP_LCLCLASS_SYMBOLTABLE_CREATE_IMPL3(wiparray) \
  BOOST_PP_ARRAY_PUSH_BACK( \
    wiparray, \
    BOOST_PP_ADD( \
      WG_PP_LCLCLASS_SYMBOLTABLE_XXX_SIZE_MEMLIKE(wiparray), \
      WG_PP_LCLCLASS_SYMBOLTABLE_XXX_SIZE_MEMSET(wiparray) ))

#endif /* WG_PP_LCLCLASS_SYMBOLTABLE_HH_ */
