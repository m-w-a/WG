#ifndef WG_UTIL_PP_SEQ_HH_
#define WG_UTIL_PP_SEQ_HH_

#include <boost/preprocessor.hpp>
#include <WG/Utils/PP.hh>

//###########
//Public APIs
//###########

#define WG_PP_SEQ_ISHEAD_1TUPLE(tuple_seq) \
  WG_PP_SEQ_ISHEAD_1TUPLE_IMPL(tuple_seq)

#define WG_PP_SEQ_ISHEAD_2TUPLE(tuple_seq) \
  WG_PP_SEQ_ISHEAD_2TUPLE_IMPL(tuple_seq)

// Nil sequences are defined to be BOOST_PP_NIL.
#define WG_PP_SEQ_IS_NEXTTOKEN_NOTNILSEQ(seq) \
  WG_PP_SEQ_IS_NEXTTOKEN_NOTNILSEQ_IMPL(seq)

#define WG_PP_IS_SEQ_COUNT_EVEN(seq) \
  BOOST_PP_NOT(BOOST_PP_MOD(BOOST_PP_SEQ_SIZE(seq), 2))

#define WG_PP_IS_SEQ_COUNT_ODD(seq) \
  BOOST_PP_NOT(WG_PP_IS_SEQ_COUNT_EVEN(seq))

#define WG_PP_IS_SEQ_INDEX_LAST(seq_count, indx) \
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
#define WG_PP_SEQ_ENUM(seq) \
  WG_PP_SEQ_ENUM_IMPL(seq)

// Handles empty sequences.
// Handles empty token as indx.
#define WG_PP_SEQ_REPLACE(seq, indx, elem) \
  WG_PP_SEQ_REPLACE_IMPL(seq, indx, elem)

//###########
//Impl Macros
//###########

#define WG_PP_SEQ_ISHEAD_1TUPLE_IMPL(tuple_seq) \
  WG_PP_TOKENS_START_WITH_WG_PP_TRUE( \
    BOOST_PP_EXPAND( \
      WG_PP_MAP_1ARG_TO_TRUETOKEN \
      tuple_seq))

#define WG_PP_SEQ_ISHEAD_2TUPLE_IMPL(tuple_seq) \
  WG_PP_TOKENS_START_WITH_WG_PP_TRUE( \
    BOOST_PP_EXPAND( \
      WG_PP_MAP_2ARG_TO_TRUETOKEN \
      tuple_seq))

#define WG_PP_SEQ_MAP_NIL_TO_TRUETOKEN(seq) WG_PP_TRUE
#define WG_PP_SEQ_IS_NEXTTOKEN_NOTNILSEQ_IMPL(seq) \
  WG_PP_TOKENS_START_WITH_WG_PP_TRUE( \
    BOOST_PP_EXPAND(WG_PP_SEQ_MAP_NIL_TO_TRUETOKEN seq))

#define WG_PP_SEQ_FOR_EACH_I_IMPL_0(macro, data, seq)
#define WG_PP_SEQ_FOR_EACH_I_IMPL_1(macro, data, seq) \
  BOOST_PP_SEQ_FOR_EACH_I(macro, data, seq)
#define WG_PP_SEQ_FOR_EACH_I_IMPL(macro, data, seq) \
  BOOST_PP_EXPAND( \
    BOOST_PP_CAT( \
      WG_PP_SEQ_FOR_EACH_I_IMPL_, \
      WG_PP_SEQ_IS_NEXTTOKEN_NOTNILSEQ(seq)))(macro, data, seq)

#define WG_PP_SEQ_SIZE_IMPL_0(seq) 0
#define WG_PP_SEQ_SIZE_IMPL_1(seq) BOOST_PP_SEQ_SIZE(seq)
#define WG_PP_SEQ_SIZE_IMPL(seq) \
  BOOST_PP_EXPAND( \
    BOOST_PP_CAT( \
      WG_PP_SEQ_SIZE_IMPL_, \
      WG_PP_SEQ_IS_NEXTTOKEN_NOTNILSEQ(seq)))(seq)

#define WG_PP_SEQ_ENUM_IMPL_0(seq)
#define WG_PP_SEQ_ENUM_IMPL_1(seq) BOOST_PP_SEQ_ENUM(seq)
#define WG_PP_SEQ_ENUM_IMPL(seq) \
  BOOST_PP_EXPAND( \
    BOOST_PP_CAT(WG_PP_SEQ_ENUM_IMPL_, WG_PP_SEQ_IS_NEXTTOKEN_NOTNILSEQ(seq)))(seq)

#define WG_PP_SEQ_REPLACE_IMPL_00(seq, indx, elem)
#define WG_PP_SEQ_REPLACE_IMPL_01(seq, indx, elem)
#define WG_PP_SEQ_REPLACE_IMPL_10(seq, indx, elem) seq
#define WG_PP_SEQ_REPLACE_IMPL_11(seq, indx, elem) \
  BOOST_PP_SEQ_REPLACE(seq, indx, elem)
#define WG_PP_SEQ_REPLACE_IMPL(seq, indx, elem) \
  BOOST_PP_EXPAND( \
    BOOST_PP_CAT( \
      BOOST_PP_CAT( \
        WG_PP_SEQ_REPLACE_IMPL_, \
        WG_PP_SEQ_IS_NEXTTOKEN_NOTNILSEQ(seq)), \
      BOOST_PP_NOT(WG_PP_TOKENS_START_WITH_BOOST_PP_NIL(indx)))) \
  (seq, indx, elem)

#define WG_PP_SEQ_ELEM_IMPL_00(indx, seq)
#define WG_PP_SEQ_ELEM_IMPL_01(indx, seq)
#define WG_PP_SEQ_ELEM_IMPL_10(indx, seq)
#define WG_PP_SEQ_ELEM_IMPL_11(indx, seq) BOOST_PP_SEQ_ELEM(indx, seq)
#define WG_PP_SEQ_ELEM_IMPL(indx, seq) \
  BOOST_PP_EXPAND( \
    BOOST_PP_CAT( \
      BOOST_PP_CAT( \
        WG_PP_SEQ_ELEM_IMPL_, \
        BOOST_PP_NOT(WG_PP_TOKENS_START_WITH_BOOST_PP_NIL(indx))), \
      WG_PP_SEQ_IS_NEXTTOKEN_NOTNILSEQ(seq))) \
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
        WG_PP_SEQ_IS_NEXTTOKEN_NOTNILSEQ(x), \
        WG_PP_SEQ_IS_NEXTTOKEN_NOTNILSEQ(y)))) (x, y)
  
#endif /* WG_UTIL_PP_SEQ_HH_ */
