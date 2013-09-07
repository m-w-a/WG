#ifndef WG_PP_ALTSEQ_HH_
#define WG_PP_ALTSEQ_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/PP.hh>
#include <WG/Local/Detail/PP/Seq.hh>

//###########
//Public APIs
//###########

#define WG_PP_ALTSEQ_APPEND_COMMA_TO_HEAD_1(x) \
  WG_PP_TUPLIZE_1(x) BOOST_PP_COMMA() 2

#define WG_PP_ALTSEQ_APPEND_COMMA_TO_HEAD_2(x, y) \
  WG_PP_TUPLIZE_2(x, y) BOOST_PP_COMMA() 1

///@brief head_tuple_kind
///@brief   an unsigned integer representing the kind of tuple the head tuple
///@brief   is, i.e., 1-tuple, 2-tuple, etc.
///@brief TRANSFORM
///@brief   the name of a one or two parameter macro to apply to
///@brief   the head of tuple_seq
///@brief TRANSFORM_REST
///@brief   the name of a single parameter macro to apply to the rest of
///@brief   tuple_seq.
#define WG_PP_ALTSEQ_TRANSFORM( \
  head_tuple_kind, \
  tuple_seq, \
  TRANSFORM, \
  TRANSFORM_REST) \
    WG_PP_ALTSEQ_TRANSFORM_HEAD_IMPL1( \
      head_tuple_kind, tuple_seq, TRANSFORM, TRANSFORM_REST)

///@brief head_tuple_kind
///@brief   an unsigned integer representing the arity of the head tuple
#define WG_PP_ALTSEQ_EAT_HEAD(head_tuple_kind, tuple_seq) \
  WG_PP_ALTSEQ_TRANSFORM( \
    head_tuple_kind, \
    tuple_seq, \
    BOOST_PP_TUPLE_EAT(head_tuple_kind), \
    WG_PP_IDENTITY)

///@brief head_tuple_kind
///@brief   an unsigned integer representing the arity of the head tuple
///@brief 1-tuplizes the head of tuple_seq, and discards the rest.
#define WG_PP_ALTSEQ_1TUPLIZE_HEAD(head_tuple_kind, tuple_seq) \
  WG_PP_ALTSEQ_TRANSFORM( \
    head_tuple_kind, \
    tuple_seq, \
    BOOST_PP_CAT(WG_PP_1TUPLIZE_, head_tuple_kind), \
    BOOST_PP_TUPLE_EAT(1))

#define WG_PP_ALTSEQ_LINEARIZE(tuple_seq) \
  BOOST_PP_FOR( \
    WG_PP_ALTSEQ_LINEARIZE_MAKE_INITIAL_STATE(tuple_seq), \
    WG_PP_ALTSEQ_LINEARIZE_PRED, \
    WG_PP_ALTSEQ_LINEARIZE_INC_OP, \
    WG_PP_ALTSEQ_LINEARIZE_HEAD)

//###########
//Impl Macros
//###########

#define WG_PP_ALTSEQ_TRANSFORM_HEAD_IMPL1( \
  head_tuple_kind, \
  tuple_seq, \
  TRANSFORM, \
  TRANSFORM_REST) \
    BOOST_PP_EXPAND( \
      WG_PP_ALTSEQ_TRANSFORM_HEAD_IMPL2 \
        BOOST_PP_LPAREN() \
          BOOST_PP_CAT( \
            WG_PP_ALTSEQ_APPEND_COMMA_TO_HEAD_, head_tuple_kind) \
          tuple_seq BOOST_PP_COMMA() \
          TRANSFORM BOOST_PP_COMMA() \
          TRANSFORM_REST \
        BOOST_PP_RPAREN() )

#define WG_PP_ALTSEQ_TRANSFORM_HEAD_IMPL2( \
  head_tuple, \
  tuple_seq_rest, \
  TRANSFORM, \
  TRANSFORM_REST) \
    TRANSFORM head_tuple \
    BOOST_PP_EXPR_IIF( \
      WG_PP_TOKENS_START_WITH_WG_PP_TRUE( \
        BOOST_PP_CAT(WG_PP_MAP_TO_TRUETOKEN_ARG, tuple_seq_rest)), \
      TRANSFORM_REST( \
        BOOST_PP_CAT( \
          WG_PP_TUPLIZE_, \
          tuple_seq_rest)) BOOST_PP_EMPTY) ()

//----------------
//ALTSEQ_LINEARIZE
//----------------

#define WG_PP_ALTSEQ_LINEARIZE_MAKE_INITIAL_STATE(tuple_seq) \
  (0, tuple_seq)
#define WG_PP_ALTSEQ_LINEARIZE_GET_HEAD_INDEX(state) \
  BOOST_PP_TUPLE_ELEM(2, 0, state)
#define WG_PP_ALTSEQ_LINEARIZE_GET_HEAD_ARITY(state) \
  BOOST_PP_INC( \
    BOOST_PP_MOD( \
      WG_PP_ALTSEQ_LINEARIZE_GET_HEAD_INDEX(state), \
      2))
#define WG_PP_ALTSEQ_LINEARIZE_GET_SEQ(state) \
  BOOST_PP_TUPLE_ELEM(2, 1, state)

#define WG_PP_ALTSEQ_LINEARIZE_PRED(r, state) \
  WG_PP_ISNEXTTOKEN_A_TUPLE( \
    WG_PP_ALTSEQ_LINEARIZE_GET_HEAD_ARITY(state), \
    WG_PP_ALTSEQ_LINEARIZE_GET_SEQ(state))

#define WG_PP_ALTSEQ_LINEARIZE_INC_OP_IMPL1(indx, seq) \
  BOOST_PP_IIF( \
    WG_PP_TOKENS_START_WITH_WG_PP_TRUE( \
      BOOST_PP_CAT( \
        WG_PP_MAP_TO_TRUETOKEN_ARG, \
        WG_PP_ALTSEQ_LINEARIZE_GET_HEAD_ARITY((indx, seq))) seq), \
    (indx, seq()), \
    (indx, seq))
#define WG_PP_ALTSEQ_LINEARIZE_INC_OP(r, state) \
  WG_PP_ALTSEQ_LINEARIZE_INC_OP_IMPL1( \
    BOOST_PP_INC(BOOST_PP_TUPLE_ELEM(2, 0, state)), \
    WG_PP_ALTSEQ_EAT_HEAD( \
      WG_PP_ALTSEQ_LINEARIZE_GET_HEAD_ARITY(state), \
      WG_PP_ALTSEQ_LINEARIZE_GET_SEQ(state)) \
    BOOST_PP_EMPTY)

#define WG_PP_ALTSEQ_LINEARIZE_HEAD(r, state) \
    WG_PP_ALTSEQ_1TUPLIZE_HEAD( \
      WG_PP_ALTSEQ_LINEARIZE_GET_HEAD_ARITY(state), \
      WG_PP_ALTSEQ_LINEARIZE_GET_SEQ(state))

#endif /* WG_PP_ALTSEQ_HH_ */
