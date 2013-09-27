#include <WG/Local/AutoFunctor.hh>
#include <WG/Local/Tests/test.h>
#include <WG/Local/Detail/PP/TokenMatching.hh>

#define WG_PP_KEYWORDS_STARTSWITH_INVALIDNAMEDPARAMETERS_ERRMSG(tokens) \
  WG_PP_TOKENMATCH_BEGINSWITH(\
    tokens, \
    WG_PP_INVALIDNAMEDPARAMETERS_TOKENMATCH_BEGINSWITH_)

#define \
  WG_PP_INVALIDNAMEDPARAMETERS_TOKENMATCH_BEGINSWITH_ERROR_Invalid_tokensXXXassignTo \
    WG_PP_TOKENMATCH_FRONTMATCH
// Misspelled assignto.
BEGIN WG_PP_KEYWORDS_STARTSWITH_INVALIDNAMEDPARAMETERS_ERRMSG( \
  WG_AUTOFUNCTOR(assign, assignTo ((bool) didAssign) ) ) == 1 END

// Invalid named token "pAraMBInD" in the middle.
#define \
  WG_PP_INVALIDNAMEDPARAMETERS_TOKENMATCH_BEGINSWITH_ERROR_Invalid_tokensXXXpAraMBInD \
    WG_PP_TOKENMATCH_FRONTMATCH
BEGIN WG_PP_KEYWORDS_STARTSWITH_INVALIDNAMEDPARAMETERS_ERRMSG( \
  WG_AUTOFUNCTOR
  (makeGingerBreadCookie,
    assignto (success)
    return (int)
    pAraMBInD (pinchOfSalt) ((bool) dashOfSugar)
    paramset (temperature, 450.0f) ((double) bakingTime, 0.5)
    membind (pinchOfSalt) ((bool) dashOfSugar)
    memset (temperature, 450.0f) ((double) bakingTime, 0.5) ) ) == 1 END
