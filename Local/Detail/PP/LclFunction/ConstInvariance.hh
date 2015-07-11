#ifndef WG_PP_LOCAL_DETAIL_LCLFUNCTION_CONSTINVARIANCE_HH_
#define WG_PP_LOCAL_DETAIL_LCLFUNCTION_CONSTINVARIANCE_HH_

//###########
//Public APIs
//###########

// These macros are to mark the places were code needs to be modified to ensure
// that local function objects are const invariant.
// (This allows local function objects to be used with const and non-const
// std::function objects.)

#define WG_PP_LCLFUNCTION_CONSTINVARIANCE_KEYWORD_CONST const
#define WG_PP_LCLFUNCTION_CONSTINVARIANCE_KEYWORD_MUTABLE mutable

#endif /* WG_PP_LOCAL_DETAIL_LCLFUNCTION_CONSTINVARIANCE_HH_ */
