#ifndef WG_PP_SYMBOLTABLE_HH_
#define WG_PP_SYMBOLTABLE_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP.hh>
#include <WG/Local/Detail/Seq.hh>
#include <WG/Local/Detail/Keywords.hh>
#include <WG/Local/Detail/BackEnd/TypeDeducer.hh>

//###########
//Public APIs
//###########

//------
//INPUT:
//------
//assignto_nrmlzd_tuple: { BOOST_PP_NIL | normalized-bound-tuple }
//return_nrmlzd_type: { void | some-token }
//parambind_nrmlzd_tupleseq: { BOOST_PP_NIL | {normalized-bound-tuple}+ }
//paramset_nrmlzd_tupleseq: { BOOST_PP_NIL | {normalized-set-tuple}+ }
//
//normalized-bound-tuple := (explicit-or-deduced-type)(var-name)
//normalized-set-tuple := (explicit-type)(var-name)(value-expr)
//explicit-or-deduced-type := explicit-type | deduced-type
//explicit-type := local(some-token) | localref(some-tokens) | some-token
//deduced-type :=
//  WG_PP_DEDUCEDTYPE
//  { BT | add_const<BT> | add_ref<BT> | add_ref< add_const<BT> > }
//BT := BOOST_TYPEOF(some-token)
//
//-------
//OUTPUT:
//-------
//A SymbolTable whose values are accessible using the below macros.
#define WG_PP_SYMBOLTABLE_CREATE( \
  assignto_nrmlzd_tuple, \
  return_type, \
  parambind_nrmlzd_tupleseq, \
  paramset_nrmlzd_tupleseq) \
    WG_PP_ST_CREATE_IMPL1( \
      assignto_nrmlzd_tuple, \
      return_type, \
      parambind_nrmlzd_tupleseq, \
      paramset_nrmlzd_tupleseq)

//------
//INPUT:
//------
//The symbol table created using WG_PP_SYMBOLTABLE_CREATE.
//-------
//OUTPUT:
//-------
//Maps all occurrences of deduced-type to their typededucer counterparts.
//
//A SymbolTable whose values are accessible using the below macros.
//Note: the new definition of deduced-type:
//
//deduced-type := <typededucer_name>::<some_typedef_name>
#define WG_PP_SYMBOLTABLE_USETYPEDEDUCER(symbtbl, typededucer_name) \
  WG_PP_SYMBOLTABLE_USETYPEDEDUCER_IMPL(symbtbl, typededucer_name)

//Returns: { BOOST_PP_NIL | (explicit-or-deduced-type) }
#define WG_PP_SYMBOLTABLE_TYPESEQ_ASSIGNEE(symbtbl) \
  WG_PP_SYMBOLTABLE_GET(symbtbl, TYPESEQ_ASSIGNEE)

//Returns: { BOOST_PP_NIL | (var-name) }
#define WG_PP_SYMBOLTABLE_OBJSEQ_ASSIGNEE(symbtbl) \
  WG_PP_SYMBOLTABLE_GET(symbtbl, OBJSEQ_ASSIGNEE)

//Returns: { 0 | 1 }
#define WG_PP_SYMBOLTABLE_EXISTS_ASSIGNEE(symbtbl) \
  WG_PP_SYMBOLTABLE_GET(symbtbl, EXISTS_ASSIGNEE)

//Returns: { BOOST_PP_NIL | return-type  }
#define WG_PP_SYMBOLTABLE_RETTYPE(symbtbl) \
  WG_PP_SYMBOLTABLE_GET(symbtbl, RETTYPE)

//Returns: { BOOST_PP_NIL | {(explicit-or-deduced-type)}+ }
#define WG_PP_SYMBOLTABLE_TYPESEQ_BOUNDPARAM(symbtbl) \
  WG_PP_SYMBOLTABLE_GET(symbtbl, TYPESEQ_BOUNDPARAM)

//Returns: { BOOST_PP_NIL | {(var-name)}+ }
#define WG_PP_SYMBOLTABLE_OBJSEQ_BOUNDPARAM(symbtbl) \
  WG_PP_SYMBOLTABLE_GET(symbtbl, OBJSEQ_BOUNDPARAM)

//Returns: { integer }
#define WG_PP_SYMBOLTABLE_XXX_SIZE_BOUNDPARAM(symbtbl) \
  WG_PP_SYMBOLTABLE_GET(symbtbl, XXX_SIZE_BOUNDPARAM)

