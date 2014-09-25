#ifndef WG_PP_LCLFUNCTION_SYMBOLTABLE_HH_
#define WG_PP_LCLFUNCTION_SYMBOLTABLE_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/PP.hh>
#include <WG/Local/Detail/PP/Seq.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/SymbolTableUtil.hh>

//###########
//Public APIs
//###########

#define WG_PP_LCLFUNCTION_SYMBOLTABLE_MODULEID(symbtbl) \
  WG_PP_LCLFUNCTION_ST_GET(symbtbl, MODULEID)

#define WG_PP_LCLFUNCTION_SYMBOLTABLE_ISTPL(symbtbl) \
  WG_PP_LCLFUNCTION_ST_GET(symbtbl, ISTPL)

// Returns: { 0 | 1 }
#define WG_PP_LCLFUNCTION_SYMBOLTABLE_EXISTS_RETTYPE(symbtbl) \
  BOOST_PP_COMPL( \
    WG_PP_STARTSWITH_BOOST_PP_NIL( \
      WG_PP_LCLFUNCTION_ST_GET(symbtbl, RETTUPLE) ) )

// Returns: { parsed-explicit-non-local-type | some-unspecified-token-seq }
#define WG_PP_LCLFUNCTION_SYMBOLTABLE_RETTYPE(symbtbl) \
  WG_PP_LCLFUNCTION_ST_GET(symbtbl, RETTUPLE)

//------
//Params
//------

// Returns: { BOOST_PP_NIL | param-seq }
#define WG_PP_LCLFUNCTION_SYMBOLTABLE_DCLNS_PARAMS(symbtbl) \
  WG_PP_LCLFUNCTION_ST_GET(symbtbl, DCLNS_PARAMS)

//--------
//BoundVar
//--------

// dcln: parsed-bound-var-dcln
// Returns: parsed-explicit-non-local-type-or-deduced-type
#define WG_PP_LCLFUNCTION_SYMBOLTABLE_DCLN_GETTYPE_BOUNDVAR(dcln) \
  WG_PP_SEQ_ELEM(0, dcln)

// dcln: parsed-bound-var-dcln
// type: the replacement type for dcln.
// Returns: parsed-bound-var-dcln
#define WG_PP_LCLFUNCTION_SYMBOLTABLE_DCLN_SETTYPE_BOUNDVAR(dcln, type) \
  WG_PP_SEQ_REPLACE(dcln, 0, type)

// dcln: parsed-bound-var-dcln
// Returns: var-name
#define WG_PP_LCLFUNCTION_SYMBOLTABLE_DCLN_OBJ_BOUNDVAR(dcln) \
  WG_PP_SEQ_ELEM(1, dcln)

// Returns: { BOOST_PP_NIL | parsed-bound-var-seq }
#define WG_PP_LCLFUNCTION_SYMBOLTABLE_GETDCLNS_BOUNDVAR(symbtbl) \
  WG_PP_LCLFUNCTION_ST_GET(symbtbl, DCLNS_BOUNDVAR)

#define WG_PP_LCLFUNCTION_SYMBOLTABLE_SETDCLNS_BOUNDVAR(symbtbl, dclns) \
  WG_PP_STUTIL_SYMBOLTABLE_REPLACE( \
    symbtbl, WG_PP_LCLFUNCTION_SYMBOLTABLE_INDX(DCLNS_BOUNDVAR), dclns)

// Returns: { integer }
#define WG_PP_LCLFUNCTION_SYMBOLTABLE_DCLNS_SIZE_BOUNDVAR(symbtbl) \
  WG_PP_LCLFUNCTION_ST_GET(symbtbl, DCLNS_SIZE_BOUNDVAR)

// Returns: { BOOST_PP_NIL | integer }
#define WG_PP_LCLFUNCTION_SYMBOLTABLE_DCLNS_THISU_MARKER_BOUNDVAR(symbtbl) \
  WG_PP_LCLFUNCTION_ST_GET(symbtbl, THISU_MARKER_BOUNDVAR)

