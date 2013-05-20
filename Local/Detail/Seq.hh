#ifndef WG_PP_SEQ_HH_
#define WG_PP_SEQ_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP.hh>

//###########
//Public APIs
//###########

// Nil sequences are defined to be BOOST_PP_NIL.
#define WG_PP_SEQ_IFNIL_THENCLEAR(seq) \
  WG_PP_SEQ_IFNIL_THENCLEAR_IMPL(seq)

#define WG_PP_SEQ_IS_COUNT_EVEN(seq) \
  BOOST_PP_NOT(BOOST_PP_MOD(BOOST_PP_SEQ_SIZE(seq), 2))

#define WG_PP_SEQ_IS_COUNT_ODD(seq) \
  BOOST_PP_NOT(WG_PP_SEQ_IS_COUNT_EVEN(seq))

#define WG_PP_SEQ_IS_INDEX_LAST(seq_count, indx) \
  BOOST_PP_EQUAL(seq_count, BOOST_PP_INC(indx))

#define WG_PP_SEQ_SIZE(seq) \
  WG_PP_SEQ_SIZE_IMPL(seq)

// Handles empty sequences.
// Handles empty token as indx.
#define WG_PP_SEQ_ELEM(indx, seq) \
  WG_PP_SEQ_ELEM_IMPL(indx, seq)
  
#define WG_PP_SEQ_CAT(x, y) \
  WG_PP_SEQ_CAT_IMPL(x, y)
  
#define WG_PP_SEQ_FOR_EACH_I(macro, data, seq) \
  WG_PP_SEQ_FOR_EACH_I_IMPL(macro, data, seq)
  
// Handles empty sequences.
// NOTE: maps empty sequences to nothing
#define WG_PP_SEQ_ENUM(seq) \
  WG_PP_SEQ_ENUM_IMPL(seq)

// Handles empty sequences.
// Handles empty token as indx.
#define WG_PP_SEQ_REPLACE(seq, indx, elem) \
  WG_PP_SEQ_REPLACE_IMPL(seq, indx, elem)

//###########
//Impl Macros
//###########

#define WG_PP_SEQ_IFNIL_THENCLEAR_IMPL(seq) \
  BOOST_PP_EXPR_IIF( \
    BOOST_PP_NOT( \
      WG_PP_TOKENS_START_WITH_BOOST_PP_NIL(seq)), \
    seq)

#define WG_PP_SEQ_FOR_EACH_I_IMPL_0(macro, data, seq) BOOST_PP_NIL
#define WG_PP_SEQ_FOR_EACH_I_IMPL_1(macro, data, seq) \
  BOOST_PP_SEQ_FOR_EACH_I(macro, data, seq)
#define WG_PP_SEQ_FOR_EACH_I_IMPL(macro, data, seq) \
  BOOST_PP_EXPAND( \
    BOOST_PP_CAT( \
      WG_PP_SEQ_FOR_EACH_I_IMPL_, \
      WG_PP_ISNEXTTOKEN_A_TUPLE(1, seq)))(macro, data, seq)

#define WG_PP_SEQ_SIZE_IMPL_0(seq) 0
#define WG_PP_SEQ_SIZE_IMPL_1(seq) BOOST_PP_SEQ_SIZE(seq)
#define WG_PP_SEQ_SIZE_IMPL(seq) \
  BOOST_PP_EXPAND( \
    BOOST_PP_CAT( \
      WG_PP_SEQ_SIZE_IMPL_, \
      WG_PP_ISNEXTTOKEN_A_TUPLE(1, seq)))(seq)

#define WG_PP_SEQ_ENUM_IMPL_0(seq)
#define WG_PP_SEQ_ENUM_IMPL_1(seq) BOOST_PP_SEQ_ENUM(seq)
#define WG_PP_SEQ_ENUM_IMPL(seq) \
  BOOST_PP_EXPAND( \
    BOOST_PP_CAT( \
      WG_PP_SEQ_ENUM_IMPL_, \
      WG_PP_ISNEXTTOKEN_A_TUPLE(1, seq)))(seq)

#define WG_PP_SEQ_REPLACE_IMPL_00(seq, indx, elem) BOOST_PP_NIL
#define WG_PP_SEQ_REPLACE_IMPL_01(seq, indx, elem) BOOST_PP_NIL
#define WG_PP_SEQ_REPLACE_IMPL_10(seq, indx, elem) seq
#define WG_PP_SEQ_REPLACE_IMPL_11(seq, indx, elem) \
  BOOST_PP_SEQ_REPLACE(seq, indx, elem)
#define WG_PP_SEQ_REPLACE_IMPL(seq, indx, elem) \
  BOOST_PP_EXPAND( \
    BOOST_PP_CAT( \
      BOOST_PP_CAT( \
        WG_PP_SEQ_REPLACE_IMPL_, \
        WG_PP_ISNEXTTOKEN_A_TUPLE(1, seq)), \
      BOOST_PP_NOT(WG_PP_TOKENS_START_WITH_BOOST_PP_NIL(indx)))) \
  (seq, indx, elem)

#define WG_PP_SEQ_ELEM_IMPL_00(indx, seq) BOOST_PP_NIL
#define WG_PP_SEQ_ELEM_IMPL_01(indx, seq) BOOST_PP_NIL
#define WG_PP_SEQ_ELEM_IMPL_10(indx, seq) BOOST_PP_NIL
#define WG_PP_SEQ_ELEM_IMPL_11(indx, seq) BOOST_PP_SEQ_ELEM(indx, seq)
#define WG_PP_SEQ_ELEM_IMPL(indx, seq) \
  BOOST_PP_EXPAND( \
    BOOST_PP_CAT( \
      BOOST_PP_CAT( \
        WG_PP_SEQ_ELEM_IMPL_, \
        BOOST_PP_NOT(WG_PP_TOKENS_START_WITH_BOOST_PP_NIL(indx))), \
      WG_PP_ISNEXTTOKEN_A_TUPLE(1, seq))) \
  (indx, seq)

#define WG_PP_SEQ_CAT_IMPL_00(x, y) BOOST_PP_NIL
#define WG_PP_SEQ_CAT_IMPL_01(x, y) y
#define WG_PP_SEQ_CAT_IMPL_10(x, y) x
#define WG_PP_SEQ_CAT_IMPL_11(x, y) x y
#define WG_PP_SEQ_CAT_IMPL(x, y) \
  BOOST_PP_EXPAND( \
    BOOST_PP_CAT( \
      WG_PP_SEQ_CAT_IMPL_, \
      BOOST_PP_CAT( \
        WG_PP_ISNEXTTOKEN_A_TUPLE(1, x), \
        WG_PP_ISNEXTTOKEN_A_TUPLE(1, y)))) (x, y)
  
#endif /* WG_PP_SEQ_HH_ */
