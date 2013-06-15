#ifndef WG_PP_BOUNDVARDCLNNORMALIZE_HH_
#define WG_PP_BOUNDVARDCLNNORMALIZE_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/Keywords.hh>
#include <WG/Local/Detail/Seq.hh>
#include <WG/Local/Detail/FrontEnd/VarDcln.hh>
#include <WG/Local/Detail/FrontEnd/VarDclnExplicit.hh>
#include <WG/Local/Detail/FrontEnd/VarDclnImplicit.hh>

//###########
//Public APIs
//###########

// Expands to the following:
//   {(parsed-explicit-or-deduced-type) (bound-var-name)}+
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_BOUNDVARDCLN_NORMALIZE(boundvardcln) \
  WG_PP_BOUNDVARDCLN_NORMALIZE_IMPL(boundvardcln)

//###########
//Impl Macros
//###########

#define WG_PP_BOUNDVARDCLN_NORMALIZE_IMPL(boundvardcln) \
  BOOST_PP_IIF( \
    WG_PP_VARDCLN_ISEXPLICIT(boundvardcln), \
    WG_PP_VARDCLNEXPLICIT_TUPLIZE, \
    WG_PP_VARDCLNIMPLICIT_TUPLIZE) (boundvardcln)

#endif //WG_PP_BOUNDVARDCLNNORMALIZE_HH_