//------
//SetVar
//------

// dcln: parsed-set-var-dcln
// Returns: parsed-explicit-non-local-type-or-deduced-type
#define WG_PP_LCLFUNCTION_SYMBOLTABLE_DCLN_GETTYPE_SETVAR(dcln) \
  WG_PP_SEQ_ELEM(0, dcln)

// dcln: parsed-set-var-dcln
// type: the replacement type for dcln.
// Returns: parsed-set-var-dcln
#define WG_PP_LCLFUNCTION_SYMBOLTABLE_DCLN_SETTYPE_SETVAR(dcln, type) \
  WG_PP_SEQ_REPLACE(dcln, 0, type)

// dcln: parsed-set-var-dcln
// Returns: var-name
#define WG_PP_LCLFUNCTION_SYMBOLTABLE_DCLN_OBJ_SETVAR(dcln) \
  WG_PP_SEQ_ELEM(1, dcln)

// dcln: parsed-set-var-dcln
// Returns: value-expr
#define WG_PP_LCLFUNCTION_SYMBOLTABLE_DCLN_VALUE_SETVAR(dcln) \
  WG_PP_SEQ_ELEM(2, dcln)

// Returns: { BOOST_PP_NIL | parsed-set-var-seq }
#define WG_PP_LCLFUNCTION_SYMBOLTABLE_GETDCLNS_SETVAR(symbtbl) \
  WG_PP_LCLFUNCTION_ST_GET(symbtbl, DCLNS_SETVAR)

#define WG_PP_LCLFUNCTION_SYMBOLTABLE_SETDCLNS_SETVAR(symbtbl, dclns) \
  WG_PP_STUTIL_SYMBOLTABLE_REPLACE( \
    symbtbl, WG_PP_LCLFUNCTION_SYMBOLTABLE_INDX(DCLNS_SETVAR), dclns)

// Returns: { integer }
#define WG_PP_LCLFUNCTION_SYMBOLTABLE_DCLNS_SIZE_SETVAR(symbtbl) \
  WG_PP_LCLFUNCTION_ST_GET(symbtbl, DCLNS_SIZE_SETVAR)

//-----
//Misc.
//-----

//Returns: { integer }
#define WG_PP_LCLFUNCTION_SYMBOLTABLE_DCLNS_TOTALSIZE(symbtbl) \
  WG_PP_LCLFUNCTION_ST_GET(symbtbl, DCLNS_TOTALSIZE)

//-----
//NOTE:
//-----
//
//What ever terms not defined here are defined in the respective BNF.
//------
//INPUT:
//------
//
// return_type: { BOOST_PP_NIL | parsed-explicit-non-local-type }
// paramseq: { BOOST_PP_NIL | param-seq }
//
// parsedboundvarseq: { BOOST_PP_NIL | parsed-bound-var-seq }
// parsedsetvarseq: { BOOST_PP_NIL | parsed-set-var-seq }
//
// parsed-bound-var-seq:
//   { ( parsed-bound-var-dcln ) }+
// parsed-bound-var-dcln:
//   {
//     ( WG_PP_MARKER_<NOOP | DEDUCED> parsed-explicit-or-deduced-type )
//     ( var-name )
//   }
//
// parsed-set-var-seq:
//   { ( parsed-set-var-dcln ) }+
// parsed-set-var-dcln:
//   {
//     ( WG_PP_MARKER_<NOOP | DEDUCED> parsed-explicit-or-deduced-type )
//     ( var-name )
//     ( value-expr )
//   }
//
// parsed-explicit-non-local-type-or-deduced-type: =
//     WG_PP_MARKER_NOOP parsed-explicit-non-local-type
//   | WG_PP_MARKER_DEDUCEDTYPE parsed-deduced-type
// parsed-explicit-non-local-type :=
//   type explicit-non-local-type
// parsed-deduced-type :=
//   type( { BT | add_const<BT> | add_ref<BT> | add_ref< add_const<BT> > } )
// BT := BOOST_TYPEOF(some-token)
//
//-------
//OUTPUT:
//-------
// A SymbolTable whose values are accessible using the public API.
#define WG_PP_LCLFUNCTION_SYMBOLTABLE_CREATE( \
  istpl, \
  return_type, \
  paramseq, \
  parsedboundvarseq, \
  parsedsetvarseq) \
    WG_PP_LCLFUNCION_SYMBOLTABLE_CREATE_IMPL1( \
      istpl, \
      return_type, \
      paramseq, \
      parsedboundvarseq, \
      parsedsetvarseq)

