#ifndef WG_PP_LOCALOPERANDSYNTAXCHECK_HH_
#define WG_PP_LOCALOPERANDSYNTAXCHECK_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP.hh>
#include <WG/Local/Detail/BackEnd/SymbolTable.hh>
#include <WG/Local/Detail/BackEnd/TypeExtractor.hh>

//###########
//Public APIs
//###########

// Creates a noop struct for checking the syntax of local operands.
// This has to be done in the CodeGen phase since it's impossible to do in the
// front end without running into UB. Explicitly, one can't check for const or
// & usage in local(SomeType *) without having to concat '&' or '*'.
#define WG_PP_LOCALOPERANDSYNTAXCHECK_DCLN(syntaxcheckername, symbtbl) \
  WG_PP_LOCALOPERANDSYNTAXCHECK_DCLN_IMPL(syntaxcheckername, symbtbl)

//###########
//Impl Macros
//###########

#define  WG_PP_LOCALOPERANDSYNTAXCHECK_EXPAND1(x) x

#define WG_PP_LOCALOPERANDSYNTAXCHECK_ROOTNAME_ASSIGNEE() assignee
#define WG_PP_LOCALOPERANDSYNTAXCHECK_ROOTNAME_BOUNDPARAM() boundparam
#define WG_PP_LOCALOPERANDSYNTAXCHECK_ROOTNAME_SETPARAM() setparam
#define WG_PP_LOCALOPERANDSYNTAXCHECK_ROOTNAME_BOUNDMEM() boundmem
#define WG_PP_LOCALOPERANDSYNTAXCHECK_ROOTNAME_SETMEM() setmem

// TODO: Add boundmem/setmem
#define WG_PP_LOCALOPERANDSYNTAXCHECK_DCLN_IMPL(syntaxcheckername, symbtbl) \
  struct syntaxcheckername \
  { \
    WG_PP_LOCALOPERANDSYNTAXCHECK_CNGRNCECLASS_MEMBERDCLN(ASSIGNEE, symbtbl) \
    WG_PP_LOCALOPERANDSYNTAXCHECK_CNGRNCECLASS_MEMBERDCLN(BOUNDPARAM, symbtbl) \
    WG_PP_LOCALOPERANDSYNTAXCHECK_CNGRNCECLASS_MEMBERDCLN(SETPARAM, symbtbl) \
  };

#define WG_PP_LOCALOPERANDSYNTAXCHECK_CNGRNCECLASS_MEMBERDCLN(suffix, symbtbl) \
  WG_PP_LOCALOPERANDSYNTAXCHECK_CNGRNCECLASS_MEMBERDCLN2( \
    BOOST_PP_CAT(WG_PP_SYMBOLTABLE_TYPESEQ_, suffix) (symbtbl), \
    BOOST_PP_CAT(WG_PP_SYMBOLTABLE_OBJSEQ_, suffix) (symbtbl), \
    BOOST_PP_CAT(WG_PP_LOCALOPERANDSYNTAXCHECK_ROOTNAME_, suffix))

#define WG_PP_LOCALOPERANDSYNTAXCHECK_CNGRNCECLASS_MEMBERDCLN2( \
  typeseq, objseq, varrootname) \
    WG_PP_LOCALOPERANDSYNTAXCHECK_EXPAND1( \
      BOOST_PP_EMPTY \
      WG_PP_SEQ_IFNIL_THENMAPTO( \
        WG_PP_SEQ_FOR_EACH_I(transform, (varrootname)(objseq), typeseq), \
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
    localtype const & \
      WG_PP_ID_CAT( \
        WG_PP_ID_CAT(WG_PP_ID_CAT(varrootname, indx), objname), \
        ERROR_local_operand_is_a_reference_or_is_const_qualified) ;

#endif /* WG_PP_LOCALOPERANDSYNTAXCHECK_HH_ */
