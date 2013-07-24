#include <WG/Local/AutoFunctor.hh>
#include <WG/Local/Tests/test.h>

#define WG_PP_TOKENS_START_WITH_INVALIDNAMEDPARAMETERS_ERRMSG(tokens) \
  BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT( \
    tokens, \
    WG_PP_INVALIDNAMEDPARAMETERS_MATCHES_)

#define \
  WG_PP_INVALIDNAMEDPARAMETERS_MATCHES_ERROR_Invalid_tokensXXXassignTo \
    (1) /* unary */
// Misspelled assignto.
BEGIN WG_PP_TOKENS_START_WITH_INVALIDNAMEDPARAMETERS_ERRMSG( \
  WG_AUTOFUNCTOR(assign, assignTo ((bool) didAssign) ) ) == 1 END

// Invalid named token in the middle.
#define \
  WG_PP_INVALIDNAMEDPARAMETERS_MATCHES_ERROR_Invalid_tokensXXXpAraMBInD \
    (1) /* unary */
BEGIN WG_PP_TOKENS_START_WITH_INVALIDNAMEDPARAMETERS_ERRMSG( \
  WG_AUTOFUNCTOR
  (makeGingerBreadCookie,
    assignto (success)
    return (int)
    pAraMBInD (pinchOfSalt) ((bool) dashOfSugar)
    paramset (temperature, 450.0f) ((double) bakingTime, 0.5)
    membind (pinchOfSalt) ((bool) dashOfSugar)
    memset (temperature, 450.0f) ((double) bakingTime, 0.5) ) ) == 1 END
