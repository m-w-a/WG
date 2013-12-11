#ifndef WG_PP_LOCALOPERANDSYNTAXCHECK_HH_
#define WG_PP_LOCALOPERANDSYNTAXCHECK_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/PP.hh>
#include <WG/Local/Detail/PP/Seq.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/TypeExtractor.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/SymbolTableUtil.hh>

//###########
//Public APIs
//###########

// Creates a noop struct for checking the syntax of local operands.
// This has to be done in the CodeGen phase since it's impossible to do in the
// front end without running into UB. Explicitly, one can't check for const or
// & usage in local(SomeType *) without having to concat '&' or '*'.
// Note that neither TMP techniques can be used for type checking since in
// C++03 local types may not be used as template parameters.
//
// symbtbl:
//   must have the following defined:
//     1) WG_PP_STUTIL_CALL_F2(TYPESEQ, <suffix>, symbtbl)
//     2) WG_PP_STUTIL_CALL_F2(OBJSEQ, <suffix>, symbtbl)
//   where suffix is declared in specseq.
//
// specseq:
//   { ( (suffix)(varrootname) ) }+
//
//   suffix:
//     The class of variables that if are locally typed then should be syntax
//     checked.
//   varrootname:
//     The root name of the variables to be used in the syntax checker.
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
    WG_PP_STUTIL_CALL_F2( \
      TYPESEQ, WG_PP_LOCALOPERANDSYNTAXCHECK_SPEC_SUFFIX(spec), symbtbl), \
    WG_PP_STUTIL_CALL_F2( \
      OBJSEQ, WG_PP_LOCALOPERANDSYNTAXCHECK_SPEC_SUFFIX(spec), symbtbl), \
    WG_PP_LOCALOPERANDSYNTAXCHECK_SPEC_VARROOTNAME(spec))

#define WG_PP_LOCALOPERANDSYNTAXCHECK_CNGRNCECLASS_MEMBERDCLN2( \
  typeseq, objseq, varrootname) \
    WG_PP_SEQ_NOTHING_FOR_EACH_I( \
      WG_PP_LOCALOPERANDSYNTAXCHECK_MEMBERVARDLCN, \
      (varrootname)(objseq), \
      typeseq )

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_LOCALOPERANDSYNTAXCHECK_MEMBERVARDLCN( \
  r, varrootname_objseq, indx, type) \
    BOOST_PP_IIF( \
      WG_PP_KEYWORDS_STARTSWITH_LOCAL(type), \
      WG_PP_LOCALOPERANDSYNTAXCHECK_MEMBERVARDLCN2, \
      WG_PP_MAPTO_NOTHING_ARG3) (varrootname_objseq, indx, type)

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
