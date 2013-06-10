#ifndef WG_PP_TOKENMATCHING_HH_
#define WG_PP_TOKENMATCHING_HH_

// TODO.
#include <boost/preprocessor.hpp>

//###########
//Public APIs
//###########

// tokens:
//   a sequence of tokens that does not contain comma(s)
// endmatcher:
//   an object-like macro of the form:
//     _<keyword-to-match>_<keyword-to-match>_<some-app-specific-id>
//   that evaluates to: ) (
#define WG_PP_TOKENS_ENDWITH(tokens, endmatcher) \
  WG_PP_TOKENS_ENDWITH_IMPL(tokens, endmatcher)

//###########
//Impl Macros
//###########

#define WG_PP_TOKENS_ENDWITH_IMPL(tokens, endmatcher) \
  WG_PP_TOKENS_ENDWITH_IMPL2( \
    BOOST_PP_LPAREN() \
      BOOST_PP_CAT(tokens, endmatcher BOOST_PP_NIL) \
    BOOST_PP_RPAREN() )

#define WG_PP_TOKENS_ENDWITH_IMPL2(seq) \
  BOOST_PP_IIF( \
    WG_PP_ISNEXTTOKEN_A_TUPLE(1, BOOST_PP_SEQ_POP_FRONT(seq) BOOST_PP_NIL), \
    1, \
    0)

#endif /* WG_PP_TOKENMATCHING_HH_ */
