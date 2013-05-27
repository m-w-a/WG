#ifndef WG_PP_AUTOFUNCTIONCODEGEN_HH_
#define WG_PP_AUTOFUNCTIONCODEGEN_HH_

#include <boost/preprocessor.hpp>

//###########
//Public APIs
//###########

//###########
//Impl Macros
//###########

#define WG_PP_AUTOFUNCTION_CG_FORMATNAME(name) \
  BOOST_PP_CAT(WG_PP_IDENTITY(wgWWWautofunctionWWW), name)
  
#endif //WG_PP_AUTOFUNCTIONCODEGEN_HH_