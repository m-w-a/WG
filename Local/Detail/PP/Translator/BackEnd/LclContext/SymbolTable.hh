#ifndef WG_PP_LCLCONTEXT_SYMBOLTABLE_HH_
#define WG_PP_LCLCONTEXT_SYMBOLTABLE_HH_

#include <boost/preprocessor.hpp>

//###########
//Public APIs
//###########

#define WG_PP_LCLCONTEXT_SYMBOLTABLE_MODULEID(symbtbl) \
  WG_PP_LCLCONTEXT_ST_GET(symbtbl, MODULEID)

#define WG_PP_LCLCONTEXT_SYMBOLTABLE_ISTPL(symbtbl) \
  WG_PP_LCLCONTEXT_ST_GET(symbtbl, ISPTL)

#define WG_PP_LCLCONTEXT_SYMBOLTABLE_ISNOEX(symbtbl) \
  WG_PP_LCLCONTEXT_ST_GET(symbtbl, NOEX)

// Returns: { symblseq }
#define WG_PP_LCLCONTEXT_SYMBOLTABLE_SYMBOLS(symbtbl) \
  WG_PP_LCLCONTEXT_ST_GET(symbtbl, SYMBOLS)

#define WG_PP_LCLCONTEXT_SYMBOLTABLE_SYMBOLS_TOTALCOUNT(symbtbl) \
  WG_PP_LCLCONTEXT_ST_GET(symbtbl, SYMBOLS_TOTALCOUNT)

//------
//Symbol
//------

#define WG_PP_LCLCONTEXT_SYMBOLTABLE_SYMBOL_CATEGORY(symbol) \
  BOOST_PP_SEQ_ELEM(0, symbol)

#define WG_PP_LCLCONTEXT_SYMBOLTABLE_SYMBOL_CATEGORY_ISEXTANT(symbol) \
  BOOST_PP_EQUAL( \
    0, \
    BOOST_PP_SEQ_ELEM(1,symbol) )

#define WG_PP_LCLCONTEXT_SYMBOLTABLE_SYMBOL_CATEGORY_ISADHOC(symbol) \
  BOOST_PP_EQUAL( \
    1, \
    BOOST_PP_SEQ_ELEM(1,symbol) )

//------------
//ExtantSymbol
//------------

// Returns: { unsigned-integer }
#define WG_PP_LCLCONTEXT_SYMBOLTABLE_EXTANTSYMBOL_ID(symbol) \
  BOOST_PP_SEQ_ELEM(2, symbol)

// Returns: { scopemngrseq }
#define WG_PP_LCLCONTEXT_SYMBOLTABLE_EXTANTSYMBOL_SCOPEMNGRSEQ(symbol) \
  BOOST_PP_SEQ_ELEM(3, symbol)

// Returns: { nrmlzdenteredasseq }
#define WG_PP_LCLCONTEXT_SYMBOLTABLE_EXTANTSYMBOL_NRMLZDENTEREDASSEQ(symbol) \
  BOOST_PP_SEQ_ELEM(4, symbol)

//-----------
//AdhocSymbol
//-----------

// Returns: { unsigned-integer }
#define WG_PP_LCLCONTEXT_SYMBOLTABLE_ADHOCSYMBOL_ID(symbol) \
  BOOST_PP_SEQ_ELEM(2, symbol)

#define WG_PP_LCLCONTEXT_SYMBOLTABLE_ADHOCSYMBOL_VARBINDSEQ(symbol) \
  BOOST_PP_SEQ_ELEM(3, symbol)

#define WG_PP_LCLCONTEXT_SYMBOLTABLE_ADHOCSYMBOL_ONENTERSEQ(symbol) \
  BOOST_PP_SEQ_ELEM(4, symbol)

#define WG_PP_LCLCONTEXT_SYMBOLTABLE_ADHOCSYMBOL_ONEXITSEQ(symbol) \
  BOOST_PP_SEQ_ELEM(5, symbol)

