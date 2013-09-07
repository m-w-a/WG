#ifndef WG_PP_SYMBOLTABLEUTIL_HH_
#define WG_PP_SYMBOLTABLEUTIL_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP.hh>
#include <WG/Local/Detail/PP/Seq.hh>
#include <WG/Local/Detail/PP/Keywords.hh>
#include <WG/Local/Detail/PP/BackEnd/TypeDeducer.hh>

//----------------------------------------------------------------------------//
// This is a "friend" of SymbolTable.
// Therefore it is ok if it assumes SymbolTable is implemented as a pp array.
//----------------------------------------------------------------------------//

//################
//Interface Impls.
//################

// Expands to <symbtbl-moduleid>_<objmacro>
// symbtbl:
//   The first element must be the moduleid.
#define WG_PP_STUTIL_ACCESS(objmacro, symbtbl) \
  WG_PP_UCAT(BOOST_PP_ARRAY_ELEM(0, symbtbl), objmacro)

// Expands to <symbtbl-moduleid>_<objmacropt1>_<objmacropt2>
// symbtbl:
//   The first element must be the moduleid.
#define WG_PP_STUTIL_ACCESS2(objmacropt1, objmacropt2, symbtbl) \
  WG_PP_UCAT3(BOOST_PP_ARRAY_ELEM(0, symbtbl), objmacropt1, objmacropt2)

// Expands to <symbtbl-moduleid>_<function>(symbtbl)
// symbtbl:
//   The first element must be the moduleid.
#define WG_PP_STUTIL_CALL(function, symbtbl) \
  WG_PP_UCAT(BOOST_PP_ARRAY_ELEM(0, symbtbl), function) (symbtbl)

// Expands to <symbtbl-moduleid>_<functionpt1>_<functionpt2>(symbtbl)
// symbtbl:
//   The first element must be the moduleid.
#define WG_PP_STUTIL_CALL2(functionpt1, functionpt2, symbtbl) \
  WG_PP_UCAT3(BOOST_PP_ARRAY_ELEM(0, symbtbl), functionpt1, functionpt2) (symbtbl)

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
//The symbol table created using <symbol-moduleid>_SYMBOLTABLE_CREATE.
//This symbol table must have the following defined:
//  1) WG_PP_STUTIL_CALL(ISTPL, symbtbl)
//  2) WG_PP_STUTIL_ACCESS2(INDX_TYPESEQ, <suffix>, symbtbl)
//  3) WG_PP_STUTIL_ACCESS2(TYPESEQ, <suffix>, symbtbl)
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

// WORKAROUND for BOOST_PP_ARRAY_REPLACE bug.
#ifndef BOOST_PP_TUPLE_REM_0
#define BOOST_PP_TUPLE_REM_0() // nothing
#endif

#define WG_PP_STUTIL_USETYPEDEDUCER_REPLACEDEDUCEDTUPLESEQ( \
  symbtbl, typededucer_name, spec) \
    BOOST_PP_ARRAY_REPLACE( \
      symbtbl, \
      WG_PP_STUTIL_ACCESS2( \
        INDX_TYPESEQ, WG_PP_TYPEDEDUCER_SPEC_SUFFIX(spec), symbtbl), \
      WG_PP_STUTIL_USETYPEDEDUCER_REPLACEMENTDEDUCEDTUPLESEQ( \
        symbtbl, \
        typededucer_name, \
        spec) )

#define WG_PP_STUTIL_USETYPEDEDUCER_REPLACEMENTDEDUCEDTUPLESEQ( \
  symbtbl, typededucer_name, spec) \
    WG_PP_SEQ_FOR_EACH_I( \
      WG_PP_STUTIL_USETYPEDEDUCER_REPLACEBOUNDTUPLEENTRY, \
      (spec) (typededucer_name) (WG_PP_STUTIL_CALL(ISTPL,symbtbl)), \
      WG_PP_STUTIL_CALL2( \
		TYPESEQ, WG_PP_TYPEDEDUCER_SPEC_SUFFIX(spec), symbtbl) )

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_STUTIL_USETYPEDEDUCER_REPLACEBOUNDTUPLEENTRY( \
  r, spec_typededucername_istpl, indx, entry) \
    BOOST_PP_LPAREN() \
      BOOST_PP_IIF( \
        WG_PP_TOKENS_START_WITH_WG_PP_DEDUCEDTYPE(entry), \
        WG_PP_STUTIL_USETYPEDEDUCER_REPLACEBOOSTYPEOF( \
          spec_typededucername_istpl, indx), \
        entry) \
    BOOST_PP_RPAREN()

#define WG_PP_STUTIL_USETYPEDEDUCER_REPLACEBOOSTYPEOF( \
  spec_typededucername_istpl, indx) \
    WG_PP_STUTIL_USETYPEDEDUCER_REPLACEBOOSTYPEOF2( \
      BOOST_PP_SEQ_ELEM(0, spec_typededucername_istpl), \
      BOOST_PP_SEQ_ELEM(1, spec_typededucername_istpl), \
      BOOST_PP_SEQ_ELEM(2, spec_typededucername_istpl), \
      indx)

#define WG_PP_STUTIL_USETYPEDEDUCER_REPLACEBOOSTYPEOF2( \
  spec, typededucername, istpl, indx) \
    WG_PP_ADDTYPENAME(istpl) \
      typededucername::WG_PP_TYPEDEDUCER_TYPENAME(spec, indx)

#endif /* WG_PP_SYMBOLTABLEUTIL_HH_ */
