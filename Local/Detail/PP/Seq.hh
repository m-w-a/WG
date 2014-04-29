#ifndef WG_PP_SEQ_HH_
#define WG_PP_SEQ_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/PP.hh>

//###########
//Public APIs
//###########

// Nil sequences are defined to be BOOST_PP_NIL.

// If it can be determined that seq is not a WG-seq then will expand to
// WG_PP_ERROR_INVALID_ARGUMENT, else it's UB.
#define WG_PP_SEQ_ISNIL(seq) \
  WG_PP_SEQ_ISNIL_IMPL1(seq)

// seq_count as param instead of seq because want to encourage caching former.
#define WG_PP_SEQ_IS_INDEX_LAST(seq_count, indx) \
  BOOST_PP_EQUAL(seq_count, BOOST_PP_INC(indx))

// Maps to BOOST_PP_NIL if seq is nil.
#define WG_PP_SEQ_CAT(seq) WG_PP_SEQ_CAT_IMPL(seq)

// Maps to BOOST_PP_NIL if indx or seq is nil
#define WG_PP_SEQ_ELEM(indx, seq) \
  WG_PP_SEQ_ELEM_IMPL(indx, seq)

// Maps to BOOST_PP_NIL if seq is nil.
// Lists each element of the seq as they appeared in the seq.
#define WG_PP_SEQ_FLATTEN(seq) \
  WG_PP_SEQ_FLATTEN_IMPL(seq)

// Handles empty sequences.
// NOTE: maps empty sequences to NOTHING!
//   Rationale:
//     SEQ_ENUM introduces commas into the token seq, therefore it's impossible
//     to use with non-variadic macros.
#define WG_PP_SEQ_ENUM(seq) WG_PP_SEQ_ENUM_IMPL(seq)

// Maps to BOOST_PP_NIL if seq is nil
#define WG_PP_SEQ_FOR_EACH(macro, data, seq) \
  WG_PP_SEQ_FOR_EACH_IMPL(macro, data, seq)

// Maps to nothing if seq is nil.
#define WG_PP_SEQ_NOTHING_FOR_EACH_I(macro, data, seq) \
  WG_PP_SEQ_NOTHING_FOR_EACH_I_IMPL(macro, data, seq)

// Maps to BOOST_PP_NIL if seq is nil
#define WG_PP_SEQ_FOR_EACH_I(macro, data, seq) \
  WG_PP_SEQ_FOR_EACH_I_IMPL(macro, data, seq)

//Maps to BOOST_PP_NIL iff all params are nil sequences.
#define WG_PP_SEQ_JOIN_ARG2(a, b) \
  WG_PP_SEQ_JOIN_IMPL(a,b)
#define WG_PP_SEQ_JOIN_ARG3(a, b, c) \
  WG_PP_SEQ_JOIN_ARG2(a, WG_PP_SEQ_JOIN_ARG2(b,c))
#define WG_PP_SEQ_JOIN_ARG4(a, b, c, d) \
  WG_PP_SEQ_JOIN_ARG3(a, b, WG_PP_SEQ_JOIN_ARG2(c,d))
#define WG_PP_SEQ_JOIN_ARG5(a, b, c, d, e) \
  WG_PP_SEQ_JOIN_ARG4(a, b, c, WG_PP_SEQ_JOIN_ARG2(d,e))

// Maps to BOOST_PP_NIL if seq is nil.
// Maps to seq if indx is BOOST_PP_NIL.
#define WG_PP_SEQ_REPLACE(seq, indx, elem) \
  WG_PP_SEQ_REPLACE_IMPL(seq, indx, elem)

// Nil sequences have zero size.
#define WG_PP_SEQ_SIZE(seq) \
  WG_PP_SEQ_SIZE_IMPL(seq)

// Maps to BOOST_PP_NIL if seq is nil.
// transform: a 1-arg macro to apply to the elements of seq
// Expands to: { BOOST_PP_NIL | { ( transform(elem) ) }+ }
#define WG_PP_SEQ_APPLY_TRANSFORM(transform, seq) \
  WG_PP_SEQ_APPLY_TRANSFORM_IMPL(transform, seq)