//Returns: { BOOST_PP_NIL | integer }
#define WG_PP_SYMBOLTABLE_OBJSEQ_BOUNDPARAM_THISU_MARKER(symbtbl) \
  WG_PP_SYMBOLTABLE_GET(symbtbl, OBJSEQ_BOUNDPARAM_THISU_MARKER)

//Returns: { BOOST_PP_NIL | {(explicit-type)}+ }
#define WG_PP_SYMBOLTABLE_TYPESEQ_SETPARAM(symbtbl) \
  WG_PP_SYMBOLTABLE_GET(symbtbl, TYPESEQ_SETPARAM)

//Returns: { BOOST_PP_NIL | {(var-name)}+ }
#define WG_PP_SYMBOLTABLE_OBJSEQ_SETPARAM(symbtbl) \
  WG_PP_SYMBOLTABLE_GET(symbtbl, OBJSEQ_SETPARAM)

//Returns: { BOOST_PP_NIL | {(value-expr)}+ }
#define WG_PP_SYMBOLTABLE_VALUESEQ_SETPARAM(symbtbl) \
  WG_PP_SYMBOLTABLE_GET(symbtbl, VALUESEQ_SETPARAM)

//Returns: { BOOST_PP_NIL | integer }
#define WG_PP_SYMBOLTABLE_XXX_SIZE_SETPARAM(symbtbl) \
  WG_PP_SYMBOLTABLE_GET(symbtbl, XXX_SIZE_SETPARAM)

//Returns: { BOOST_PP_NIL | integer }
#define WG_PP_SYMBOLTABLE_TOTALXXX_SIZE(symbtbl) \
  WG_PP_SYMBOLTABLE_GET(symbtbl, TOTALXXX_SIZE)

//###########
//Impl Macros
//###########

#define WG_PP_SYMBOLTABLE_INDX_TYPESEQ_ASSIGNEE 0
#define WG_PP_SYMBOLTABLE_INDX_OBJSEQ_ASSIGNEE 1
#define WG_PP_SYMBOLTABLE_INDX_EXISTS_ASSIGNEE 2
#define WG_PP_SYMBOLTABLE_INDX_RETTYPE 3
#define WG_PP_SYMBOLTABLE_INDX_TYPESEQ_BOUNDPARAM 4
#define WG_PP_SYMBOLTABLE_INDX_OBJSEQ_BOUNDPARAM 5
#define WG_PP_SYMBOLTABLE_INDX_XXX_SIZE_BOUNDPARAM 6
#define WG_PP_SYMBOLTABLE_INDX_OBJSEQ_BOUNDPARAM_THISU_MARKER 7
#define WG_PP_SYMBOLTABLE_INDX_TYPESEQ_SETPARAM 8
#define WG_PP_SYMBOLTABLE_INDX_OBJSEQ_SETPARAM 9
#define WG_PP_SYMBOLTABLE_INDX_VALUESEQ_SETPARAM 10
#define WG_PP_SYMBOLTABLE_INDX_XXX_SIZE_SETPARAM 11
#define WG_PP_SYMBOLTABLE_INDX_TOTALXXX_SIZE 12

// suffix: must match one of the following: WG_PP_SYMBOLTABLE_INDX_<suffix>
#define WG_PP_SYMBOLTABLE_GET(symbtbl, suffix) \
  BOOST_PP_ARRAY_ELEM( \
    BOOST_PP_CAT(WG_PP_SYMBOLTABLE_INDX_, suffix), \
    symbtbl)

//---------------
//Creation Macros
//---------------

#define WG_PP_ST_CREATE_IMPL1( \
  assignto_nrmlzd_tuple, \
  return_type, \
  parambind_nrmlzd_tupleseq, \
  paramset_nrmlzd_tupleseq) \
    WG_PP_ST_CREATE_IMPL2( \
      WG_PP_ST_NBOUNDTUPLESEQ_TO_TYPESEQ(assignto_nrmlzd_tuple), \
      WG_PP_ST_NBOUNDTUPLESEQ_TO_OBJSEQ(assignto_nrmlzd_tuple), \
      return_type, \
      WG_PP_ST_NBOUNDTUPLESEQ_TO_TYPESEQ(parambind_nrmlzd_tupleseq), \
      WG_PP_ST_NBOUNDTUPLESEQ_TO_OBJSEQ(parambind_nrmlzd_tupleseq), \
      WG_PP_ST_NSETTUPLESEQ_TO_TYPESEQ(paramset_nrmlzd_tupleseq), \
      WG_PP_ST_NSETTUPLESEQ_TO_OBJSEQ(paramset_nrmlzd_tupleseq), \
      WG_PP_ST_NSETTUPLESEQ_TO_VALUESEQ(paramset_nrmlzd_tupleseq))

