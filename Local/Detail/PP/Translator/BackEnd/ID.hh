#ifndef WG_PP_ID_HH_
#define WG_PP_ID_HH_

//###########
//Public APIs
//###########

#define WG_PP_ID_GLOBAL_PREFIX() wg
#define WG_PP_ID_DELIMITER() XXX

#define WG_PP_ID_CAT(x, y) \
  BOOST_PP_CAT(x, BOOST_PP_CAT(WG_PP_ID_DELIMITER(), y))

#define WG_PP_ID_MAKE_GLOBAL(name) \
  WG_PP_ID_CAT( \
    WG_PP_ID_GLOBAL_PREFIX(), name)

#endif /* WG_PP_ID_HH_ */
