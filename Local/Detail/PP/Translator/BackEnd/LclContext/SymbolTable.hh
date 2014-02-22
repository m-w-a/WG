#ifndef WG_PP_LCLCONTEXT_SYMBOLTABLE_HH_
#define WG_PP_LCLCONTEXT_SYMBOLTABLE_HH_

#include <boost/preprocessor.hpp>

//################
//Interface Impls.
//  (Implements interfaces required by external macros.)
//################

#define WG_PP_LCLCONTEXT_SYMBOLTABLE_MODULEID(symbtbl) \
  WG_PP_LCLCONTEXT_ST_GET(symbtbl, MODULEID)

#define WG_PP_LCLCONTEXT_SYMBOLTABLE_ISTPL(symbtbl) \
  WG_PP_LCLCONTEXT_ST_GET(symbtbl, ISPTL)

#define WG_PP_LCLCONTEXT_SYMBOLTABLE_ISNOEX(symbtbl) \
  WG_PP_LCLCONTEXT_ST_GET(symbtbl, NOEX)

//###########
//Public APIs
//###########

//-----
//NOTE:
//-----
//
// What ever terms not defined here are defined in the respective BNF.
//------
//INPUT:
//------
// istpl_noex: { (0|1)(0|1) }
// withas_dcln_seq:
//   { BOOST_PP_NIL | { ( with-as-dcln ) }+ }
// withadhoc_dcln_seq:
//   { BOOST_PP_NIL | { ( with-adhoc-dcln ) }+ }
// orderedenteredas_seq:
//   { ( orderedenteredas-dcln ) }+
//
// with-as-dcln :=
//   normalized-bound-tuple [normalized-bound-tuple]
// with-adhoc-dcln :=
//   captured-vars-seq onenter-tuple onexit-tuple
// orderedenteredas-dcln :=
//  { (identifier) | (identifier)(identifier)(non-negative-integer) }
// captured-vars-seq :=
//   { BOOST_PP_NIL | ( { (normalized-bound-tuple) }+ ) }
// onenter-tuple :=
//   compound-statement
// onexit-tuple :=
//   compound-statement
//
// normalized-bound-tuple := (parsed-explicit-or-deduced-type)(var-name)
// parsed-explicit-or-deduced-type :=
//     WG_PP_MARKER_NOOP parsed-explicit-type
//   | WG_PP_MARKER_DEDUCEDTYPE parsed-deduced-type
// parsed-explicit-type := parsed-local-type | type explicit-non-local-type
// parsed-local-type := local(some-token) lib-type-qualifier-seq
// lib-type-qualifier-seq := (const) | (ref) | (const)(ref)
// parsed-deduced-type :=
//   type( { BT | add_const<BT> | add_ref<BT> | add_ref< add_const<BT> > } )
// BT := BOOST_TYPEOF(some-token)
//
//-------
//OUTPUT:
//-------
//A SymbolTable whose values are accessible using the public API.
#define WG_PP_LCLCONTEXT_SYMBOLTABLE_CREATE( \
  istpl_noex, \
  withas_dcln_seq, \
  withadhoc_dcln_seq, \
  orderedenteredas_seq) \
    TODO

//###########
//Impl Macros
//###########

#define WG_PP_LCLCONTEXT_ST_INDX_MODULEID 0

#define WG_PP_LCLCONTEXT_ST_INDX_ISTPL 1

#define WG_PP_LCLCONTEXT_ST_INDX_ISNOEX 2

#define WG_PP_LCLCONTEXT_ST_INDX_DCLNS_WITHAS 3
#define WG_PP_LCLCONTEXT_ST_INDX_DCLNS_SIZE_WITHAS 4

#define WG_PP_LCLCONTEXT_ST_INDX_DCLNS_WITHADHOC 5
#define WG_PP_LCLCONTEXT_ST_INDX_DCLNS_SIZE_WITHADHOC 6

#define WG_PP_LCLCONTEXT_ST_INDX_SEQ_ORDEREDENTEREDAS 7

#define WG_PP_LCLCONTEXT_ST_INDX_DCLNS_TOTALSIZE 8

// suffix: must match one of the following: WG_PP_LCLCONTEXT_ST_INDX_<suffix>
#define WG_PP_LCLCONTEXT_ST_GET(symbtbl, suffix) \
  BOOST_PP_ARRAY_ELEM( \
    BOOST_PP_CAT(WG_PP_LCLCONTEXT_ST_INDX_, suffix), \
    symbtbl)

#endif /* WG_PP_LCLCONTEXT_SYMBOLTABLE_HH_ */
