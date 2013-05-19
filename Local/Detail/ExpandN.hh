#ifndef WG_PP_EXPANDN_HH_
#define WG_PP_EXPANDN_HH_

#include <boost/preprocessor.hpp>

//###########
//Public APIs
//###########

#define WG_PP_EXPANDN(tokenstoexpand, expandcount) \
  BOOST_PP_TUPLE_ELEM( \
    2, \
    1, \
    WG_PP_EXPANDN_IMPL(tokenstoexpand, expandcount))

//###########
//Impl Macros
//###########

#define WG_PP_EXPANDN_IMPL(tokenstoexpand, expandcount) \
  BOOST_PP_WHILE( \
    WG_PP_AUTOFUNCTION_EXPANDN_WHILELOOP_PRED, \
    WG_PP_AUTOFUNCTION_EXPANDN_WHILELOOP_OP, \
    WG_PP_AUTOFUNCTION_EXPANDN_WHILELOOP_INITSTATE( \
      expandcount, \
      tokenstoexpand))

#define WG_PP_AUTOFUNCTION_EXPANDN_WHILELOOP_INITSTATE( \
  expandcount, tokenstoexpand) \
    (expandcount, tokenstoexpand)
#define WG_PP_AUTOFUNCTION_EXPANDN_WHILELOOP_CURRENTCOUNT(state) \
  BOOST_PP_TUPLE_ELEM(2, 0, state)
#define WG_PP_AUTOFUNCTION_EXPANDN_WHILELOOP_CURRENTTOKEN(state) \
  BOOST_PP_TUPLE_ELEM(2, 1, state)

#define WG_PP_AUTOFUNCTION_EXPANDN_WHILELOOP_PRED(d, state) \
  WG_PP_AUTOFUNCTION_EXPANDN_WHILELOOP_CURRENTCOUNT(state)

#define WG_PP_AUTOFUNCTION_EXPANDN_WHILELOOP_OP(d, state) \
  ( \
    BOOST_PP_DEC( \
      WG_PP_AUTOFUNCTION_EXPANDN_WHILELOOP_CURRENTCOUNT(state)), \
    BOOST_PP_EXPAND( \
      WG_PP_AUTOFUNCTION_EXPANDN_WHILELOOP_CURRENTTOKEN(state)) \
  )

#endif /* WG_PP_EXPANDN_HH_ */
