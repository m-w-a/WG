#ifndef WG_PP_LOCALOPERANDSYNTAXCHECK_HH_
#define WG_PP_LOCALOPERANDSYNTAXCHECK_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP.hh>
#include <WG/Local/Detail/BackEnd/TypeExtractor.hh>
#include <WG/Local/Detail/BackEnd/SymbolTableUtil.hh>

//###########
//Public APIs
//###########

// Creates a noop struct for checking the syntax of local operands.
// This has to be done in the CodeGen phase since it's impossible to do in the
// front end without running into UB. Explicitly, one can't check for const or
// & usage in local(SomeType *) without having to concat '&' or '*'.
//
// symbtbl:
//   must have the following defined:
//     1) WG_PP_STUTIL_CALL2(TYPESEQ, <suffix>, symbtbl)
//     2) WG_PP_STUTIL_CALL2(OBJSEQ, <suffix>, symbtbl)
//   where suffix is declared in specseq.
//
// specseq:
//   { ( (suffix)(varrootname) ) }+
//
//   varrootname:
//     the root name of the congruence class of variables that if are locally
//     typed then should be syntax checked.
#define WG_PP_LOCALOPERANDSYNTAXCHECK_DCLN(syntaxcheckername, symbtbl, specseq) \
  WG_PP_LOCALOPERANDSYNTAXCHECK_DCLN_IMPL(syntaxcheckername, symbtbl, specseq)

//###########
//Impl Macros
//###########

#define  WG_PP_LOCALOPERANDSYNTAXCHECK_EXPAND1(x) x

#define WG_PP_LOCALOPERANDSYNTAXCHECK_SPEC_SUFFIX(spec) \
  BOOST_PP_SEQ_ELEM(0, spec)
#define WG_PP_LOCALOPERANDSYNTAXCHECK_SPEC_VARROOTNAME(spec) \
  BOOST_PP_SEQ_ELEM(1, spec)

#define WG_PP_LOCALOPERANDSYNTAXCHECK_DCLN_IMPL( \
  syntaxcheckername, symbtbl, specseq) \
    struct syntaxcheckername \
    { \
      BOOST_PP_SEQ_FOR_EACH( \
        WG_PP_LOCALOPERANDSYNTAXCHECK_CNGRNCECLASS_MEMBERDCLN, \
        symbtbl, \
        specseq) \
    };

// BOOST_PP_SEQ_FOR_EACH functor.
#define WG_PP_LOCALOPERANDSYNTAXCHECK_CNGRNCECLASS_MEMBERDCLN(r, symbtbl, spec) \
  WG_PP_LOCALOPERANDSYNTAXCHECK_CNGRNCECLASS_MEMBERDCLN2( \
    WG_PP_STUTIL_CALL2( \
      TYPESEQ, WG_PP_LOCALOPERANDSYNTAXCHECK_SPEC_SUFFIX(spec), symbtbl), \
    WG_PP_STUTIL_CALL2( \
      OBJSEQ, WG_PP_LOCALOPERANDSYNTAXCHECK_SPEC_SUFFIX(spec), symbtbl), \
    WG_PP_LOCALOPERANDSYNTAXCHECK_SPEC_VARROOTNAME(spec))

#define WG_PP_LOCALOPERANDSYNTAXCHECK_CNGRNCECLASS_MEMBERDCLN2( \
  typeseq, objseq, varrootname) \
    WG_PP_LOCALOPERANDSYNTAXCHECK_EXPAND1( \
      BOOST_PP_EMPTY \
      WG_PP_SEQ_IFNIL_THENMAPTO( \
        WG_PP_SEQ_FOR_EACH_I( \
          WG_PP_LOCALOPERANDSYNTAXCHECK_MEMBERVARDLCN, \
          (varrootname)(objseq), \
          typeseq), \
        () BOOST_PP_EMPTY ) \
      () )

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_LOCALOPERANDSYNTAXCHECK_MEMBERVARDLCN( \
  r, varrootname_objseq, indx, type) \
    () \
    BOOST_PP_IIF( \
      WG_PP_TOKENS_STARTWITH_LOCAL(type), \
      WG_PP_LOCALOPERANDSYNTAXCHECK_MEMBERVARDLCN2, \
      WG_PP_MAP_TO_NOTHING3) (varrootname_objseq, indx, type) \
    BOOST_PP_EMPTY

#define WG_PP_LOCALOPERANDSYNTAXCHECK_MEMBERVARDLCN2( \
  varrootname_objseq, indx, type) \
    WG_PP_LOCALOPERANDSYNTAXCHECK_MEMBERVARDLCN3( \
      WG_PP_PARSEDTYPE_LOCALTYPE_OPERAND(type), \
      BOOST_PP_SEQ_ELEM( \
        indx, BOOST_PP_SEQ_ELEM(1, varrootname_objseq)), \
      BOOST_PP_SEQ_ELEM(0, varrootname_objseq), \
      indx)

#define WG_PP_LOCALOPERANDSYNTAXCHECK_MEMBERVARDLCN3( \
  localtype, objname, varrootname, indx) \
    typedef \
      localtype const & (* \
        WG_PP_ID_CAT(WG_PP_ID_CAT(varrootname, indx), objname) ) () ;

#endif /* WG_PP_LOCALOPERANDSYNTAXCHECK_HH_ */
