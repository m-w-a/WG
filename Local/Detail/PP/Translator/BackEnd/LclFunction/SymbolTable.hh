#ifndef WG_PP_LCLFUNCTION_SYMBOLTABLE_HH_
#define WG_PP_LCLFUNCTION_SYMBOLTABLE_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/PP.hh>
#include <WG/Local/Detail/PP/Seq.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/SymbolTableUtil.hh>

//################
//Interface Impls.
//  (Implements interfaces required by external macros.)
//################

#define WG_PP_LCLFUNCTION_SYMBOLTABLE_MODULEID(symbtbl) \
  WG_PP_LCLCLASS_ST_GET(symbtbl, MODULEID)

#define WG_PP_LCLFUNCTION_SYMBOLTABLE_ISTPL(symbtbl) \
  WG_PP_LCLFUNCTION_ST_GET(symbtbl, ISTPL)

//Returns: { 0 | 1 }
#define WG_PP_LCLFUNCTION_SYMBOLTABLE_EXISTS_RETTYPE(symbtbl) \
  WG_PP_ISNEXTTOKEN_A_TUPLE( \
    1, \
    WG_PP_LCLFUNCTION_SYMBOLTABLE_RETTUPLE(symbtbl) )

//Returns: { return-type | some-unspecified-token-seq }
#define WG_PP_LCLFUNCTION_SYMBOLTABLE_RETTYPE(symbtbl) \
  WG_PP_LCLFUNCTION_SYMBOLTABLE_RETTYPE_IMPL( \
    WG_PP_IDENTITY_ARG1 WG_PP_LCLFUNCTION_SYMBOLTABLE_RETTUPLE(symbtbl) )

//Returns: { BOOST_PP_NIL | return-tuple  }
#define WG_PP_LCLFUNCTION_SYMBOLTABLE_RETTUPLE(symbtbl) \
  WG_PP_LCLFUNCTION_ST_GET(symbtbl, RETTUPLE)

//Returns: { BOOST_PP_NIL | {(non-local-type)}+ }
#define WG_PP_LCLFUNCTION_SYMBOLTABLE_TYPESEQ_PARAMS(symbtbl) \
  WG_PP_LCLFUNCTION_ST_GET(symbtbl, TYPESEQ_PARAMS)

//Returns: { BOOST_PP_NIL | {(var-name)}+ }
#define WG_PP_LCLFUNCTION_SYMBOLTABLE_OBJSEQ_PARAMS(symbtbl) \
  WG_PP_LCLFUNCTION_ST_GET(symbtbl, OBJSEQ_PARAMS)

//Returns: { BOOST_PP_NIL | {(parsed-explicit-non-local-type-or-deduced-type)}+ }
#define WG_PP_LCLFUNCTION_SYMBOLTABLE_TYPESEQ_BOUNDVAR(symbtbl) \
  WG_PP_LCLFUNCTION_ST_GET(symbtbl, TYPESEQ_BOUNDVAR)

//Returns: { BOOST_PP_NIL | {(var-name)}+ }
#define WG_PP_LCLFUNCTION_SYMBOLTABLE_OBJSEQ_BOUNDVAR(symbtbl) \
  WG_PP_LCLFUNCTION_ST_GET(symbtbl, OBJSEQ_BOUNDVAR)

//See WG_PP_LCLFUNCTION_SYMBOLTABLE_OBJSEQ_BOUNDVAR.
#define WG_PP_LCLFUNCTION_SYMBOLTABLE_VALUESEQ_BOUNDVAR(symbtbl) \
  WG_PP_LCLFUNCTION_SYMBOLTABLE_OBJSEQ_BOUNDVAR(symbtbl)

//Returns: { integer }
#define WG_PP_LCLFUNCTION_SYMBOLTABLE_XXX_SIZE_BOUNDVAR(symbtbl) \
  WG_PP_LCLFUNCTION_ST_GET(symbtbl, XXX_SIZE_BOUNDVAR)

//Returns: { BOOST_PP_NIL | integer }
#define WG_PP_LCLFUNCTION_SYMBOLTABLE_OBJSEQ_THISU_MARKER_BOUNDVAR(symbtbl) \
  WG_PP_LCLFUNCTION_ST_GET(symbtbl, OBJSEQ_THISU_MARKER_BOUNDVAR)

