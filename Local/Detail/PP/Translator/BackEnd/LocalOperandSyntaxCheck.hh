#ifndef WG_PP_LOCALOPERANDSYNTAXCHECK_HH_
#define WG_PP_LOCALOPERANDSYNTAXCHECK_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/PP.hh>
#include <WG/Local/Detail/PP/Seq.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/TypeExtractor.hh>

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
// specseq:
//   { ( (varrootname)(getdclnsmacro)(gettypemacro)(getobjmacro) ) }+
//
//   varrootname:
//     The root name of the variables to be used in the syntax checker.
//   getdclnsmacro:
//     A one arg macro that when applied to symbtbl expands to a sequence of
//     dclnS whose types, if they are local, should be syntax checked.
//   gettypemacro:
//     A one arg macro that when applied to an element of getdclnsmacro(symbtbl)
//     expands to the type associated with that sequence.
//   getobjmacro:
//     A one arg macro that when applied to an element of getdclnsmacro(symbtbl)
//     expands to the obj associated with that sequence.
#define WG_PP_LOCALOPERANDSYNTAXCHECK_DCLN(syntaxcheckername, symbtbl, specseq) \
  WG_PP_LOCALOPERANDSYNTAXCHECK_DCLN_IMPL(syntaxcheckername, symbtbl, specseq)

//###########
//Impl Macros
//###########

//-----
//Utils
//-----

#define  WG_PP_LOCALOPERANDSYNTAXCHECK_EXPAND1(x) x

#define WG_PP_LOCALOPERANDSYNTAXCHECK_SPEC_VARROOTNAME(spec) \
  BOOST_PP_SEQ_ELEM(0, spec)
#define WG_PP_LOCALOPERANDSYNTAXCHECK_SPEC_GETDCLNSMACRO(spec) \
  BOOST_PP_SEQ_ELEM(1, spec)
#define WG_PP_LOCALOPERANDSYNTAXCHECK_SPEC_GETTYPEMACRO(spec) \
  BOOST_PP_SEQ_ELEM(2, spec)
#define WG_PP_LOCALOPERANDSYNTAXCHECK_SPEC_GETOBJMACRO(spec) \
  BOOST_PP_SEQ_ELEM(3, spec)

//----------------------------------
//WG_PP_LOCALOPERANDSYNTAXCHECK_DCLN
//----------------------------------

#define WG_PP_LOCALOPERANDSYNTAXCHECK_DCLN_IMPL( \
  syntaxcheckername, symbtbl, specseq) \
    WG_PP_LOCALOPERANDSYNTAXCHECK_DCLN_IMPL2( \
      syntaxcheckername, \
      ( BOOST_PP_NIL ) \
      WG_PP_LOCALOPERANDSYNTAXCHECK_SYNTAXCHECKSEQ(symbtbl, specseq) )

#define WG_PP_LOCALOPERANDSYNTAXCHECK_DCLN_IMPL2( \
  syntaxcheckername, syntaxcheckseq) \
    BOOST_PP_IF( \
      BOOST_PP_GREATER(WG_PP_SEQ_SIZE(syntaxcheckseq), 1), \
      WG_PP_LOCALOPERANDSYNTAXCHECK_SYNTAXCHECKER, \
      WG_PP_MAPTO_NOTHING_ARG2) (syntaxcheckername, syntaxcheckseq)

#define WG_PP_LOCALOPERANDSYNTAXCHECK_SYNTAXCHECKER( \
  syntaxcheckername, syntaxcheckseq) \
    { /* Put it in its own scope to help optimize it out as dead code. */ \
      struct syntaxcheckername \
      { \
        WG_PP_SEQ_FLATTEN(BOOST_PP_SEQ_TAIL(syntaxcheckseq)) \
      }; \
    }

//--------------------------------------------
//WG_PP_LOCALOPERANDSYNTAXCHECK_SYNTAXCHECKSEQ
//--------------------------------------------

#define WG_PP_LOCALOPERANDSYNTAXCHECK_SYNTAXCHECKSEQ(symbtbl, specseq) \
  BOOST_PP_SEQ_FOR_EACH( \
    WG_PP_LOCALOPERANDSYNTAXCHECK_CNGRNCECLASS_MEMBERDCLN, \
    symbtbl, \
    specseq)

// BOOST_PP_SEQ_FOR_EACH functor.
#define WG_PP_LOCALOPERANDSYNTAXCHECK_CNGRNCECLASS_MEMBERDCLN(r, symbtbl, spec) \
  WG_PP_LOCALOPERANDSYNTAXCHECK_CNGRNCECLASS_MEMBERDCLN2( \
    WG_PP_LOCALOPERANDSYNTAXCHECK_SPEC_GETDCLNSMACRO(spec) (symbtbl), \
    WG_PP_LOCALOPERANDSYNTAXCHECK_SPEC_VARROOTNAME(spec), \
    WG_PP_LOCALOPERANDSYNTAXCHECK_SPEC_GETTYPEMACRO(spec), \
    WG_PP_LOCALOPERANDSYNTAXCHECK_SPEC_GETOBJMACRO(spec) )

#define WG_PP_LOCALOPERANDSYNTAXCHECK_CNGRNCECLASS_MEMBERDCLN2( \
  dclnseq, gettypemacro, getobjmacro, varrootname) \
    WG_PP_SEQ_NOTHING_FOR_EACH_I( \
      WG_PP_LOCALOPERANDSYNTAXCHECK_MEMBERVARDLCN, \
      (varrootname)(gettypemacro)(getobjmacro), \
      dclnseq )

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_LOCALOPERANDSYNTAXCHECK_MEMBERVARDLCN( \
  r, varrootname_gettypemacro_getobjmacro, indx, dcln) \
    WG_PP_LOCALOPERANDSYNTAXCHECK_MEMBERVARDLCN2( \
      BOOST_PP_SEQ_ELEM(0, varrootname_gettypemacro_getobjmacro), \
      BOOST_PP_SEQ_ELEM(1, varrootname_gettypemacro_getobjmacro), \
      BOOST_PP_SEQ_ELEM(2, varrootname_gettypemacro_getobjmacro), \
      indx, \
      dcln)

#define WG_PP_LOCALOPERANDSYNTAXCHECK_MEMBERVARDLCN2( \
  varrootname, gettypemacro, getobjmacro, indx, dcln)
    BOOST_PP_IIF( \
      WG_PP_KEYWORDS_STARTSWITH_LOCAL( gettypemacro(dcln) ), \
      WG_PP_LOCALOPERANDSYNTAXCHECK_MEMBERVARDLCN3, \
      WG_PP_MAPTO_NOTHING_ARG5) \
    (varrootname, gettypemacro, getobjmacro, indx, dcln)

#define WG_PP_LOCALOPERANDSYNTAXCHECK_MEMBERVARDLCN3( \
  varrootname, gettypemacro, getobjmacro, indx, dcln) \
    WG_PP_LOCALOPERANDSYNTAXCHECK_MEMBERVARDLCN4( \
      /* NOTE: we're only interested in the operand of the local specifier.*/ \
      /* This is because we want to test that no const or & appears alongside*/ \
      /* that operand*/ \
      WG_PP_PARSEDTYPE_LOCALTYPE_OPERAND( gettypemacro(dcln) ), \
      getobjmacro(dcln), \
      varrootname, \
      indx)

#define WG_PP_LOCALOPERANDSYNTAXCHECK_MEMBERVARDLCN4( \
  localtype, objname, varrootname, indx) \
    ( \
      typedef \
        localtype const & (*objname) () ; \
    )

#endif /* WG_PP_LOCALOPERANDSYNTAXCHECK_HH_ */
