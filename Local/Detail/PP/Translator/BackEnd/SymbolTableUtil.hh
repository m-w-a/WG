#ifndef WG_PP_SYMBOLTABLEUTIL_HH_
#define WG_PP_SYMBOLTABLEUTIL_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/PP.hh>
#include <WG/Local/Detail/PP/Seq.hh>
#include <WG/Local/Detail/PP/Translator/Keywords.hh>

//----------------------------------------------------------------------------//
// This is a "friend" of SymbolTable.
// Therefore it is ok if it assumes SymbolTable is implemented as a pp array.
//----------------------------------------------------------------------------//

//################
//Interface Impls.
//  (Implements interfaces required by external macros.)
//################

// Expands to <symbtbl-moduleid>_<function>(arg)
//
// symbtbl:
//   The first element must be the moduleid.
#define WG_PP_STUTIL_CALL_F1(function, symbtbl, arg) \
  WG_PP_UCAT_ARG2( \
    BOOST_PP_ARRAY_ELEM(0, symbtbl), function) (arg)

// Expands to <symbtbl-moduleid>_<functionpt1>_<functionpt2>(arg)
//
// symbtbl:
//   The first element must be the moduleid.
#define WG_PP_STUTIL_CALL_F2(functionpt1, functionpt2, symbtbl, arg) \
  WG_PP_UCAT_ARG3( \
    BOOST_PP_ARRAY_ELEM(0, symbtbl), functionpt1, functionpt2) \
  (arg)

//###########
//Public APIs
//###########

// Expands to { BOOST_PP_NIL | { (normalized-bound-tuple) }+ }
//
// nrmlzd_bound_tuple_seq:
//  { BOOST_PP_NIL | {normalized-bound-tuple}+ }
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_STUTIL_NRMLZDBOUNDTUPLESEQ_TO_BOUNDDCLNSEQ( \
  nrmlzd_bound_tuple_seq) \
    WG_PP_STUTIL_NRMLZDBOUNDTUPLESEQ_TO_BOUNDDCLNSEQ_IMPL(nrmlzd_bound_tuple_seq)

// Expands to { BOOST_PP_NIL | { (normalized-set-tuple) }+ }
//
// nrmlzd_set_tuple_seq:
//   { BOOST_PP_NIL | {normalized-set-tuple}+ }
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_STUTIL_NRMLZDSETTUPLESEQ_TO_SETDCLNSEQ(nrmlzd_set_tuple_seq) \
  WG_PP_STUTIL_NRMLZDSETTUPLESEQ_TO_SETDCLNSEQ_IMPL(nrmlzd_set_tuple_seq)

// decln_seq:
//   Some sequence of dclnS that have associated objects.
// decln_objmacro:
//   A 1-arg macro that when applied to a decln expands to the obj associated
//   with that macro.
//
// Returns: { BOOST_PP_NIL | integer }
#define WG_PP_STUTIL_THISU_INDX(decln_seq, decln_objmacro) \
  WG_PP_STUTIL_THISU_INDX_IMPL1(decln_seq, decln_objmacro)

//------
//INPUT:
//------
// The symbol table created using <symbol-moduleid>_SYMBOLTABLE_CREATE.
// This symbol table must have the result of the following defined:
//   1) WG_PP_STUTIL_CALL_F2(DCLNS, suffix, symbtbl, symbtbl)
//   2) WG_PP_STUTIL_CALL_F1(INDX, symbtbl, WG_PP_UCAT_ARG2(DCLNS,suffix) )
// where suffix is declared in specseq
//
// specseq:
//   { ( suffix ) }+
//
// callback:
//   A three argument macro to apply to the sequence(s) to be replaced.
//   The first arg will be the sequence from the symbtbl that needs to be
//   replaced, as specified by specseq.
//   The second arg will be a zero-based index into specseq specifying which
//   spec is being processed.
//   The third arg will be some user specified data.
//
// data:
//   An argument to callback.
//
//-------
//OUTPUT:
//-------
// A symbol table where:
//   1) The sequence associated with
//     WG_PP_STUTIL_CALL_F2(DCLNS, suffix, symbtbl, symbtbl) is replaced by
//     "callback(the-said-sequence, iteration, data)"
//
#define WG_PP_STUTIL_REPLACESEQ(symbtbl, specseq, callback, data) \
  WG_PP_STUTIL_REPLACESEQ_IMPL(symbtbl, specseq, callback, data)