//Returns: { BOOST_PP_NIL | {(parsed-explicit-non-local-type-or-deduced-type)}+ }
#define WG_PP_LCLFUNCTION_SYMBOLTABLE_TYPESEQ_SETVAR(symbtbl) \
  WG_PP_LCLFUNCTION_ST_GET(symbtbl, TYPESEQ_SETVAR)

//Returns: { BOOST_PP_NIL | {(var-name)}+ }
#define WG_PP_LCLFUNCTION_SYMBOLTABLE_OBJSEQ_SETVAR(symbtbl) \
  WG_PP_LCLFUNCTION_ST_GET(symbtbl, OBJSEQ_SETVAR)

//Returns: { BOOST_PP_NIL | {(value-expr)}+ }
#define WG_PP_LCLFUNCTION_SYMBOLTABLE_VALUESEQ_SETVAR(symbtbl) \
  WG_PP_LCLFUNCTION_ST_GET(symbtbl, VALUESEQ_SETVAR)

//Returns: { integer }
#define WG_PP_LCLFUNCTION_SYMBOLTABLE_XXX_SIZE_SETVAR(symbtbl) \
  WG_PP_LCLFUNCTION_ST_GET(symbtbl, XXX_SIZE_SETVAR)

//#######################
//STUTIL Interface Impls.
//#######################

#define WG_PP_LCLFUNCTION_SYMBOLTABLE_INDX(suffix) \
  BOOST_PP_CAT(WG_PP_LCLFUNCTION_ST_INDX_, suffix)

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
//
//return_type: { BOOST_PP_NIL | type }
//params_nrmlzd_tupleseq: { BOOST_PP_NIL | {normalized-explicit-nlt-tuple}+ }
//
//varbind_nrmlzd_tupleseq: { BOOST_PP_NIL | {normalized-bound-nlt-tuple}+ }
//varset_nrmlzd_tupleseq: { BOOST_PP_NIL | {normalized-set-nlt-tuple}+ }
//
//normalized-explicit-nlt-tuple :=
//  (non-local-type)(var-name)
//normalized-bound-nlt-tuple :=
//  (parsed-explicit-non-local-type-or-deduced-type)(var-name)
//normalized-set-nlt-tuple :=
//  (parsed-explicit-non-local-type-or-deduced-type)(var-name)(value-expr)
//parsed-explicit-non-local-type-or-deduced-type: =
//    WG_PP_MARKER_NOOP parsed-explicit-non-local-type
//  | WG_PP_MARKER_DEDUCEDTYPE parsed-deduced-type
//parsed-explicit-non-local-type :=
//  explicit-non-local-type
//parsed-deduced-type :=
//  ( { BT | add_const<BT> | add_ref<BT> | add_ref< add_const<BT> > } )
//BT := BOOST_TYPEOF(some-token)
//
//-------
//OUTPUT:
//-------
//A SymbolTable whose values are accessible using the public API.
#define WG_PP_LCLFUNCTION_SYMBOLTABLE_CREATE( \
  istpl, \
  return_type, \
  params_nrmlzd_tupleseq, \
  varbind_nrmlzd_tupleseq, \
  varset_nrmlzd_tupleseq) \
    WG_PP_LCLFUNCION_SYMBOLTABLE_CREATE_IMPL1( \
      istpl, \
      return_type, \
      params_nrmlzd_tupleseq, \
      varbind_nrmlzd_tupleseq, \
      varset_nrmlzd_tupleseq)

//###########
//Impl Macros
//###########

#define WG_PP_LCLFUNCTION_ST_INDX_MODULEID 0

#define WG_PP_LCLFUNCTION_ST_INDX_ISTPL 1

#define WG_PP_LCLFUNCTION_ST_INDX_RETTUPLE 2

#define WG_PP_LCLFUNCTION_ST_INDX_TYPESEQ_PARAMS 3
#define WG_PP_LCLFUNCTION_ST_INDX_OBJSEQ_PARAMS 4
#define WG_PP_LCLFUNCTION_ST_INDX_TYPESEQ_BOUNDVAR 5
#define WG_PP_LCLFUNCTION_ST_INDX_OBJSEQ_BOUNDVAR 6
#define WG_PP_LCLFUNCTION_ST_INDX_XXX_SIZE_BOUNDVAR 7
#define WG_PP_LCLFUNCTION_ST_INDX_OBJSEQ_THISU_MARKER_BOUNDVAR 8

