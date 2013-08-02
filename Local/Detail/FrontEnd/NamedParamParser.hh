#ifndef WG_PP_NAMEDPARAMPARSER_HH_
#define WG_PP_NAMEDPARAMPARSER_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP.hh>
#include <WG/Local/Detail/Keywords.hh>

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
// id:
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
//   1) WG_PP_NAMEDPARAMPARSER_PARSE_FOUND_<id>_<currentkeyword>(
//        spec, specoptions, nexttransform)
//      if the head token of spec matches "currentkeyword", where nexttransform
//      is the token WG_PP_NAMEDPARAMPARSER_PARSE_<id>_<nextkeyword> , else
//   2) WG_PP_NAMEDPARAMPARSER_PARSE_NOTFOUND_<id>_<currentkeyword>()
//      WG_PP_NAMEDPARAMPARSER_PARSE_<id>_<nextkeyword>(spec, specoptions)
//-----------------------------------------------------------------------------

#define WG_PP_NAMEDPARAMPARSER_MACRONAME( \
  spec, id, currentkeyword, nextkeyword) \
    WG_PP_NAMEDPARAMPARSER_MACRONAME_IMPL( \
      spec, id, currentkeyword, nextkeyword)

#define WG_PP_NAMEDPARAMPARSER_MACROPARAMS( \
  spec, specoptions, id, currentkeyword, nextkeyword) \
    WG_PP_NAMEDPARAMPARSER_MACROPARAMS_IMPL( \
      spec, specoptions, id, currentkeyword, nextkeyword)

//###########
//Impl Macros
//###########

//-------------------------------------
//WG_PP_NAMEDPARAMPARSER_MACRONAME_IMPL
//-------------------------------------

#define WG_PP_NAMEDPARAMPARSER_MACRONAME_IMPL( \
  spec, id, currentkeyword, nextkeyword) \
    BOOST_PP_CAT( \
      WG_PP_NAMEDPARAMPARSER_MACRONAME_IMPL, \
      BOOST_PP_CAT(WG_PP_TOKENS_STARTWITH_, currentkeyword) (spec)) \
    (spec, id, currentkeyword, nextkeyword)
#define WG_PP_NAMEDPARAMPARSER_MACRONAME_IMPL0( \
  spec, id, currentkeyword, nextkeyword) \
    WG_PP_CAT4( \
      WG_PP_NAMEDPARAMPARSER_PARSE_NOTFOUND_, id, _, currentkeyword) () \
    WG_PP_CAT4( \
      WG_PP_NAMEDPARAMPARSER_PARSE_, id, _, nextkeyword)
#define WG_PP_NAMEDPARAMPARSER_MACRONAME_IMPL1( \
  spec, id, currentkeyword, nextkeyword) \
    WG_PP_CAT4(WG_PP_NAMEDPARAMPARSER_PARSE_FOUND_, id, _, currentkeyword)

//----------------------------------
//WG_PP_NAMEDPARAMPARSER_MACROPARAMS
//----------------------------------

#define WG_PP_NAMEDPARAMPARSER_MACROPARAMS_IMPL( \
  spec, specoptions, id, currentkeyword, nextkeyword) \
    BOOST_PP_CAT( \
      WG_PP_NAMEDPARAMPARSER_MACROPARAMS_IMPL, \
      BOOST_PP_CAT(WG_PP_TOKENS_STARTWITH_, currentkeyword) (spec)) \
    (spec, specoptions, id, currentkeyword, nextkeyword)
#define WG_PP_NAMEDPARAMPARSER_MACROPARAMS_IMPL0( \
  spec, specoptions, id, currentkeyword, nextkeyword) \
    (spec, specoptions)
#define WG_PP_NAMEDPARAMPARSER_MACROPARAMS_IMPL1( \
  spec, specoptions, id, currentkeyword, nextkeyword) \
    (spec, \
     specoptions, \
     WG_PP_CAT4(WG_PP_NAMEDPARAMPARSER_PARSE_, id, _, nextkeyword))

#endif /* WG_PP_NAMEDPARAMPARSER_HH_ */
