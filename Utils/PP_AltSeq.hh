#ifndef WG_UTIL_PP_ALTSEQ_HH_
#define WG_UTIL_PP_ALTSEQ_HH_

#include <boost/preprocessor.hpp>
#include <WG/Utils/PP.hh>

//###########
//Public APIs
//###########

#define WG_PP_ALTSEQ_APPEND_COMMA_TO_HEAD_1(x) \
  WG_PP_TUPLIZE_1(x) BOOST_PP_COMMA()

#define WG_PP_ALTSEQ_APPEND_COMMA_TO_HEAD_2(x, y) \
  WG_PP_TUPLIZE_2(x, y) BOOST_PP_COMMA()

//###########
//Impl Macros
//###########

#endif /* WG_UTIL_PP_ALTSEQ_HH_ */
