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

#define WG_PP_LCLCLASS_SYMBOLTABLE_MODULEID(symbtbl) \
  WG_PP_LCLCLASS_ST_GET(symbtbl, MODULEID)

#define WG_PP_LCLCLASS_SYMBOLTABLE_ISTPL(symbtbl) \
  WG_PP_LCLCLASS_ST_GET(symbtbl, ISTPL)

//Returns: { BOOST_PP_NIL | derives-tuple-seq }
#define WG_PP_LCLCLASS_SYMBOLTABLE_DERIVESSEQ(symbtbl) \
  WG_PP_LCLCLASS_ST_GET(symbtbl, DERIVESSEQ)

//Returns: { BOOST_PP_NIL | {(parsed-explicit-or-deduced-type)}+ }
#define WG_PP_LCLCLASS_SYMBOLTABLE_TYPESEQ_MEMEXT(symbtbl) \
  WG_PP_LCLCLASS_ST_GET(symbtbl, TYPESEQ_MEMEXT)

//Returns: { BOOST_PP_NIL | {(var-name)}+ }
#define WG_PP_LCLCLASS_SYMBOLTABLE_OBJSEQ_MEMEXT(symbtbl) \
  WG_PP_LCLCLASS_ST_GET(symbtbl, OBJSEQ_MEMEXT)

//See WG_PP_LCLCLASS_SYMBOLTABLE_OBJSEQ_MEMEXT.
#define WG_PP_LCLCLASS_SYMBOLTABLE_VALUESEQ_MEMEXT(symbtbl) \
  WG_PP_LCLCLASS_SYMBOLTABLE_OBJSEQ_MEMEXT(symbtbl)

//Returns: { integer }
#define WG_PP_LCLCLASS_SYMBOLTABLE_XXX_SIZE_MEMEXT(symbtbl) \
  WG_PP_LCLCLASS_ST_GET(symbtbl, XXX_SIZE_MEMEXT)

//Returns: { BOOST_PP_NIL | integer }
#define WG_PP_LCLCLASS_SYMBOLTABLE_OBJSEQ_THISU_MARKER_MEMEXT(symbtbl) \
  WG_PP_LCLCLASS_ST_GET(symbtbl, OBJSEQ_THISU_MARKER_MEMEXT)

//Returns: { BOOST_PP_NIL | {(parsed-explicit-type-or-deduced-type)}+ }
#define WG_PP_LCLCLASS_SYMBOLTABLE_TYPESEQ_MEMINT(symbtbl) \
  WG_PP_LCLCLASS_ST_GET(symbtbl, TYPESEQ_MEMINT)

//Returns: { BOOST_PP_NIL | {(var-name)}+ }
#define WG_PP_LCLCLASS_SYMBOLTABLE_OBJSEQ_MEMINT(symbtbl) \
  WG_PP_LCLCLASS_ST_GET(symbtbl, OBJSEQ_MEMINT)

//Returns: { BOOST_PP_NIL | {(value-expr)}+ }
#define WG_PP_LCLCLASS_SYMBOLTABLE_VALUESEQ_MEMINT(symbtbl) \
  WG_PP_LCLCLASS_ST_GET(symbtbl, VALUESEQ_MEMINT)

//Returns: { integer }
#define WG_PP_LCLCLASS_SYMBOLTABLE_XXX_SIZE_MEMINT(symbtbl) \
  WG_PP_LCLCLASS_ST_GET(symbtbl, XXX_SIZE_MEMINT)

//Returns: { integer }
#define WG_PP_LCLCLASS_SYMBOLTABLE_TOTALXXX_SIZE(symbtbl) \
  WG_PP_LCLCLASS_ST_GET(symbtbl, TOTALXXX_SIZE)

//#######################
//STUTIL Interface Impls.
//#######################