#define WG_PP_ST_CREATE_IMPL2( \
  assignto_type_seq, assignto_ob_seq, \
  return_type, \
  parambind_type_seq, parambind_obj_seq, \
  paramset_type_seq, paramset_obj_seq, paramset_value_seq) \
    WG_PP_ST_CREATE_IMPL3( \
      (12, \
        (assignto_type_seq, \
        assignto_ob_seq, \
        WG_PP_SEQ_SIZE(assignto_type_seq), \
        return_type, \
        parambind_type_seq, \
        parambind_obj_seq, \
        WG_PP_SEQ_SIZE(parambind_type_seq), \
        WG_PP_ST_THISU_INDX(parambind_obj_seq), \
        paramset_type_seq, \
        paramset_obj_seq, \
        paramset_value_seq, \
        WG_PP_SEQ_SIZE(paramset_type_seq))) \
    )

#define WG_PP_ST_CREATE_IMPL3(wiparray) \
  BOOST_PP_ARRAY_PUSH_BACK( \
    wiparray, \
    BOOST_PP_ADD( \
      BOOST_PP_ADD( \
        WG_PP_SYMBOLTABLE_XXX_SIZE_BOUNDPARAM(wiparray), \
        WG_PP_SYMBOLTABLE_XXX_SIZE_SETPARAM(wiparray)), \
        WG_PP_SYMBOLTABLE_EXISTS_ASSIGNEE(wiparray)))

//------------------------
//Partitioning Operations.
//------------------------

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_ST_SEQUENCE_IF_INDEX(r, CONDITION, indx, elem) \
  BOOST_PP_EXPR_IF( \
    CONDITION(indx), \
    BOOST_PP_LPAREN() elem BOOST_PP_RPAREN())
    
#define WG_PP_ST_NBOUNDTUPLESEQ_TO_TYPESEQ(nrmlzd_bound_tuple_seq) \
  WG_PP_SEQ_FOR_EACH_I( \
    WG_PP_ST_SEQUENCE_IF_INDEX, \
    WG_PP_IS_EVEN, \
    nrmlzd_bound_tuple_seq)
    
#define WG_PP_ST_NBOUNDTUPLESEQ_TO_OBJSEQ(nrmlzd_bound_tuple_seq) \
  WG_PP_SEQ_FOR_EACH_I( \
    WG_PP_ST_SEQUENCE_IF_INDEX, \
    WG_PP_IS_ODD, \
    nrmlzd_bound_tuple_seq)

#define WG_PP_ST_NSETTUPLESEQ_TO_TYPESEQ(nrmlzd_set_tuple_seq) \
  WG_PP_SEQ_FOR_EACH_I( \
    WG_PP_ST_SEQUENCE_IF_INDEX, \
    WG_PP_IS_MOD3_R0, \
    nrmlzd_set_tuple_seq)
      
#define WG_PP_ST_NSETTUPLESEQ_TO_OBJSEQ(nrmlzd_set_tuple_seq) \
  WG_PP_SEQ_FOR_EACH_I( \
    WG_PP_ST_SEQUENCE_IF_INDEX, \
    WG_PP_IS_MOD3_R1, \
    nrmlzd_set_tuple_seq)

#define WG_PP_ST_NSETTUPLESEQ_TO_VALUESEQ(nrmlzd_set_tuple_seq) \
  WG_PP_SEQ_FOR_EACH_I( \
    WG_PP_ST_SEQUENCE_IF_INDEX, \
    WG_PP_IS_MOD3_R2, \
    nrmlzd_set_tuple_seq)

//----------------------
//Calculate this_ index.
//----------------------

//Returns: { BOOST_PP_NIL | integer }
#define WG_PP_ST_THISU_INDX(bound_obj_seq) \
  WG_PP_ST_THISU_INDX_IMPL( \
    (BOOST_PP_NIL) \
    WG_PP_SEQ_FOR_EACH_I(WG_PP_ST_THISU_MARK_INDX, ~, bound_obj_seq))

