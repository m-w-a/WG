#ifndef WG_PP_SYMBOLTABLEUTIL_HH_
#define WG_PP_SYMBOLTABLEUTIL_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP.hh>
#include <WG/Local/Detail/Seq.hh>
#include <WG/Local/Detail/Keywords.hh>
#include <WG/Local/Detail/BackEnd/TypeDeducer.hh>

//###########
//Public APIs
//###########

// Expands to a sequence of all the types in the order in which they declared
// in nrmlzd_bound_tuple_seq.
// nrmlzd_bound_tuple_seq:
//   {normalized-bound-tuple}+
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_STUTIL_BOUNDTUPLESEQ_TO_TYPESEQ(nrmlzd_bound_tuple_seq) \
  WG_PP_STUTIL_BOUNDTUPLESEQ_TO_TYPESEQ_IMPL(nrmlzd_bound_tuple_seq)

// Expands to a sequence of all the objects in the order in which they declared
// in nrmlzd_bound_tuple_seq.
// nrmlzd_bound_tuple_seq:
//   {normalized-bound-tuple}+
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_STUTIL_BOUNDTUPLESEQ_TO_OBJSEQ(nrmlzd_bound_tuple_seq) \
  WG_PP_STUTIL_BOUNDTUPLESEQ_TO_OBJSEQ_IMPL(nrmlzd_bound_tuple_seq)

// Expands to a sequence of all the types in the order in which they declared
// in nrmlzd_bound_tuple_seq.
// nrmlzd_set_tuple_seq:
//   {normalized-set-tuple}+
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_STUTIL_SETTUPLESEQ_TO_TYPESEQ(nrmlzd_set_tuple_seq) \
  WG_PP_STUTIL_SETTUPLESEQ_TO_TYPESEQ_IMPL(nrmlzd_set_tuple_seq)

// Expands to a sequence of all the objects in the order in which they declared
// in nrmlzd_bound_tuple_seq.
// nrmlzd_set_tuple_seq:
//   {normalized-set-tuple}+
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_STUTIL_SETTUPLESEQ_TO_OBJSEQ(nrmlzd_set_tuple_seq) \
  WG_PP_STUTIL_SETTUPLESEQ_TO_OBJSEQ_IMPL(nrmlzd_set_tuple_seq)

// Expands to a sequence of all the value expressions in the order in which
// they declared in nrmlzd_bound_tuple_seq.
// nrmlzd_set_tuple_seq:
//   {normalized-set-tuple}+
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_STUTIL_SETTUPLESEQ_TO_VALUESEQ(nrmlzd_set_tuple_seq) \
  WG_PP_STUTIL_SETTUPLESEQ_TO_VALUESEQ_IMPL(nrmlzd_set_tuple_seq)

// bound_obj_seq:
//   The expansion of WG_PP_STUTIL_BOUNDTUPLESEQ_TO_OBJSEQ.
// Returns: { BOOST_PP_NIL | integer }
#define WG_PP_STUTIL_THISU_INDX(bound_obj_seq) \
  WG_PP_STUTIL_THISU_INDX_IMPL0(bound_obj_seq)

//------
//INPUT:
//------
//The symbol table created using WG_PP_SYMBOLTABLE_CREATE. This symbol table
//must have the following defined:
//  1) WG_PP_SYMBOLTABLE_INDX_TYPESEQ_<suffix>
//  2) WG_PP_SYMBOLTABLE_TYPESEQ_<suffix>
//where suffix is declared in specseq as defined in the TypeDeducer.hh
//
//-------
//OUTPUT:
//-------
//A symbol table where all occurrences of parsed-deduced-type are mapped to
//their typededucer counterparts.
//Note: the new definition of parsed-deduced-type:
//
//parsed-deduced-type := <typededucer_name>::<some_typedef_name>
#define WG_PP_STUTIL_USETYPEDEDUCER(symbtbl, typededucer_name, specseq) \
  WG_PP_STUTIL_USETYPEDEDUCER_IMPL(symbtbl, typededucer_name, specseq)

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

#define WG_PP_STUTIL_THISU_INDX_IMPL0(bound_obj_seq) \
  WG_PP_STUTIL_THISU_INDX_IMPL( \
    (BOOST_PP_NIL) \
    WG_PP_SEQ_FOR_EACH_I(WG_PP_STUTIL_THISU_MARK_INDX, ~, bound_obj_seq))

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
    WG_PP_TOKENS_STARTWITH_THISU(elem), \
    (indx))

//---------------------
//UseTypeDeducer Macros
//---------------------

#define WG_PP_STUTIL_USETYPEDEDUCER_WHILE_STATE_INIT( \
  symbtbl, typededucer_name, specseq) \
    (specseq, typededucer_name, symbtbl)
#define WG_PP_STUTIL_USETYPEDEDUCER_WHILE_STATE_ELEM(indx, state) \
  BOOST_PP_TUPLE_ELEM(3, indx, state)
#define WG_PP_STUTIL_USETYPEDEDUCER_WHILE_STATE_SPECSEQ(state) \
  WG_PP_STUTIL_USETYPEDEDUCER_WHILE_STATE_ELEM(0, state)
