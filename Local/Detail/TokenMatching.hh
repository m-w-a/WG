#ifndef WG_PP_TOKENMATCHING_HH_
#define WG_PP_TOKENMATCHING_HH_

#include <boost/preprocessor/punctuation/paren.hpp>
#include <boost/preprocessor/seq/size.hpp>

//###########
//Public APIs
//###########

// tokens:
//   a sequence of tokens that does not contain comma(s) nor end in
//   non-alphanumeric-underscore characters.
// endmatcher:
//   an object-like macro of the form:
//     _<keyword-to-match>_<keyword-to-match>_<some-app-specific-id>
//   that evaluates to: ) (
#define WG_PP_TOKENMATCH_ENDSWITH(tokens, endmatcher) \
  WG_PP_TOKENMATCH_ENDSWITH_IMPL(tokens, endmatcher)

//###########
//Impl Macros
//###########

#define WG_PP_TOKENMATCH_EXPAND(x) x

#define WG_PP_TOKENMATCH_SEQ_EATHEADELEM(x)
#define WG_PP_TOKENMATCH_SEQ_EATHEADELEM_1(x)
#define WG_PP_TOKENMATCH_SEQ_EATHEADELEM_0

#define WG_PP_TOKENMATCH_SEQ_PROCESSHEAD(x) \
  x WG_PP_TOKENMATCH_CAT(WG_PP_TOKENMATCH_SEQ_EATHEADELEM_, x)

// On end token match, will expand to:
//   (tokens-minus-lasttoken)(BOOST_PP_NIL)
// else, will expand to:
//   (some-tokens BOOST_PP_NIL)
#define WG_PP_TOKENMATCH_ENDSWITH_IMPL(tokens, endmatcher) \
  WG_PP_TOKENMATCH_SEQ_ISCOUNT2( \
    BOOST_PP_LPAREN() \
      WG_PP_TOKENMATCH_CAT(tokens, endmatcher BOOST_PP_NIL) \
    BOOST_PP_RPAREN() )

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
