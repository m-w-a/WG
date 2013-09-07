#ifndef WG_PP_LCLFUNCTION_SYMBOLTABLE_HH_
#define WG_PP_LCLFUNCTION_SYMBOLTABLE_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/Seq.hh>
#include <WG/Local/Detail/PP/Keywords.hh>
#include <WG/Local/Detail/PP/BackEnd/SymbolTableUtil.hh>

//################
//Interface Impls.
//################

#define WG_PP_LCLFUNCTION_SYMBOLTABLE_ISTPL(symbtbl) \
  WG_PP_LCLFUNCTION_ST_GET(symbtbl, ISTPL)

//Returns: { BOOST_PP_NIL | return-type  }
#define WG_PP_LCLFUNCTION_SYMBOLTABLE_RETTYPE(symbtbl) \
  WG_PP_LCLFUNCTION_ST_GET(symbtbl, RETTYPE)

//Returns: { 0 | 1 }
#define WG_PP_LCLFUNCTION_SYMBOLTABLE_EXISTS_RETTYPE(symbtbl) \
  BOOST_PP_NOT( \
    WG_PP_TOKENS_START_WITH_BOOST_PP_NIL( \
      WG_PP_LCLFUNCTION_SYMBOLTABLE_RETTYPE(symbtbl) ))

//RETURNS: { BOOST_PP_NIL | (param-seq) }
#define WG_PP_LCLFUNCTION_SYMBOLTABLE_PARAMS(symbtbl) \
  WG_PP_LCLFUNCTION_ST_GET(symbtbl, PARAMS)

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

#define WG_PP_LCLFUNCTION_SYMBOLTABLE_INDX_TYPESEQ_BOUNDVAR \
  WG_PP_LCLFUNCTION_ST_INDX_TYPESEQ_BOUNDVAR
#define WG_PP_LCLFUNCTION_SYMBOLTABLE_INDX_TYPESEQ_SETVAR \
  WG_PP_LCLFUNCTION_ST_INDX_TYPESEQ_SETVAR

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
//params: { BOOST_PP_NIL | (param-seq) }
//varbind_nrmlzd_tupleseq: { BOOST_PP_NIL | {normalized-bound-nlt-tuple}+ }
//varset_nrmlzd_tupleseq: { BOOST_PP_NIL | {normalized-set-nlt-tuple}+ }
//
//normalized-bound-nlt-tuple :=
//  (parsed-explicit-non-local-type-or-deduced-type)(var-name)
//normalized-set-nlt-tuple :=
//  (parsed-explicit-non-local-type-or-deduced-type)(var-name)(value-expr)
//parsed-explicit-non-local-type-or-deduced-type: =
//  (non-local-type)(parsed-deduced-type)
//parsed-deduced-type :=
//  WG_PP_DEDUCEDTYPE
//  { BT | add_const<BT> | add_ref<BT> | add_ref< add_const<BT> > }
//BT := BOOST_TYPEOF(some-token)
//
//-------
//OUTPUT:
//-------
//A SymbolTable whose values are accessible using the public API.
#define WG_PP_LCLFUNCION_SYMBOLTABLE_CREATE( \
  istpl, \
  return_type, \
  params, \
  varbind_nrmlzd_tupleseq, \
  varset_nrmlzd_tupleseq) \
    WG_PP_LCLFUNCION_SYMBOLTABLE_CREATE_IMPL1( \
      istpl, \
      return_type, \
      params, \
      varbind_nrmlzd_tupleseq, \
      varset_nrmlzd_tupleseq)

//###########
//Impl Macros
//###########

#define WG_PP_LCLFUNCTION_ST_INDX_MODULEID 0

#define WG_PP_LCLFUNCTION_ST_INDX_ISTPL 1

#define WG_PP_LCLFUNCTION_ST_INDX_RETURN 2

#define WG_PP_LCLFUNCTION_ST_INDX_TYPESEQ_BOUNDVAR 3
#define WG_PP_LCLFUNCTION_ST_INDX_OBJSEQ_BOUNDVAR 4
#define WG_PP_LCLFUNCTION_ST_INDX_XXX_SIZE_BOUNDVAR 5
#define WG_PP_LCLFUNCTION_ST_INDX_OBJSEQ_THISU_MARKER_BOUNDVAR 6

#define WG_PP_LCLFUNCTION_ST_INDX_TYPESEQ_SETVAR 7
#define WG_PP_LCLFUNCTION_ST_INDX_OBJSEQ_SETVAR 8
#define WG_PP_LCLFUNCTION_ST_INDX_VALUESEQ_SETVAR 9
#define WG_PP_LCLFUNCTION_ST_INDX_XXX_SIZE_SETVAR 10

#define WG_PP_LCLFUNCTION_ST_INDX_TOTALXXX_SIZE 11

// suffix: must match one of the following: WG_PP_AUTOFUNCTOR_ST_INDX_<suffix>
#define WG_PP_LCLFUNCTION_ST_GET(symbtbl, suffix) \
  BOOST_PP_ARRAY_ELEM( \
    BOOST_PP_CAT(WG_PP_LCLFUNCTION_ST_INDX_, suffix), \
    symbtbl)

//---------------
//Creation Macros
//---------------

#define WG_PP_LCLFUNCION_SYMBOLTABLE_CREATE_IMPL1( \
  istpl, \
  return_type, \
  params, \
  varbind_nrmlzd_tupleseq, \
  varset_nrmlzd_tupleseq) \
    WG_PP_LCLFUNCTION_ST_CREATE_IMPL2( \
      istpl, \
      return_type, \
      WG_PP_STUTIL_BOUNDTUPLESEQ_TO_TYPESEQ(varbind_nrmlzd_tupleseq), \
      WG_PP_STUTIL_BOUNDTUPLESEQ_TO_OBJSEQ(varbind_nrmlzd_tupleseq), \
      WG_PP_STUTIL_SETTUPLESEQ_TO_TYPESEQ(varset_nrmlzd_tupleseq), \
      WG_PP_STUTIL_SETTUPLESEQ_TO_OBJSEQ(varset_nrmlzd_tupleseq), \
      WG_PP_STUTIL_SETTUPLESEQ_TO_VALUESEQ(varset_nrmlzd_tupleseq))

#define WG_PP_LCLFUNCTION_ST_CREATE_IMPL2( \
  istpl, \
  return_type, \
  varbind_type_seq, varbind_obj_seq, \
  varset_type_seq, varset_obj_seq, varset_value_seq) \
    WG_PP_LCLFUNCTION_ST_CREATE_IMPL3( \
      (10, \
        (WG_PP_LCLFUNCTION_SYMBOLTABLE, \
        istpl, \
        return_type, \
        varbind_type_seq, varbind_obj_seq, \
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
