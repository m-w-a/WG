#ifndef WG_PP_TOKENMATCHING_HH_
#define WG_PP_TOKENMATCHING_HH_

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/punctuation/paren.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/enum.hpp>

//###########
//Public APIs
//###########

//------------------------------------------------------------------------------
//API Note:
//  1) The pattern "_<keyword-to-match>_<keyword-to-match>" described below
//    is required in order to distinguish between different tokens that appear
//    adjacent to each other.
//    For example, if both "const" and "ref" are keywords to match, and the
//    pattern "_<keyword-to-match>" was used for the accompanying object like
//    macro instead of the above, then
//    <some-app-specific-id>_const and <some-app-specific-id>_ref will BOTH
//    return true for the following series of tokens:
//      const ref
//------------------------------------------------------------------------------

// Evaluates to exactly 0 or 1.
// tokens:
//   a series of tokens that does not contain comma(s) nor begins with any
//   non-alphanumeric, non-underscore characters.
// frontmatcher:
//   a token of the form:
//     <some-app-specific-id>_<keyword-to-match>_
//   that has an accompanying object like macro of the form:
//     <some-app-specific-id>_<keyword-to-match>_<keyword-to-match>
//   which must expand to: WG_PP_TOKENMATCH_FRONTMATCH
#define WG_PP_TOKENMATCH_BEGINSWITH(tokens, frontmatcher) \
  WG_PP_TOKENMATCH_BEGINSWITH_IMPL(tokens, frontmatcher)

// Evaluates exactly to 0 or 1.
// tokens:
//   a series of tokens that does not contain comma(s) nor ends in
//   non-alphanumeric, non-underscore characters.
// endmatcher:
//   a token of the form:
//     _<keyword-to-match>_<some-app-specific-id>
//   that has an accompanying object like macro of the form:
//     <keyword-to-match>_<keyword-to-match>_<some-app-specific-id>
//   which must expand to: WG_PP_TOKENMATCH_ENDMATCH
#define WG_PP_TOKENMATCH_ENDSWITH(tokens, endmatcher) \
  WG_PP_TOKENMATCH_ENDSWITH_IMPL(tokens, endmatcher)

// Evaluates exactly to 0 or 1.
// tokenXs:
//   1) either a single token, or
//   2) a series of tokens that does not contain comma(s) nor begins with any
//     non-alphanumeric, non-underscore characters.
// matcher:
//   a token of the form:
//     <some-app-specific-id>_<keyword-to-match>_
//   that has an accompanying object like macro of the form:
//     <some-app-specific-id>_<keyword-to-match>_<keyword-to-match>
//   which must expand to: WG_PP_TOKENMATCH_EXACTMATCH
#define WG_PP_TOKENMATCH_MATCHES(tokenXs, matcher) \
  WG_PP_TOKENMATCH_MATCHES_IMPL(tokenXs, matcher)

//###########
//Impl Macros
//###########

#define WG_PP_TOKENMATCH_EXPAND(x) x
#define WG_PP_TOKENMATCH_EXPAND2(x) x

//---------------------------
//WG_PP_TOKENMATCH_BEGINSWITH
//---------------------------

#define WG_PP_TOKENMATCH_FRONTMATCH ) (

// On front token match, will expand to:
//   (BOOST_PP_NIL)(tokens-minus-1st-token)
// else, will expand to:
//   (BOOST_PP_NIL some-tokens)
#define WG_PP_TOKENMATCH_BEGINSWITH_IMPL(tokens, frontmatcher) \
  WG_PP_TOKENMATCH_SEQ_ISCOUNT2( \
    BOOST_PP_LPAREN() \
      BOOST_PP_NIL BOOST_PP_CAT(frontmatcher, tokens) \
    BOOST_PP_RPAREN() )

//-------------------------
//WG_PP_TOKENMATCH_ENDSWITH
//-------------------------

#define WG_PP_TOKENMATCH_ENDMATCH ) (

// On end token match, will expand to:
//   (tokens-minus-lasttoken)(BOOST_PP_NIL)
// else, will expand to:
//   (some-tokens BOOST_PP_NIL)
#define WG_PP_TOKENMATCH_ENDSWITH_IMPL(tokens, endmatcher) \
  WG_PP_TOKENMATCH_SEQ_ISCOUNT2( \
    BOOST_PP_LPAREN() \
      BOOST_PP_CAT(tokens, endmatcher) BOOST_PP_NIL \
    BOOST_PP_RPAREN() )

//------------------------
//WG_PP_TOKENMATCH_MATCHES
//------------------------

#define WG_PP_TOKENMATCH_EXACTMATCH ) ( xxx

// On front token match, will expand to:
//   (WG_PP_TOKENMATCH_MARKER)(xxx tokens-minus-1st-token)
// else, will expand to:
//   (WG_PP_TOKENMATCH_MARKER some-tokens)
#define WG_PP_TOKENMATCH_MATCHES_IMPL(tokenXs, matcher) \
  WG_PP_TOKENMATCH_MATCHES_IMPL2( \
    BOOST_PP_LPAREN() \
      WG_PP_TOKENMATCH_MARKER \
      BOOST_PP_CAT(matcher, tokenXs) \
    BOOST_PP_RPAREN() )

#define WG_PP_TOKENMATCH_MATCHES_IMPL2(seq) \
  BOOST_PP_CAT( \
    WG_PP_TOKENMATCH_MATCHES_IMPL3_, \
    BOOST_PP_SEQ_SIZE(seq)) (seq)

#define WG_PP_TOKENMATCH_MATCHES_IMPL3_1(seq) 0
#define WG_PP_TOKENMATCH_MATCHES_IMPL3_2(seq) \
  WG_PP_TOKENMATCH_EXPAND( \
    WG_PP_TOKENMATCH_MATCHES_IMPL4 \
    BOOST_PP_LPAREN() \
      BOOST_PP_SEQ_ENUM(seq) \
    BOOST_PP_RPAREN() )

#define WG_PP_TOKENMATCH_MATCHES_IMPL4(first, second) \
  WG_PP_TOKENMATCH_MATCHES_IMPL5( \
    BOOST_PP_CAT( \
      BOOST_PP_CAT( \
        first, \
        second), \
      WG_PP_TOKENMATCH_MARKER) )

#define WG_PP_EVAL_WG_PP_TOKENMATCH_MARKERxxx 0, WG_PP_TOKENMATCH_MARKER
#define WG_PP_EVAL_WG_PP_TOKENMATCH_MARKERxxxWG_PP_TOKENMATCH_MARKER \
  1, WG_PP_TOKENMATCH_MARKER
#define WG_PP_TOKENMATCH_MATCHES_IMPL5(cat_tokenXs) \
  WG_PP_TOKENMATCH_EXPAND2( \
    WG_PP_TOKENMATCH_MATCHES_IMPL6 \
    BOOST_PP_LPAREN() \
      BOOST_PP_CAT(WG_PP_EVAL_, cat_tokenXs) \
    BOOST_PP_RPAREN() )

#define WG_PP_TOKENMATCH_MATCHES_IMPL6(bit, ignore) \
  bit

//-----
//Utils
//-----

#define WG_PP_TOKENMATCH_SEQ_ISCOUNT2(seq) \
  BOOST_PP_CAT( \
    WG_PP_TOKENMATCH_SEQ_ISCOUNT2_, \
    BOOST_PP_SEQ_SIZE(seq))

#define WG_PP_TOKENMATCH_SEQ_ISCOUNT2_2 1
#define WG_PP_TOKENMATCH_SEQ_ISCOUNT2_1 0

#endif /* WG_PP_TOKENMATCHING_HH_ */
