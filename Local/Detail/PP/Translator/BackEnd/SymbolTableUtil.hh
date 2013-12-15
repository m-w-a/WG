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

// Expands to a sequence of all the types in the order in which they declared
// in nrmlzd_bound_tuple_seq.
//
// nrmlzd_bound_tuple_seq:
//   {normalized-bound-tuple}+
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_STUTIL_BOUNDTUPLESEQ_TO_TYPESEQ(nrmlzd_bound_tuple_seq) \
  WG_PP_STUTIL_BOUNDTUPLESEQ_TO_TYPESEQ_IMPL(nrmlzd_bound_tuple_seq)

// Expands to a sequence of all the objects in the order in which they declared
// in nrmlzd_bound_tuple_seq.
//
// nrmlzd_bound_tuple_seq:
//   {normalized-bound-tuple}+
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_STUTIL_BOUNDTUPLESEQ_TO_OBJSEQ(nrmlzd_bound_tuple_seq) \
  WG_PP_STUTIL_BOUNDTUPLESEQ_TO_OBJSEQ_IMPL(nrmlzd_bound_tuple_seq)

// Expands to a sequence of all the types in the order in which they declared
// in nrmlzd_bound_tuple_seq.
//
// nrmlzd_set_tuple_seq:
//   {normalized-set-tuple}+
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_STUTIL_SETTUPLESEQ_TO_TYPESEQ(nrmlzd_set_tuple_seq) \
  WG_PP_STUTIL_SETTUPLESEQ_TO_TYPESEQ_IMPL(nrmlzd_set_tuple_seq)

// Expands to a sequence of all the objects in the order in which they declared
// in nrmlzd_bound_tuple_seq.
//
// nrmlzd_set_tuple_seq:
//   {normalized-set-tuple}+
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_STUTIL_SETTUPLESEQ_TO_OBJSEQ(nrmlzd_set_tuple_seq) \
  WG_PP_STUTIL_SETTUPLESEQ_TO_OBJSEQ_IMPL(nrmlzd_set_tuple_seq)

// Expands to a sequence of all the value expressions in the order in which
// they declared in nrmlzd_bound_tuple_seq.
//
// nrmlzd_set_tuple_seq:
//   {normalized-set-tuple}+
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_STUTIL_SETTUPLESEQ_TO_VALUESEQ(nrmlzd_set_tuple_seq) \
  WG_PP_STUTIL_SETTUPLESEQ_TO_VALUESEQ_IMPL(nrmlzd_set_tuple_seq)

// bound_obj_seq:
//   The expansion of WG_PP_STUTIL_BOUNDTUPLESEQ_TO_OBJSEQ.
//
// Returns: { BOOST_PP_NIL | integer }
#define WG_PP_STUTIL_THISU_INDX(bound_obj_seq) \
  WG_PP_STUTIL_THISU_INDX_IMPL1(bound_obj_seq)

//------
//INPUT:
//------
// The symbol table created using <symbol-moduleid>_SYMBOLTABLE_CREATE.
// This symbol table must have the result of the following defined:
//   1) WG_PP_STUTIL_CALL_F1(suffix, symbtbl, symbtbl)
//   2) WG_PP_STUTIL_CALL_F1(INDX, symbtbl, suffix)
// where suffix is declared in specseq
//
// specseq:
//   { ( suffix ) }+
//
// callback:
//   A three argument macro to apply to the sequence(s) to be replaced.
//   The first arg will be the sequence as specified by specseq.
//   The second arg will be a zero-based index into specseq specifying which
//   sequence was passed as the first arg.
//   The third arg will be the user specified data.
//
// data:
//   An argument to callback.
//
//-------
//OUTPUT:
//-------
// A symbol table where:
//   1) The sequence associated with
//     WG_PP_STUTIL_CALL_F1(suffix, symbtbl, symbtbl) is replaced by
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
#define WG_PP_STUTIL_SEQUENCE_IF_INDEX(r, CONDITION, indx, elem) \
  BOOST_PP_EXPR_IF( \
    CONDITION(indx), \
    BOOST_PP_LPAREN() elem BOOST_PP_RPAREN())

#define WG_PP_STUTIL_BOUNDTUPLESEQ_TO_TYPESEQ_IMPL(nrmlzd_bound_tuple_seq) \
  WG_PP_SEQ_FOR_EACH_I( \
    WG_PP_STUTIL_SEQUENCE_IF_INDEX, \
    WG_PP_IS_EVEN, \
    nrmlzd_bound_tuple_seq)

#define WG_PP_STUTIL_BOUNDTUPLESEQ_TO_OBJSEQ_IMPL(nrmlzd_bound_tuple_seq) \
  WG_PP_SEQ_FOR_EACH_I( \
    WG_PP_STUTIL_SEQUENCE_IF_INDEX, \
    WG_PP_IS_ODD, \
    nrmlzd_bound_tuple_seq)

#define WG_PP_STUTIL_SETTUPLESEQ_TO_TYPESEQ_IMPL(nrmlzd_set_tuple_seq) \
  WG_PP_SEQ_FOR_EACH_I( \
    WG_PP_STUTIL_SEQUENCE_IF_INDEX, \
    WG_PP_IS_MOD3_R0, \
    nrmlzd_set_tuple_seq)

#define WG_PP_STUTIL_SETTUPLESEQ_TO_OBJSEQ_IMPL(nrmlzd_set_tuple_seq) \
  WG_PP_SEQ_FOR_EACH_I( \
    WG_PP_STUTIL_SEQUENCE_IF_INDEX, \
    WG_PP_IS_MOD3_R1, \
    nrmlzd_set_tuple_seq)

#define WG_PP_STUTIL_SETTUPLESEQ_TO_VALUESEQ_IMPL(nrmlzd_set_tuple_seq) \
  WG_PP_SEQ_FOR_EACH_I( \
    WG_PP_STUTIL_SEQUENCE_IF_INDEX, \
    WG_PP_IS_MOD3_R2, \
    nrmlzd_set_tuple_seq)

//----------------------
//Calculate this_ index.
//----------------------

#define WG_PP_STUTIL_THISU_INDX_IMPL1(bound_obj_seq) \
  WG_PP_STUTIL_THISU_INDX_IMPL( \
    (BOOST_PP_NIL) \
    WG_PP_SEQ_NOTHING_FOR_EACH_I( \
      WG_PP_STUTIL_THISU_MARK_INDX, ~, bound_obj_seq))

#define WG_PP_STUTIL_THISU_INDX_IMPL_0 BOOST_PP_NIL
#define WG_PP_STUTIL_THISU_INDX_IMPL_1(indx) indx
#define WG_PP_STUTIL_THISU_INDX_IMPL(seq) \
  BOOST_PP_CAT( \
    WG_PP_STUTIL_THISU_INDX_IMPL_, \
    WG_PP_ISNEXTTOKEN_A_TUPLE( \
      1, BOOST_PP_TUPLE_EAT(1)seq BOOST_PP_NIL)) BOOST_PP_TUPLE_EAT(1)seq

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_STUTIL_THISU_MARK_INDX(r, data, indx, elem) \
  BOOST_PP_EXPR_IIF( \
    WG_PP_KEYWORDS_STARTSWITH_THISU(elem), \
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
      WG_PP_STUTIL_CALL_F1(INDX, symbtbl, spec), \
      callback(WG_PP_STUTIL_CALL_F1(spec, symbtbl, symbtbl), iteration, data) )

#endif /* WG_PP_SYMBOLTABLEUTIL_HH_ */