#define WG_PP_ST_THISU_INDX_IMPL_0 BOOST_PP_NIL
#define WG_PP_ST_THISU_INDX_IMPL_1(indx) indx
#define WG_PP_ST_THISU_INDX_IMPL(seq) \
  BOOST_PP_CAT( \
    WG_PP_ST_THISU_INDX_IMPL_, \
    WG_PP_ISNEXTTOKEN_A_TUPLE( \
      1, BOOST_PP_TUPLE_EAT(1)seq BOOST_PP_NIL)) BOOST_PP_TUPLE_EAT(1)seq

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_ST_THISU_MARK_INDX(r, data, indx, elem) \
  BOOST_PP_EXPR_IIF( \
    WG_PP_TOKENS_STARTWITH_THISU(elem), \
    (indx))

//---------------------
//UseTypeDeducer Macros
//---------------------

#define WG_PP_SYMBOLTABLE_USETYPEDEDUCER_IMPL(symbtbl, typededucer_name) \
  WG_PP_SYMBOLTABLE_USETYPEDEDUCER_IMPL2( \
    WG_PP_ST_USETYPEDEDUCER_REPLACEBOUNDTUPLESEQ( \
      symbtbl, typededucer_name, ASSIGNEE), \
    typededucer_name)

#define WG_PP_SYMBOLTABLE_USETYPEDEDUCER_IMPL2(symbtbl, typededucer_name) \
  WG_PP_SYMBOLTABLE_USETYPEDEDUCER_IMPL3( \
    WG_PP_ST_USETYPEDEDUCER_REPLACEBOUNDTUPLESEQ( \
      symbtbl, typededucer_name, BOUNDPARAM), \
    typededucer_name)

// TODO: BOUNDMEM
#define WG_PP_SYMBOLTABLE_USETYPEDEDUCER_IMPL3(symbtbl, typededucer_name) \
  symbtbl

//TODO: WORKAROUND
#ifndef BOOST_PP_TUPLE_REM_0
#define BOOST_PP_TUPLE_REM_0() // nothing
#endif
// suffix: {ASSIGNEE, BOUNDPARAM, BOUNDMEM}
#define WG_PP_ST_USETYPEDEDUCER_REPLACEBOUNDTUPLESEQ( \
  symbtbl, typededucer_name, suffix) \
    BOOST_PP_ARRAY_REPLACE( \
      symbtbl, \
      BOOST_PP_CAT(WG_PP_SYMBOLTABLE_INDX_TYPESEQ_, suffix), \
      WG_PP_ST_USETYPEDEDUCER_REPLACEMENTBOUNDTUPLESEQ( \
        symbtbl, typededucer_name, suffix) )

#define WG_PP_ST_USETYPEDEDUCER_REPLACEMENTBOUNDTUPLESEQ( \
  symbtbl, typededucer_name, suffix) \
    WG_PP_SEQ_FOR_EACH_I( \
      WG_PP_ST_USETYPEDEDUCER_REPLACEBOUNDTUPLEENTRY, \
      (BOOST_PP_CAT(WG_PP_TYPEDEDUCER_TYPENAME_, suffix)) (typededucer_name), \
      BOOST_PP_CAT(WG_PP_SYMBOLTABLE_TYPESEQ_, suffix) (symbtbl) )

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_ST_USETYPEDEDUCER_REPLACEBOUNDTUPLEENTRY( \
  r, boundtypenamer_typededucername, indx, entry) \
    BOOST_PP_LPAREN() \
      BOOST_PP_IIF( \
        WG_PP_TOKENS_START_WITH_WG_PP_DEDUCEDTYPE(entry), \
        WG_PP_ST_USETYPEDEDUCER_REPLACEBOOSTYPEOF( \
          boundtypenamer_typededucername, indx), \
        entry) \
    BOOST_PP_RPAREN()

#define WG_PP_ST_USETYPEDEDUCER_REPLACEBOOSTYPEOF( \
  boundtypenamer_typededucername, indx) \
    WG_PP_ST_USETYPEDEDUCER_REPLACEBOOSTYPEOF2( \
      BOOST_PP_SEQ_ELEM(0, boundtypenamer_typededucername), \
      BOOST_PP_SEQ_ELEM(1, boundtypenamer_typededucername), \
      indx)

#define WG_PP_ST_USETYPEDEDUCER_REPLACEBOOSTYPEOF2( \
  boundtypenamer, typededucername, indx) \
    typededucername::boundtypenamer(indx)


#endif //WG_PP_SYMBOLTABLE_HH_