#define WG_PP_LCLFUNCTION_ST_INDX_TYPESEQ_SETVAR 9
#define WG_PP_LCLFUNCTION_ST_INDX_OBJSEQ_SETVAR 10
#define WG_PP_LCLFUNCTION_ST_INDX_VALUESEQ_SETVAR 11
#define WG_PP_LCLFUNCTION_ST_INDX_XXX_SIZE_SETVAR 12

#define WG_PP_LCLFUNCTION_ST_INDX_TOTALXXX_SIZE 13

// suffix: must match one of the following: WG_PP_LCLFUNCTION_ST_INDX_<suffix>
#define WG_PP_LCLFUNCTION_ST_GET(symbtbl, suffix) \
  BOOST_PP_ARRAY_ELEM( \
    BOOST_PP_CAT(WG_PP_LCLFUNCTION_ST_INDX_, suffix), \
    symbtbl)

#define WG_PP_LCLFUNCTION_SYMBOLTABLE_RETTYPE_IMPL(rescan) \
  rescan

//---------------
//Creation Macros
//---------------

#define WG_PP_LCLFUNCION_SYMBOLTABLE_CREATE_IMPL1( \
  istpl, \
  return_type, \
  params_nrmlzd_tupleseq, \
  varbind_nrmlzd_tupleseq, \
  varset_nrmlzd_tupleseq) \
    WG_PP_LCLFUNCTION_ST_CREATE_IMPL2( \
      istpl, \
      return_type, \
      WG_PP_STUTIL_BOUNDTUPLESEQ_TO_TYPESEQ(params_nrmlzd_tupleseq), \
      WG_PP_STUTIL_BOUNDTUPLESEQ_TO_OBJSEQ(params_nrmlzd_tupleseq), \
      WG_PP_STUTIL_BOUNDTUPLESEQ_TO_TYPESEQ(varbind_nrmlzd_tupleseq), \
      WG_PP_STUTIL_BOUNDTUPLESEQ_TO_OBJSEQ(varbind_nrmlzd_tupleseq), \
      WG_PP_STUTIL_SETTUPLESEQ_TO_TYPESEQ(varset_nrmlzd_tupleseq), \
      WG_PP_STUTIL_SETTUPLESEQ_TO_OBJSEQ(varset_nrmlzd_tupleseq), \
      WG_PP_STUTIL_SETTUPLESEQ_TO_VALUESEQ(varset_nrmlzd_tupleseq))

#define WG_PP_LCLFUNCTION_ST_CREATE_IMPL2( \
  istpl, \
  return_type, \
  params_type_seq, params_obj_seq, \
  varbind_type_seq, varbind_obj_seq, \
  varset_type_seq, varset_obj_seq, varset_value_seq) \
    WG_PP_LCLFUNCTION_ST_CREATE_IMPL3( \
      (13, \
        (WG_PP_LCLFUNCTION_SYMBOLTABLE, \
        istpl, \
        return_type, \
        params_type_seq, \
        params_obj_seq, \
        varbind_type_seq, \
        varbind_obj_seq, \
        WG_PP_SEQ_SIZE(varbind_type_seq), \
        WG_PP_STUTIL_THISU_INDX(varbind_obj_seq), \
        varset_type_seq, \
        varset_obj_seq, \
        varset_value_seq, \
        WG_PP_SEQ_SIZE(varset_type_seq) )) \
    )

#define WG_PP_LCLFUNCTION_ST_CREATE_IMPL3(wiparray) \
  BOOST_PP_ARRAY_PUSH_BACK( \
    wiparray, \
    BOOST_PP_ADD( \
      WG_PP_LCLFUNCTION_SYMBOLTABLE_XXX_SIZE_BOUNDVAR(wiparray), \
      WG_PP_LCLFUNCTION_SYMBOLTABLE_XXX_SIZE_SETVAR(wiparray)) )

#endif /* WG_PP_LCLFUNCTION_SYMBOLTABLE_HH_ */
