#include <WG/Local/AutoFunctor.hh>
#include <WG/Local/Tests/test.h>

#define \
  WG_PP_REFTHISU_MATCHES_ERROR_ref_keyword_cannot_be_used_with_thisu_keyword \
    (1) /* unary */
#define WG_PP_TOKENS_START_WITH_REFTHISU_ERRMSG(tokens) \
  BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT( \
    tokens, \
    WG_PP_REFTHISU_MATCHES_)

// Illegal usage of "ref this_" in parambind.
BEGIN WG_PP_TOKENS_START_WITH_REFTHISU_ERRMSG(
  WG_AUTOFUNCTOR(test, parambind (ref this_) ) ) == 1 END

// Illegal usage of "ref this_" in membind.
BEGIN WG_PP_TOKENS_START_WITH_REFTHISU_ERRMSG( \
  WG_AUTOFUNCTOR(test, membind (ref this_) ) ) == 1 END