// suffix: must match one of the following: WG_PP_LCLCLASS_ST_INDX_<suffix>
#define WG_PP_LCLCLASS_SYMBOLTABLE_INDX(suffix) \
  BOOST_PP_CAT(WG_PP_LCLCLASS_ST_INDX_, suffix)

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
//memext_nrmlzd_tupleseq: { BOOST_PP_NIL | {normalized-bound-tuple}+ }
//memint_nrmlzd_tupleseq: { BOOST_PP_NIL | {normalized-set-tuple}+ }
//
//normalized-bound-tuple := (parsed-explicit-or-deduced-type)(var-name)
//normalized-set-tuple :=
//  (parsed-explicit-type-or-deduced-type)(var-name)(value-expr)
//parsed-explicit-or-deduced-type :=
//    WG_PP_MARKER_NOOP parsed-explicit-type
//  | WG_PP_MARKER_DEDUCEDTYPE parsed-deduced-type
//parsed-explicit-type := parsed-local-type | type explicit-non-local-type
//parsed-local-type := local(some-token) lib-type-qualifier-seq
//lib-type-qualifier-seq := (const) | (ref) | (const)(ref)
//parsed-deduced-type :=
//  type( { BT | add_const<BT> | add_ref<BT> | add_ref< add_const<BT> > } )
//BT := BOOST_TYPEOF(some-token)
//
//-------
//OUTPUT:
//-------
//A SymbolTable whose values are accessible using the public API.
#define WG_PP_LCLCLASS_SYMBOLTABLE_CREATE( \
  istpl, \
  derives_nrmlzd_tuple, \
  memext_nrmlzd_tupleseq, \
  memint_nrmlzd_tupleseq) \
    WG_PP_LCLCLASS_SYMBOLTABLE_CREATE_IMPL1( \
      istpl, \
      derives_nrmlzd_tuple, \
      memext_nrmlzd_tupleseq, \
      memint_nrmlzd_tupleseq)

//###########
//Impl Macros
//###########

#define WG_PP_LCLCLASS_ST_INDX_MODULEID 0

#define WG_PP_LCLCLASS_ST_INDX_ISTPL 1

#define WG_PP_LCLCLASS_ST_INDX_DERIVESSEQ 2

#define WG_PP_LCLCLASS_ST_INDX_TYPESEQ_MEMEXT 3
#define WG_PP_LCLCLASS_ST_INDX_OBJSEQ_MEMEXT 4
#define WG_PP_LCLCLASS_ST_INDX_XXX_SIZE_MEMEXT 5
#define WG_PP_LCLCLASS_ST_INDX_OBJSEQ_THISU_MARKER_MEMEXT 6

#define WG_PP_LCLCLASS_ST_INDX_TYPESEQ_MEMINT 7
#define WG_PP_LCLCLASS_ST_INDX_OBJSEQ_MEMINT 8
#define WG_PP_LCLCLASS_ST_INDX_VALUESEQ_MEMINT 9
#define WG_PP_LCLCLASS_ST_INDX_XXX_SIZE_MEMINT 10

#define WG_PP_LCLCLASS_ST_INDX_TOTALXXX_SIZE 11

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
  memext_nrmlzd_tupleseq, \
  memint_nrmlzd_tupleseq) \
    WG_PP_LCLCLASS_SYMBOLTABLE_CREATE_IMPL2( \
      istpl, \
      derives_nrmlzd_tuple, \
      WG_PP_STUTIL_BOUNDTUPLESEQ_TO_TYPESEQ(memext_nrmlzd_tupleseq), \
      WG_PP_STUTIL_BOUNDTUPLESEQ_TO_OBJSEQ(memext_nrmlzd_tupleseq), \
      WG_PP_STUTIL_SETTUPLESEQ_TO_TYPESEQ(memint_nrmlzd_tupleseq), \
      WG_PP_STUTIL_SETTUPLESEQ_TO_OBJSEQ(memint_nrmlzd_tupleseq), \
      WG_PP_STUTIL_SETTUPLESEQ_TO_VALUESEQ(memint_nrmlzd_tupleseq) )

#define WG_PP_LCLCLASS_SYMBOLTABLE_CREATE_IMPL2( \
  istpl, \
  derives_seq, \
  memext_type_seq, memext_obj_seq, \
  memint_type_seq, memint_obj_seq, memint_value_seq) \
    WG_PP_LCLCLASS_SYMBOLTABLE_CREATE_IMPL3( \
      (11, \
        (WG_PP_LCLCLASS_SYMBOLTABLE, \
        istpl, \
        derives_seq, \
        memext_type_seq, \
        memext_obj_seq, \
        WG_PP_SEQ_SIZE(memext_type_seq), \
        WG_PP_STUTIL_THISU_INDX(memext_obj_seq), \
        memint_type_seq, \
        memint_obj_seq, \
        memint_value_seq, \
        WG_PP_SEQ_SIZE(memint_type_seq) )) \
    )

#define WG_PP_LCLCLASS_SYMBOLTABLE_CREATE_IMPL3(wiparray) \
  BOOST_PP_ARRAY_PUSH_BACK( \
    wiparray, \
    BOOST_PP_ADD( \
      WG_PP_LCLCLASS_SYMBOLTABLE_XXX_SIZE_MEMEXT(wiparray), \
      WG_PP_LCLCLASS_SYMBOLTABLE_XXX_SIZE_MEMINT(wiparray) ))

#endif /* WG_PP_LCLCLASS_SYMBOLTABLE_HH_ */