//###########
//Impl Macros
//###########

#define WG_PP_SEQ_ISNIL_IMPL1(seq) \
  BOOST_PP_IIF( \
    WG_PP_ISNEXTTOKEN_A_TUPLE(1, seq), \
    WG_PP_MAP_TO_0_ARG1, \
    WG_PP_SEQ_ISNIL_IMPL2) (seq)

#define WG_PP_SEQ_ISNIL_IMPL2(seq) \
  BOOST_PP_IIF( \
    WG_PP_MATCHES_BOOST_PP_NIL(seq), \
    1, \
    WG_PP_ERROR_INVALID_ARGUMENT)

#define WG_PP_SEQ_CAT_IMPL_0(seq) BOOST_PP_NIL
#define WG_PP_SEQ_CAT_IMPL_1(seq) BOOST_PP_SEQ_CAT(seq)
#define WG_PP_SEQ_CAT_IMPL(seq) \
  BOOST_PP_CAT( \
    WG_PP_SEQ_CAT_IMPL_, \
    BOOST_PP_NOT(WG_PP_SEQ_ISNIL(seq))) (seq)

#define WG_PP_SEQ_FOR_EACH_IMPL_0(macro, data, seq) BOOST_PP_NIL
#define WG_PP_SEQ_FOR_EACH_IMPL_1(macro, data, seq) \
  BOOST_PP_SEQ_FOR_EACH(macro, data, seq)
#define WG_PP_SEQ_FOR_EACH_IMPL(macro, data, seq) \
  BOOST_PP_CAT( \
    WG_PP_SEQ_FOR_EACH_IMPL_, \
    WG_PP_ISNEXTTOKEN_A_TUPLE(1, seq)) (macro, data, seq)

#define WG_PP_SEQ_NOTHING_FOR_EACH_I_IMPL_0(macro, data, seq)
#define WG_PP_SEQ_NOTHING_FOR_EACH_I_IMPL_1(macro, data, seq) \
  BOOST_PP_SEQ_FOR_EACH_I(macro, data, seq)
#define WG_PP_SEQ_NOTHING_FOR_EACH_I_IMPL(macro, data, seq) \
  BOOST_PP_CAT( \
    WG_PP_SEQ_NOTHING_FOR_EACH_I_IMPL_, \
    WG_PP_ISNEXTTOKEN_A_TUPLE(1, seq)) (macro, data, seq)

#define WG_PP_SEQ_FOR_EACH_I_IMPL_0(macro, data, seq) BOOST_PP_NIL
#define WG_PP_SEQ_FOR_EACH_I_IMPL_1(macro, data, seq) \
  BOOST_PP_SEQ_FOR_EACH_I(macro, data, seq)
#define WG_PP_SEQ_FOR_EACH_I_IMPL(macro, data, seq) \
  BOOST_PP_CAT( \
    WG_PP_SEQ_FOR_EACH_I_IMPL_, \
    WG_PP_ISNEXTTOKEN_A_TUPLE(1, seq)) (macro, data, seq)

#define WG_PP_SEQ_APPLY_TRANSFORM_IMPL(transform, seq) \
  WG_PP_SEQ_FOR_EACH( \
    WG_PP_SEQ_APPLY_TRANSFORM_IMPL_ENTRY, \
    transform, \
    seq)
#define WG_PP_SEQ_APPLY_TRANSFORM_IMPL_ENTRY(r, transform, elem) \
  ( transform(elem) )

#define WG_PP_SEQ_SIZE_IMPL_0(seq) 0
#define WG_PP_SEQ_SIZE_IMPL_1(seq) BOOST_PP_SEQ_SIZE(seq)
#define WG_PP_SEQ_SIZE_IMPL(seq) \
  BOOST_PP_CAT( \
    WG_PP_SEQ_SIZE_IMPL_, \
    WG_PP_ISNEXTTOKEN_A_TUPLE(1, seq)) (seq)