//###########
//Impl Macros
//###########

//------------------------
//Partitioning Operations.
//------------------------

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_STUTIL_TUPLIZE_NRMLZDBOUNDTUPLE(r, data, indx, elem) \
  BOOST_PP_IIF(WG_PP_IS_EVEN(indx), BOOST_PP_LPAREN, BOOST_PP_EMPTY ) () \
  ( elem ) \
  BOOST_PP_IIF(WG_PP_IS_ODD(indx), BOOST_PP_RPAREN, BOOST_PP_EMPTY ) ()

#define WG_PP_STUTIL_NRMLZDBOUNDTUPLESEQ_TO_BOUNDDCLNSEQ_IMPL( \
  nrmlzd_bound_tuple_seq) \
    WG_PP_SEQ_FOR_EACH_I( \
      WG_PP_STUTIL_TUPLIZE_NRMLZDBOUNDTUPLE, \
      ~, \
      nrmlzd_bound_tuple_seq)

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_STUTIL_TUPLIZE_NRMLZDSETTUPLE(r, data, indx, elem) \
  BOOST_PP_IIF(WG_PP_IS_MOD3_R0(indx), BOOST_PP_LPAREN, BOOST_PP_EMPTY ) () \
  ( elem ) \
  BOOST_PP_IIF(WG_PP_IS_MOD3_R2(indx), BOOST_PP_RPAREN, BOOST_PP_EMPTY ) ()

#define WG_PP_STUTIL_NRMLZDSETTUPLESEQ_TO_SETDCLNSEQ_IMPL( \
  nrmlzd_set_tuple_seq) \
    WG_PP_SEQ_FOR_EACH_I( \
      WG_PP_STUTIL_TUPLIZE_NRMLZDSETTUPLE, \
      ~, \
      nrmlzd_set_tuple_seq)

//----------------------
//Calculate this_ index.
//----------------------

#define WG_PP_STUTIL_THISU_INDX_IMPL1(decln_seq, decln_objmacro) \
  WG_PP_STUTIL_THISU_INDX_IMPL( \
    (BOOST_PP_NIL) \
    WG_PP_SEQ_NOTHING_FOR_EACH_I( \
      WG_PP_STUTIL_THISU_MARK_INDX, decln_objmacro, decln_seq))

#define WG_PP_STUTIL_THISU_INDX_IMPL_0 BOOST_PP_NIL
#define WG_PP_STUTIL_THISU_INDX_IMPL_1(indx) indx
#define WG_PP_STUTIL_THISU_INDX_IMPL(seq) \
  BOOST_PP_CAT( \
    WG_PP_STUTIL_THISU_INDX_IMPL_, \
    WG_PP_ISNEXTTOKEN_A_TUPLE( \
      1, BOOST_PP_TUPLE_EAT(1)seq BOOST_PP_NIL)) BOOST_PP_TUPLE_EAT(1)seq

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_STUTIL_THISU_MARK_INDX(r, decln_objmacro, indx, decln) \
  BOOST_PP_EXPR_IIF( \
    WG_PP_KEYWORDS_STARTSWITH_THISU( decln_objmacro(decln) ), \
    (indx))

//---------------------
//UseTypeDeducer Macros
//---------------------

#define WG_PP_STUTIL_REPLACESEQ_WHILE_STATE_INIT( \
  symbtbl, specseq, callback, data) \
  /* If this is modified then WG_PP_STUTIL_REPLACESEQ_WHILE_OP has to be */ \
  /* updated. */ \
    (0, specseq, callback, data, symbtbl)
#define WG_PP_STUTIL_REPLACESEQ_WHILE_STATE_ELEM(indx, state) \
  BOOST_PP_TUPLE_ELEM(5, indx, state)
