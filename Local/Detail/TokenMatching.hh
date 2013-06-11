#ifndef WG_PP_TOKENMATCHING_HH_
#define WG_PP_TOKENMATCHING_HH_

#include <boost/preprocessor/punctuation/paren.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/enum.hpp>

//###########
//Public APIs
//###########

// tokens:
//   a sequence of tokens that does not contain comma(s) nor begins with any
//   non-alphanumeric-underscore characters.
// frontmatcher:
//   a token of the form:
//     <some-app-specific-id>_<keyword-to-match>_
//   that has an accompanying object like macro of the form:
//     <some-app-specific-id>_<keyword-to-match>_<keyword-to-match>
//   which must expand to: WG_PP_TOKENMATCH_FRONTMATCH
#define WG_PP_TOKENMATCH_BEGINSWITH(tokens, frontmatcher) \
  WG_PP_TOKENMATCH_BEGINSWITH_IMPL(tokens, frontmatcher)

// tokens:
//   a sequence of tokens that does not contain comma(s) nor ends in
//   non-alphanumeric-underscore characters.
// endmatcher:
//   a token of the form:
//     _<keyword-to-match>_<some-app-specific-id>
//   that has an accompanying object like macro of the form:
//     <keyword-to-match>_<keyword-to-match>_<some-app-specific-id>
//   which must expand to: WG_PP_TOKENMATCH_ENDMATCH
#define WG_PP_TOKENMATCH_ENDSWITH(tokens, endmatcher) \
  WG_PP_TOKENMATCH_ENDSWITH_IMPL(tokens, endmatcher)

// tokenXs:
//   1) either a single token, or
//   2) a sequence of tokens that does not contain comma(s) nor begins with any
//     non-alphanumeric-underscore characters.
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
      BOOST_PP_NIL WG_PP_TOKENMATCH_CAT(frontmatcher, tokens) \
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
      WG_PP_TOKENMATCH_CAT(tokens, endmatcher) BOOST_PP_NIL \
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
      WG_PP_TOKENMATCH_CAT(matcher, tokenXs) \
    BOOST_PP_RPAREN() )

#define WG_PP_TOKENMATCH_MATCHES_IMPL2(seq) \
  WG_PP_TOKENMATCH_CAT( \
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
    WG_PP_TOKENMATCH_CAT( \
      WG_PP_TOKENMATCH_CAT( \
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
      WG_PP_TOKENMATCH_CAT(WG_PP_EVAL_, cat_tokenXs) \
    BOOST_PP_RPAREN() )

#define WG_PP_TOKENMATCH_MATCHES_IMPL6(bit, ignore) \
  bit

//-----
//Utils
//-----

#define WG_PP_TOKENMATCH_SEQ_ISCOUNT2(seq) \
  WG_PP_TOKENMATCH_CAT( \
    WG_PP_TOKENMATCH_SEQ_ISCOUNT2_, \
    BOOST_PP_SEQ_SIZE(seq))

#define WG_PP_TOKENMATCH_SEQ_ISCOUNT2_2 1
#define WG_PP_TOKENMATCH_SEQ_ISCOUNT2_1 0

//--------------------
//WG_PP_TOKENMATCH_CAT
//--------------------
// Use our own version instead of BOOST_PP_CAT, since if BOOST_PP_CAT expands
// to a macro that contains any of this files' public apis, those apis will be
// disabled.
//--------------------

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
# include <boost/preprocessor/config/config.hpp>
#
# /* WG_PP_TOKENMATCH_CAT */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define WG_PP_TOKENMATCH_CAT(a, b) WG_PP_TOKENMATCH_CAT_I(a, b)
# else
#    define WG_PP_TOKENMATCH_CAT(a, b) WG_PP_TOKENMATCH_CAT_OO((a, b))
#    define WG_PP_TOKENMATCH_CAT_OO(par) WG_PP_TOKENMATCH_CAT_I ## par
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define WG_PP_TOKENMATCH_CAT_I(a, b) a ## b
# else
#    define WG_PP_TOKENMATCH_CAT_I(a, b) WG_PP_TOKENMATCH_CAT_II(~, a ## b)
#    define WG_PP_TOKENMATCH_CAT_II(p, res) res
# endif

#endif /* WG_PP_TOKENMATCHING_HH_ */
