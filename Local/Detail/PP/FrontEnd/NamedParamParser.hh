#ifndef WG_PP_NAMEDPARAMPARSER_HH_
#define WG_PP_NAMEDPARAMPARSER_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/PP.hh>
#include <WG/Local/Detail/PP/Keywords.hh>

//###########
//Public APIs
//###########

//-----------------------------------------------------------------------------
// Usage:
//   BOOST_PP_EXPAND(
//     WG_PP_NAMEDPARAMPARSER_MACRONAME(...)
//     WG_PP_NAMEDPARAMPARSER_MACROPARAMS(...) )
// spec:
//   tokens containing named parameters.
// specoptions:
//   any additional options to be passed along.
// moduleid:
//   token to uniquely identify macro expansions per module.
// currentkeyword:
//   the current expected named param.
// nextkeyword:
//   the next expected named param.
//
// Preconditions:
//   WG_PP_TOKENS_STARTWITH_<currentkeyword>(...) must be defined.
//
// Expands to:
//   1) <moduleid>_FOUND_<currentkeyword>(spec, specoptions, nexttransform)
//      if the head token of spec matches "currentkeyword", where nexttransform
//      is the token <moduleid>_<nextkeyword> , else
//   2) <moduleid>_NOTFOUND_<currentkeyword>()
//      <moduleid>_<nextkeyword>(spec, specoptions)
//-----------------------------------------------------------------------------

#define WG_PP_NAMEDPARAMPARSER_MACRONAME( \
  spec, moduleid, currentkeyword, nextkeyword) \
    WG_PP_NAMEDPARAMPARSER_MACRONAME_IMPL( \
      spec, moduleid, currentkeyword, nextkeyword)

#define WG_PP_NAMEDPARAMPARSER_MACROPARAMS( \
  spec, specoptions, moduleid, currentkeyword, nextkeyword) \
    WG_PP_NAMEDPARAMPARSER_MACROPARAMS_IMPL( \
      spec, specoptions, moduleid, currentkeyword, nextkeyword)

//###########
//Impl Macros
//###########

//-------------------------------------
//WG_PP_NAMEDPARAMPARSER_MACRONAME_IMPL
//-------------------------------------

#define WG_PP_NAMEDPARAMPARSER_MACRONAME_IMPL( \
  spec, moduleid, currentkeyword, nextkeyword) \
    BOOST_PP_CAT( \
      WG_PP_NAMEDPARAMPARSER_MACRONAME_IMPL, \
      BOOST_PP_CAT(WG_PP_TOKENS_STARTWITH_, currentkeyword) (spec)) \
    (spec, moduleid, currentkeyword, nextkeyword)
#define WG_PP_NAMEDPARAMPARSER_MACRONAME_IMPL0( \
  spec, moduleid, currentkeyword, nextkeyword) \
    WG_PP_UCAT3(moduleid, NOTFOUND, currentkeyword) () \
    WG_PP_UCAT(moduleid, nextkeyword)
#define WG_PP_NAMEDPARAMPARSER_MACRONAME_IMPL1( \
  spec, moduleid, currentkeyword, nextkeyword) \
    WG_PP_UCAT3(moduleid, FOUND, currentkeyword)

//----------------------------------
//WG_PP_NAMEDPARAMPARSER_MACROPARAMS
//----------------------------------

#define WG_PP_NAMEDPARAMPARSER_MACROPARAMS_IMPL( \
  spec, specoptions, moduleid, currentkeyword, nextkeyword) \
    BOOST_PP_CAT( \
      WG_PP_NAMEDPARAMPARSER_MACROPARAMS_IMPL, \
      BOOST_PP_CAT(WG_PP_TOKENS_STARTWITH_, currentkeyword) (spec)) \
    (spec, specoptions, moduleid, currentkeyword, nextkeyword)
#define WG_PP_NAMEDPARAMPARSER_MACROPARAMS_IMPL0( \
  spec, specoptions, moduleid, currentkeyword, nextkeyword) \
    (spec, specoptions)
#define WG_PP_NAMEDPARAMPARSER_MACROPARAMS_IMPL1( \
  spec, specoptions, moduleid, currentkeyword, nextkeyword) \
    (spec, \
     specoptions, \
     WG_PP_UCAT(moduleid, nextkeyword))

#endif /* WG_PP_NAMEDPARAMPARSER_HH_ */