#define WG_PP_STUTIL_REPLACESEQ_WHILE_STATE_ITERATION(state) \
  WG_PP_STUTIL_REPLACESEQ_WHILE_STATE_ELEM(0, state)
#define WG_PP_STUTIL_REPLACESEQ_WHILE_STATE_SPECSEQ(state) \
  WG_PP_STUTIL_REPLACESEQ_WHILE_STATE_ELEM(1, state)
#define WG_PP_STUTIL_REPLACESEQ_WHILE_STATE_CALLBACK(state) \
  WG_PP_STUTIL_REPLACESEQ_WHILE_STATE_ELEM(2, state)
#define WG_PP_STUTIL_REPLACESEQ_WHILE_STATE_CALLBACKDATA(state) \
  WG_PP_STUTIL_REPLACESEQ_WHILE_STATE_ELEM(3, state)
#define WG_PP_STUTIL_REPLACESEQ_WHILE_STATE_SYMBTBL(state) \
  WG_PP_STUTIL_REPLACESEQ_WHILE_STATE_ELEM(4, state)

#define WG_PP_STUTIL_REPLACESEQ_WHILE_PRED(d, state) \
  BOOST_PP_GREATER( \
    BOOST_PP_SEQ_SIZE(\
      WG_PP_STUTIL_REPLACESEQ_WHILE_STATE_SPECSEQ(state)), \
    1)

#define WG_PP_STUTIL_REPLACESEQ_WHILE_OP(d, state) \
  ( \
    BOOST_PP_INC(WG_PP_STUTIL_REPLACESEQ_WHILE_STATE_ITERATION(state)), \
    BOOST_PP_SEQ_POP_FRONT(WG_PP_STUTIL_REPLACESEQ_WHILE_STATE_SPECSEQ(state)), \
    WG_PP_STUTIL_REPLACESEQ_WHILE_STATE_CALLBACK(state), \
    WG_PP_STUTIL_REPLACESEQ_WHILE_STATE_CALLBACKDATA(state), \
    WG_PP_STUTIL_REPLACESEQ_REPLACESPEC( \
      WG_PP_STUTIL_REPLACESEQ_WHILE_STATE_SYMBTBL(state), \
      BOOST_PP_SEQ_HEAD( \
        WG_PP_STUTIL_REPLACESEQ_WHILE_STATE_SPECSEQ(state)), \
      WG_PP_STUTIL_REPLACESEQ_WHILE_STATE_CALLBACK(state), \
      WG_PP_STUTIL_REPLACESEQ_WHILE_STATE_ITERATION(state), \
      WG_PP_STUTIL_REPLACESEQ_WHILE_STATE_CALLBACKDATA(state) ) \
  )

#define WG_PP_STUTIL_REPLACESEQ_IMPL( \
  symbtbl, specseq, callback, data) \
    WG_PP_STUTIL_REPLACESEQ_WHILE_STATE_SYMBTBL( \
      BOOST_PP_WHILE( \
        WG_PP_STUTIL_REPLACESEQ_WHILE_PRED, \
        WG_PP_STUTIL_REPLACESEQ_WHILE_OP, \
        WG_PP_STUTIL_REPLACESEQ_WHILE_STATE_INIT( \
          symbtbl, \
          specseq (BOOST_PP_NIL), \
          callback, \
          data )))

// WORKAROUND for BOOST_PP_ARRAY_REPLACE bug.
#ifndef BOOST_PP_TUPLE_REM_0
#define BOOST_PP_TUPLE_REM_0() // nothing
#endif

#define WG_PP_STUTIL_REPLACESEQ_REPLACESPEC( \
  symbtbl, spec, callback, iteration, data) \
    BOOST_PP_ARRAY_REPLACE( \
      symbtbl, \
      WG_PP_STUTIL_CALL_F1(INDX, symbtbl, WG_PP_UCAT_ARG2(DCLNS,spec) ), \
      callback( \
        WG_PP_STUTIL_CALL_F2(DCLNS, spec, symbtbl, symbtbl), \
        iteration, \
        data) )

#endif /* WG_PP_SYMBOLTABLEUTIL_HH_ */