//-----
//NOTE:
//-----
//
//What ever terms not defined here are defined in the respective BNF.
//------
//INPUT:
//------
//
// istpl:
//   { (0|1) }
// noex:
//   { (0|1) }
// symblseq:
//   { BOOST_PP_NIL | { ( symbol ) }+ }
//
// symbol :=
//     extantsymbol
//   | adhocsymbol
//
// extantsymbol :=
//   ( WG_PP_LCLCONTEXT_SYMBOL_CATEGORY_EXTANT )
//   ( categoryid )
//   ( symbolid )
//   ( scopemngrseq )
//   ( nrmlzdenteredasseq )
//
// adhocsymbol :=
//   ( WG_PP_LCLCONTEXT_SYMBOL_CATEGORY_ADHOC )
//   ( categoryid )
//   ( symbolid )
//   ( varbindseq )
//   ( onenterseq )
//   ( onexitseq )
//
// symbolid := int
// scopemngrseq := { BOOST_PP_NIL | ( scope-manager-expr ) }
// nrmlzdenteredasseq := { BOOST_PP_NIL |  ( normalized-bound-nlt-tuple ) }
// varbindseq = bound-tuple-seq
// onenterseq := { BOOST_PP_NIL | ( compound-statement ) }
// onexitseq := { BOOST_PP_NIL | ( compound-statement ) }
//
// normalized-bound-nlt-tuple :=
//   (parsed-explicit-non-local-type-or-deduced-type)(var-name)
// parsed-explicit-non-local-type-or-deduced-type :=
//    WG_PP_MARKER_NOOP parsed-explicit-non-local-type
//  | WG_PP_MARKER_DEDUCEDTYPE parsed-deduced-type
// parsed-explicit-non-local-type := type explicit-non-local-type
// parsed-deduced-type :=
//   type( { BT | add_const<BT> | add_ref<BT> | add_ref< add_const<BT> > } )
// BT := BOOST_TYPEOF(some-token)
//
//-------
//OUTPUT:
//-------
// A SymbolTable whose values are accessible using the public API.
#define WG_PP_LCLCONTEXT_SYMBOLTABLE_CREATE(istpl, noex, symblseq) \
  WG_PP_LCLCONTEXT_SYMBOLTABLE_CREATE_IMPL(istpl, noex, symblseq)

//###########
//Impl Macros
//###########

// suffix: must match one of the following: WG_PP_LCLCONTEXT_ST_INDX_<suffix>
#define WG_PP_LCLCONTEXT_SYMBOLTABLE_INDX(suffix) \
  BOOST_PP_CAT(WG_PP_LCLCONTEXT_ST_INDX_, suffix)

#define WG_PP_LCLCONTEXT_ST_INDX_MODULEID 0

#define WG_PP_LCLCONTEXT_ST_INDX_ISTPL 1

#define WG_PP_LCLCONTEXT_ST_INDX_ISNOEX 2

#define WG_PP_LCLCONTEXT_ST_INDX_SYMBOLS 3

#define WG_PP_LCLCONTEXT_ST_INDX_SYMBOLS_TOTALCOUNT 4

// suffix: must match one of the following: WG_PP_LCLCONTEXT_ST_INDX_<suffix>
#define WG_PP_LCLCONTEXT_ST_GET(symbtbl, suffix) \
  BOOST_PP_ARRAY_ELEM( \
    BOOST_PP_CAT(WG_PP_LCLCONTEXT_ST_INDX_, suffix), \
    symbtbl)

#define WG_PP_LCLCONTEXT_SYMBOLTABLE_CREATE_IMPL(istpl, noex, symblseq) \
  ( \
    5, \
    (WG_PP_LCLCONTEXT_SYMBOLTABLE, \
    istpl, \
    noex, \
    symblseq, \
    BOOST_PP_SEQ_SIZE(symblseq)), \
  )


#endif /* WG_PP_LCLCONTEXT_SYMBOLTABLE_HH_ */