//###########
//Impl Macros
//###########

// suffix: must match one of the following: WG_PP_LCLFUNCTION_ST_INDX_<suffix>
#define WG_PP_LCLFUNCTION_SYMBOLTABLE_INDX(suffix) \
  BOOST_PP_CAT(WG_PP_LCLFUNCTION_ST_INDX_, suffix)

#define WG_PP_LCLFUNCTION_ST_INDX_MODULEID 0

#define WG_PP_LCLFUNCTION_ST_INDX_ISTPL 1

#define WG_PP_LCLFUNCTION_ST_INDX_RETTUPLE 2

#define WG_PP_LCLFUNCTION_ST_INDX_DCLNS_PARAMS 3

#define WG_PP_LCLFUNCTION_ST_INDX_DCLNS_BOUNDVAR 4
#define WG_PP_LCLFUNCTION_ST_INDX_THISU_MARKER_BOUNDVAR 5
#define WG_PP_LCLFUNCTION_ST_INDX_DCLNS_SIZE_BOUNDVAR 6

#define WG_PP_LCLFUNCTION_ST_INDX_DCLNS_SETVAR 7
#define WG_PP_LCLFUNCTION_ST_INDX_DCLNS_SIZE_SETVAR 8

#define WG_PP_LCLFUNCTION_ST_INDX_DCLNS_TOTALSIZE 9

// suffix: must match one of the following: WG_PP_LCLFUNCTION_ST_INDX_<suffix>
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
  paramseq, \
  parsedboundvarseq, \
  parsedsetvarseq) \
    WG_PP_LCLFUNCTION_ST_CREATE_IMPL2( \
      istpl, \
      return_type, \
      paramseq, \
      parsedboundvarseq, \
      parsedsetvarseq )

#define WG_PP_LCLFUNCTION_ST_CREATE_IMPL2( \
  istpl, \
  return_type, \
  params_dcln_seq, \
  varbind_dcln_seq, \
  varset_dcln_seq) \
    WG_PP_LCLFUNCTION_ST_CREATE_IMPL3( \
      (9, \
        (WG_PP_LCLFUNCTION_SYMBOLTABLE, \
        istpl, \
        return_type, \
        params_dcln_seq, \
        varbind_dcln_seq, \
        WG_PP_STUTIL_THISU_INDX( \
          varbind_dcln_seq, \
          WG_PP_LCLFUNCTION_SYMBOLTABLE_DCLN_OBJ_BOUNDVAR), \
        WG_PP_SEQ_SIZE(varbind_dcln_seq), \
        varset_dcln_seq, \
        WG_PP_SEQ_SIZE(varset_dcln_seq) )) \
    )

#define WG_PP_LCLFUNCTION_ST_CREATE_IMPL3(wiparray) \
  BOOST_PP_ARRAY_PUSH_BACK( \
    wiparray, \
    BOOST_PP_ADD( \
      WG_PP_LCLFUNCTION_SYMBOLTABLE_DCLNS_SIZE_BOUNDVAR(wiparray), \
      WG_PP_LCLFUNCTION_SYMBOLTABLE_DCLNS_SIZE_SETVAR(wiparray)) )

#endif /* WG_PP_LCLFUNCTION_SYMBOLTABLE_HH_ */