#define WG_PP_SEQ_ENUM_IMPL_0(seq)
#define WG_PP_SEQ_ENUM_IMPL_1(seq) BOOST_PP_SEQ_ENUM(seq)
#define WG_PP_SEQ_ENUM_IMPL(seq) \
  BOOST_PP_CAT( \
    WG_PP_SEQ_ENUM_IMPL_, \
    WG_PP_ISNEXTTOKEN_A_TUPLE(1, seq)) (seq)

#define WG_PP_SEQ_REPLACE_IMPL_00(seq, indx, elem) BOOST_PP_NIL
#define WG_PP_SEQ_REPLACE_IMPL_01(seq, indx, elem) BOOST_PP_NIL
#define WG_PP_SEQ_REPLACE_IMPL_10(seq, indx, elem) seq
#define WG_PP_SEQ_REPLACE_IMPL_11(seq, indx, elem) \
  BOOST_PP_SEQ_REPLACE(seq, indx, elem)
#define WG_PP_SEQ_REPLACE_IMPL(seq, indx, elem) \
  BOOST_PP_CAT( \
    BOOST_PP_CAT( \
      WG_PP_SEQ_REPLACE_IMPL_, \
      WG_PP_ISNEXTTOKEN_A_TUPLE(1, seq)), \
    BOOST_PP_NOT(WG_PP_STARTSWITH_BOOST_PP_NIL(indx))) \
  (seq, indx, elem)

#define WG_PP_SEQ_FLATTEN_IMPL(seq) \
  BOOST_PP_CAT( \
    BOOST_PP_EXPAND(WG_PP_SEQ_FLATTEN_FUNC1 seq), \
    _ERASED)
#define WG_PP_SEQ_FLATTEN_FUNC1(elem) elem WG_PP_SEQ_FLATTEN_FUNC2
#define WG_PP_SEQ_FLATTEN_FUNC2(elem) elem WG_PP_SEQ_FLATTEN_FUNC1
#define WG_PP_SEQ_FLATTEN_FUNC1_ERASED
#define WG_PP_SEQ_FLATTEN_FUNC2_ERASED

#define WG_PP_SEQ_ELEM_IMPL_00(indx, seq) BOOST_PP_NIL
#define WG_PP_SEQ_ELEM_IMPL_01(indx, seq) BOOST_PP_NIL
#define WG_PP_SEQ_ELEM_IMPL_10(indx, seq) BOOST_PP_NIL
#define WG_PP_SEQ_ELEM_IMPL_11(indx, seq) BOOST_PP_SEQ_ELEM(indx, seq)
#define WG_PP_SEQ_ELEM_IMPL(indx, seq) \
  BOOST_PP_CAT( \
    BOOST_PP_CAT( \
      WG_PP_SEQ_ELEM_IMPL_, \
      BOOST_PP_NOT(WG_PP_STARTSWITH_BOOST_PP_NIL(indx))), \
    WG_PP_ISNEXTTOKEN_A_TUPLE(1, seq)) \
  (indx, seq)

#define WG_PP_SEQ_JOIN_IMPL_00(x, y) BOOST_PP_NIL
#define WG_PP_SEQ_JOIN_IMPL_01(x, y) y
#define WG_PP_SEQ_JOIN_IMPL_10(x, y) x
#define WG_PP_SEQ_JOIN_IMPL_11(x, y) x y
#define WG_PP_SEQ_JOIN_IMPL(x, y) \
  BOOST_PP_CAT( \
    WG_PP_SEQ_JOIN_IMPL_, \
    BOOST_PP_CAT( \
      WG_PP_ISNEXTTOKEN_A_TUPLE(1, x), \
      WG_PP_ISNEXTTOKEN_A_TUPLE(1, y))) (x, y)

#endif /* WG_PP_SEQ_HH_ */
