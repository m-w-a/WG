#ifndef WG_PP_LCLCLASS_SYMBOLTABLE_HH_
#define WG_PP_LCLCLASS_SYMBOLTABLE_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/Seq.hh>
#include <WG/Local/Detail/PP/PP.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/SymbolTableUtil.hh>

//#######################
//STUTIL Interface Impls.
//#######################

// suffix: must match one of the following: WG_PP_LCLCLASS_ST_INDX_<suffix>
#define WG_PP_LCLCLASS_SYMBOLTABLE_INDX(suffix) \
  BOOST_PP_CAT(WG_PP_LCLCLASS_ST_INDX_, suffix)

//###########
//Public APIs
//###########

#define WG_PP_LCLCLASS_SYMBOLTABLE_MODULEID(symbtbl) \
  WG_PP_LCLCLASS_ST_GET(symbtbl, MODULEID)

#define WG_PP_LCLCLASS_SYMBOLTABLE_ISTPL(symbtbl) \
  WG_PP_LCLCLASS_ST_GET(symbtbl, ISTPL)

// Returns: { BOOST_PP_NIL | derives-tuple-seq }
#define WG_PP_LCLCLASS_SYMBOLTABLE_DERIVESSEQ(symbtbl) \
  WG_PP_LCLCLASS_ST_GET(symbtbl, DERIVESSEQ)

//------
//MemExt
//------

// dcln: memext-dcln
// Returns: parsed-explicit-or-deduced-type
#define WG_PP_LCLCLASS_SYMBOLTABLE_DCLN_GETTYPE_MEMEXT(dcln) \
  WG_PP_SEQ_ELEM(0, dcln)

// dcln: memext-dcln
// type: the replacement type for dcln.
// Returns: memext-dcln
#define WG_PP_LCLCLASS_SYMBOLTABLE_DCLN_SETTYPE_MEMEXT(dcln, type) \
  WG_PP_SEQ_REPLACE(dcln, 0, type)

// Returns: var-name
#define WG_PP_LCLCLASS_SYMBOLTABLE_DCLN_OBJ_MEMEXT(dcln) \
  WG_PP_SEQ_ELEM(1, dcln)

// Returns: { BOOST_PP_NIL | { (memext-dcln) }+ }
#define WG_PP_LCLCLASS_SYMBOLTABLE_DCLNS_MEMEXT(symbtbl) \
  WG_PP_LCLCLASS_ST_GET(symbtbl, DCLNS_MEMEXT)

// Returns: { integer }
#define WG_PP_LCLCLASS_SYMBOLTABLE_DCLNS_SIZE_MEMEXT(symbtbl) \
  WG_PP_LCLCLASS_ST_GET(symbtbl, DCLNS_SIZE_MEMEXT)

// Returns: { BOOST_PP_NIL | integer }
#define WG_PP_LCLCLASS_SYMBOLTABLE_DCLNS_THISU_MARKER_MEMEXT(symbtbl) \
  WG_PP_LCLCLASS_ST_GET(symbtbl, DCLNS_THISU_MARKER_MEMEXT)

//------
//MemInt
//------

// dcln: memint-dcln
// Returns: parsed-explicit-type-or-deduced-type
#define WG_PP_LCLCLASS_SYMBOLTABLE_DCLN_GETTYPE_MEMINT(dcln) \
  WG_PP_SEQ_ELEM(0, dcln)

// dcln: memint-dcln
// type: the replacement type for dcln.
// Returns: memint-dcln
#define WG_PP_LCLCLASS_SYMBOLTABLE_DCLN_SETTYPE_MEMINT(dcln, type) \
  WG_PP_SEQ_REPLACE(dcln, 0, type)

// dcln: memint-dcln
// Returns: var-name
#define WG_PP_LCLCLASS_SYMBOLTABLE_DCLN_OBJ_MEMINT(dcln) \
  WG_PP_SEQ_ELEM(1, dcln)

// dcln: memint-dcln
// Returns: value-expr
#define WG_PP_LCLCLASS_SYMBOLTABLE_DCLN_VALUE_MEMINT(dcln) \
  WG_PP_SEQ_ELEM(2, dcln)

// Returns: { BOOST_PP_NIL | { (memint-dcln) }+ }
#define WG_PP_LCLCLASS_SYMBOLTABLE_DCLNS_MEMINT(symbtbl) \
  WG_PP_LCLCLASS_ST_GET(symbtbl, DCLNS_MEMINT)

// Returns: { integer }
#define WG_PP_LCLCLASS_SYMBOLTABLE_DCLNS_SIZE_MEMINT(symbtbl) \
  WG_PP_LCLCLASS_ST_GET(symbtbl, DCLNS_SIZE_MEMINT)

//-----
//Misc.
//-----

//Returns: { integer }
#define WG_PP_LCLCLASS_SYMBOLTABLE_DCLNS_TOTALSIZE(symbtbl) \
  WG_PP_LCLCLASS_ST_GET(symbtbl, DCLNS_TOTALSIZE)

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
//
//memext-dcln: normalized-bound-tuple
//memint-dcln: normalized-set-tuple
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

#define WG_PP_LCLCLASS_ST_INDX_DCLNS_MEMEXT 3
#define WG_PP_LCLCLASS_ST_INDX_DCLNS_THISU_MARKER_MEMEXT 4
#define WG_PP_LCLCLASS_ST_INDX_DCLNS_SIZE_MEMEXT 5

#define WG_PP_LCLCLASS_ST_INDX_DCLNS_MEMINT 6
#define WG_PP_LCLCLASS_ST_INDX_DCLNS_SIZE_MEMINT 7

#define WG_PP_LCLCLASS_ST_INDX_DCLNS_TOTALSIZE 8

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
      WG_PP_STUTIL_NRMLZDBOUNDTUPLESEQ_TO_BOUNDDCLNSEQ(memext_nrmlzd_tupleseq), \
      WG_PP_STUTIL_NRMLZDSETTUPLESEQ_TO_SETDCLNSEQ(memint_nrmlzd_tupleseq) )

#define WG_PP_LCLCLASS_SYMBOLTABLE_CREATE_IMPL2( \
  istpl, \
  derives_nrmlzd_tuple, \
  memext_dcln_seq, \
  memint_dcln_seq) \
    WG_PP_LCLCLASS_SYMBOLTABLE_CREATE_IMPL3( \
      (8, \
        (WG_PP_LCLCLASS_SYMBOLTABLE, \
        istpl, \
        derives_nrmlzd_tuple, \
        memext_dcln_seq, \
        WG_PP_STUTIL_THISU_INDX( \
          memext_dcln_seq, WG_PP_LCLCLASS_SYMBOLTABLE_DCLN_OBJ_MEMEXT), \
        WG_PP_SEQ_SIZE(memext_dcln_seq), \
        memint_dcln_seq, \
        WG_PP_SEQ_SIZE(memint_dcln_seq) )) \
    )

#define WG_PP_LCLCLASS_SYMBOLTABLE_CREATE_IMPL3(wiparray) \
  BOOST_PP_ARRAY_PUSH_BACK( \
    wiparray, \
    BOOST_PP_ADD( \
      WG_PP_LCLCLASS_SYMBOLTABLE_DCLNS_SIZE_MEMEXT(wiparray), \
      WG_PP_LCLCLASS_SYMBOLTABLE_DCLNS_SIZE_MEMINT(wiparray) ))

#endif /* WG_PP_LCLCLASS_SYMBOLTABLE_HH_ */