#define WG_PP_STUTIL_USETYPEDEDUCER_WHILE_STATE_TDNAME(state) \
  WG_PP_STUTIL_USETYPEDEDUCER_WHILE_STATE_ELEM(1, state)
#define WG_PP_STUTIL_USETYPEDEDUCER_WHILE_STATE_SYMBTBL(state) \
  WG_PP_STUTIL_USETYPEDEDUCER_WHILE_STATE_ELEM(2, state)

#define WG_PP_STUTIL_USETYPEDEDUCER_WHILE_PRED(d, state) \
  BOOST_PP_GREATER( \
    BOOST_PP_SEQ_SIZE(\
      WG_PP_STUTIL_USETYPEDEDUCER_WHILE_STATE_SPECSEQ(state)), \
    1)

#define WG_PP_STUTIL_USETYPEDEDUCER_WHILE_OP(d, state) \
  ( \
    BOOST_PP_SEQ_POP_FRONT( \
      WG_PP_STUTIL_USETYPEDEDUCER_WHILE_STATE_SPECSEQ(state)), \
    WG_PP_STUTIL_USETYPEDEDUCER_WHILE_STATE_TDNAME(state), \
    WG_PP_STUTIL_USETYPEDEDUCER_REPLACEDEDUCEDTUPLESEQ( \
      WG_PP_STUTIL_USETYPEDEDUCER_WHILE_STATE_SYMBTBL(state), \
      WG_PP_STUTIL_USETYPEDEDUCER_WHILE_STATE_TDNAME(state), \
      BOOST_PP_SEQ_HEAD( \
        WG_PP_STUTIL_USETYPEDEDUCER_WHILE_STATE_SPECSEQ(state)) ) \
  )

#define WG_PP_STUTIL_USETYPEDEDUCER_IMPL( \
  symbtbl, typededucer_name, specseq) \
    WG_PP_STUTIL_USETYPEDEDUCER_WHILE_STATE_SYMBTBL( \
      BOOST_PP_WHILE( \
        WG_PP_STUTIL_USETYPEDEDUCER_WHILE_PRED, \
        WG_PP_STUTIL_USETYPEDEDUCER_WHILE_OP, \
        WG_PP_STUTIL_USETYPEDEDUCER_WHILE_STATE_INIT( \
          symbtbl, \
          typededucer_name, \
          specseq (BOOST_PP_NIL) )))

//TODO: WORKAROUND
#ifndef BOOST_PP_TUPLE_REM_0
#define BOOST_PP_TUPLE_REM_0() // nothing
#endif

#define WG_PP_STUTIL_USETYPEDEDUCER_REPLACEDEDUCEDTUPLESEQ( \
  symbtbl, typededucer_name, spec) \
    BOOST_PP_ARRAY_REPLACE( \
      symbtbl, \
      BOOST_PP_CAT( \
        WG_PP_SYMBOLTABLE_INDX_TYPESEQ_, \
        WG_PP_TYPEDEDUCER_SPEC_SUFFIX(spec)), \
      WG_PP_STUTIL_USETYPEDEDUCER_REPLACEMENTDEDUCEDTUPLESEQ( \
        symbtbl, \
        typededucer_name, \
        spec) )

#define WG_PP_STUTIL_USETYPEDEDUCER_REPLACEMENTDEDUCEDTUPLESEQ( \
  symbtbl, typededucer_name, spec) \
    WG_PP_SEQ_FOR_EACH_I( \
      WG_PP_STUTIL_USETYPEDEDUCER_REPLACEBOUNDTUPLEENTRY, \
      (spec) (typededucer_name), \
      BOOST_PP_CAT( \
        WG_PP_SYMBOLTABLE_TYPESEQ_, \
        WG_PP_TYPEDEDUCER_SPEC_SUFFIX(spec)) (symbtbl) )

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_STUTIL_USETYPEDEDUCER_REPLACEBOUNDTUPLEENTRY( \
  r, spec_typededucername, indx, entry) \
    BOOST_PP_LPAREN() \
      BOOST_PP_IIF( \
        WG_PP_TOKENS_START_WITH_WG_PP_DEDUCEDTYPE(entry), \
        WG_PP_STUTIL_USETYPEDEDUCER_REPLACEBOOSTYPEOF( \
          spec_typededucername, indx), \
        entry) \
    BOOST_PP_RPAREN()

#define WG_PP_STUTIL_USETYPEDEDUCER_REPLACEBOOSTYPEOF( \
  spec_typededucername, indx) \
    WG_PP_STUTIL_USETYPEDEDUCER_REPLACEBOOSTYPEOF2( \
      BOOST_PP_SEQ_ELEM(0, spec_typededucername), \
      BOOST_PP_SEQ_ELEM(1, spec_typededucername), \
      indx)

#define WG_PP_STUTIL_USETYPEDEDUCER_REPLACEBOOSTYPEOF2( \
  spec, typededucername, indx) \
    typededucername::WG_PP_TYPEDEDUCER_TYPENAME(spec, indx)

#endif /* WG_PP_SYMBOLTABLEUTIL_HH_ */
