#ifndef WG_PP_FORWARDER_HH_
#define WG_PP_FORWARDER_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/PP.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/TypeExtractor.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/ID.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/SymbolTableUtil.hh>

//###########
//Public APIs
//###########

// Creates a class for forwarding captured variables and/or expressions.
// symbtbl:
//   must have:
//     1) WG_PP_STUTIL_CALL_F1(ISTPL, symbtbl, symbtbl)
//     2) WG_PP_STUTIL_CALL_F2(TYPESEQ, <suffix>, symbtbl, symbtbl)
//     3) WG_PP_STUTIL_CALL_F2(OBJSEQ, <suffix>, symbtbl, symbtbl)
//     4) WG_PP_STUTIL_CALL_F2(VALUESEQ, <suffix>, symbtbl, symbtbl)
//     5) WG_PP_STUTIL_CALL_F1(TOTAL_XXX_SIZE, symbtbl, symbtbl)
//     6) and when necessary,
//       WG_PP_STUTIL_CALL_F2(OBJSEQ_THISU_MARKER, <suffix>, symbtbl, symbtbl)
//   Where suffix is declared in specseq.
// specseq:
//   { ( (suffix)(forwarding_type)(varrootname)(thisu_policy) ) }+
//
//   forwarding_type:
//     one of {REF, CONSTREF}
//     determines whether the variable will be forwarded by ref or const ref.
//   varrootname:
//     the root name of the congruence class of variables being forwarded.
//   thisu_policy:
//     one of {REPLACETHISU, DONOTREPLACETHISU}
//     if REPLACETHISU is chosen, then there must be a corresponding
//     WG_PP_STUTIL_CALL_F2(OBJSEQ_THISU_MARKER, <suffix>, symbtbl, symbtbl)
#define WG_PP_FORWARDER_DCLN( \
  frwdr_typename, frwdr_objname, symbtbl, specseq) \
    WG_PP_FORWARDER_DCLN_IMPL(frwdr_typename, frwdr_objname, symbtbl, specseq)

// Expands to { BOOST_PP_NIL | { (ACCESSOR_INDX0)(ACCESSOR_INDX1) }+ }
// frwdr_objname:
//   same as that pass in to WG_PP_FORWARDER_DCLN.
// spec:
//   an element of specseq as defined in WG_PP_FORWARDER_DCLN.
#define WG_PP_FORWARDER_ACCESSORWGSEQ(frwdr_objname, varrootname, count) \
  WG_PP_FORWARDER_ACCESSORWGSEQ_IMPL(frwdr_objname, varrootname, count)

#define WG_PP_FORWARDER_ACCESSOR(frwdr_objname, varrootname, indx) \
  frwdr_objname.WG_PP_FORWARDER_TYPE_ACCESSORNAME(varrootname, indx) ()

#define WG_PP_FORWARDER_SPEC_SUFFIX(spec) BOOST_PP_SEQ_ELEM(0, spec)
#define WG_PP_FORWARDER_SPEC_FORWARDINGTYPE(spec) BOOST_PP_SEQ_ELEM(1, spec)
#define WG_PP_FORWARDER_SPEC_VARROOTNAME(spec) BOOST_PP_SEQ_ELEM(2, spec)
#define WG_PP_FORWARDER_SPEC_THISUPOLICY(spec) BOOST_PP_SEQ_ELEM(3, spec)

//###########
//Impl Macros
//###########

#define WG_PP_FORWARDER_DCLN_IMPL( \
  frwdr_typename, frwdr_objname, symbtbl, specseq) \
    struct frwdr_typename \
    { \
    private: \
      WG_PP_FORWARDER_TYPE_MEMBERDCLNS(symbtbl, specseq) \
    public: \
      WG_PP_FORWARDER_TYPE_CTOR_DCLN(frwdr_typename, symbtbl, specseq) \
      WG_PP_FORWARDER_TYPE_ACCESSORS(symbtbl, specseq) \
    }; \
    frwdr_typename const & frwdr_objname = \
      frwdr_typename \
      BOOST_PP_LPAREN() \
        WG_PP_FORWARDER_OBJ_INITLIST(symbtbl, specseq) \
      BOOST_PP_RPAREN() ;

//-----------------------------
//WG_PP_FORWARDER_ACCESSORWGSEQ
//-----------------------------

#define WG_PP_FORWARDER_ACCESSORWGSEQ_IMPL( \
  frwdr_objname, varrootname, count) \
    BOOST_PP_IF( \
      count, \
      WG_PP_FORWARDER_ACCESSORWGSEQ_IMPL1, \
      WG_PP_FORWARDER_ACCESSORWGSEQ_IMPL0) \
    (frwdr_objname, varrootname, count)

#define WG_PP_FORWARDER_ACCESSORWGSEQ_IMPL0( \
  frwdr_objname, varrootname, count) \
    BOOST_PP_NIL
#define WG_PP_FORWARDER_ACCESSORWGSEQ_IMPL1( \
  frwdr_objname, varrootname, count) \
    BOOST_PP_REPEAT( \
      count, \
      WG_PP_FORWARDER_ACCESSOR_TUPLIZE, \
      (frwdr_objname)(varrootname) )

// BOOST_PP_REPEAT functor.
// access_seq: (frwdr_objname)(varrootname)
#define WG_PP_FORWARDER_ACCESSOR_TUPLIZE(z, indx, access_seq) \
  ( BOOST_PP_SEQ_ELEM(0, access_seq) . \
    WG_PP_FORWARDER_TYPE_ACCESSORNAME( \
      BOOST_PP_SEQ_ELEM(1, access_seq), indx) () )

//------------
//Common Utils
//------------

#define WG_PP_FORWARDER_TYPE_MEMBERVARNAME(rootname, indx) \
  BOOST_PP_CAT(rootname, indx)

#define WG_PP_FORWARDER_TYPE_ACCESSORNAME(varrootname, indx) \
  BOOST_PP_CAT( \
    WG_PP_ID_CAT(get, varrootname), \
    indx)

#define WG_PP_FORWARDER_EXPAND1(x) x

#define WG_PP_FORWARDER_TYPE_MEMBERTYPE_FWDBYREF(e_or_d_type, istpl) \
  WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDREFERENCE(e_or_d_type, istpl)

#define WG_PP_FORWARDER_TYPE_MEMBERTYPE_FWDBYCONSTREF(e_or_d_type, istpl) \
  WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDCONSTADDREFERENCE(e_or_d_type, istpl)

//-------------------------------------------
//WG_PP_FORWARDER_TYPE_MEMBER_COMMONTRANSFORM
//-------------------------------------------

// ref_transform:
// constref_transform:
//   a WG_PP_SEQ_FOR_EACH_I that will be passed the following params:
//     data: use WG_PP_FORWARDER_TYPE_MEMBER_COMMONTRANSFORM_<...>
//     elem: explicit_or_deduced_type
#define WG_PP_FORWARDER_TYPE_MEMBER_COMMONTRANSFORM( \
  symbtbl, specseq, ref_transform, constref_transform) \
    BOOST_PP_SEQ_FOR_EACH( \
      WG_PP_FORWARDER_TYPE_MEMBER_TRANSFORM_SPEC, \
      (symbtbl)(ref_transform)(constref_transform), \
      specseq)
#define WG_PP_FORWARDER_TYPE_MEMBER_COMMONTRANSFORM_VARROOTNAME(data) \
  BOOST_PP_SEQ_ELEM(0, data)
#define WG_PP_FORWARDER_TYPE_MEMBER_COMMONTRANSFORM_ISTPL(data) \
  BOOST_PP_SEQ_ELEM(1, data)

#define WG_PP_FORWARDER_TYPE_MEMBER_TRANSFORM_SPEC_DATA_SYMBTBL(data) \
  BOOST_PP_SEQ_ELEM(0, data)
#define WG_PP_FORWARDER_TYPE_MEMBER_TRANSFORM_SPEC_DATA_TRANSFORM(data, spec) \
  BOOST_PP_CAT( \
    WG_PP_FORWARDER_TYPE_MEMBER_TRANSFORM_SPEC_DATA_TRANSFORM_, \
    WG_PP_FORWARDER_SPEC_FORWARDINGTYPE(spec)) (data)
#define WG_PP_FORWARDER_TYPE_MEMBER_TRANSFORM_SPEC_DATA_TRANSFORM_REF(data) \
  BOOST_PP_SEQ_ELEM(1, data)
#define WG_PP_FORWARDER_TYPE_MEMBER_TRANSFORM_SPEC_DATA_TRANSFORM_CONSTREF(data) \
  BOOST_PP_SEQ_ELEM(2, data)

// BOOST_PP_SEQ_FOR_EACH functor.
#define WG_PP_FORWARDER_TYPE_MEMBER_TRANSFORM_SPEC(r, data, spec) \
  WG_PP_FORWARDER_TYPE_CNGRNCECLASS_MEMBER_TRANSFORM( \
    WG_PP_FORWARDER_SPEC_SUFFIX(spec), \
    WG_PP_FORWARDER_TYPE_MEMBER_TRANSFORM_SPEC_DATA_TRANSFORM(data, spec), \
    WG_PP_FORWARDER_SPEC_VARROOTNAME(spec), \
    WG_PP_FORWARDER_TYPE_MEMBER_TRANSFORM_SPEC_DATA_SYMBTBL(data))

#define WG_PP_FORWARDER_TYPE_CNGRNCECLASS_MEMBER_TRANSFORM( \
  suffix, transform, varrootname, symbtbl) \
    WG_PP_SEQ_NOTHING_FOR_EACH_I( \
      transform, \
      (varrootname)( WG_PP_STUTIL_CALL_F1(ISTPL, symbtbl, symbtbl) ), \
      WG_PP_STUTIL_CALL_F2(TYPESEQ, suffix, symbtbl, symbtbl) )

//-----------
//MemberDclns
//-----------

#define WG_PP_FORWARDER_TYPE_MEMBERDCLNS(symbtbl, specseq) \
  WG_PP_FORWARDER_TYPE_MEMBER_COMMONTRANSFORM( \
    symbtbl, \
    specseq, \
    WG_PP_FORWARDER_TYPE_MEMBERDCLN_REF, \
    WG_PP_FORWARDER_TYPE_MEMBERDCLN_CONSTREF)

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_FORWARDER_TYPE_MEMBERDCLN_REF( \
  r, data, indx, e_or_d_type) \
    WG_PP_FORWARDER_TYPE_MEMBERTYPE_FWDBYREF( \
      e_or_d_type, \
      WG_PP_FORWARDER_TYPE_MEMBER_COMMONTRANSFORM_ISTPL(data)) \
    WG_PP_FORWARDER_TYPE_MEMBERVARNAME( \
      WG_PP_FORWARDER_TYPE_MEMBER_COMMONTRANSFORM_VARROOTNAME(data), indx) ;

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_FORWARDER_TYPE_MEMBERDCLN_CONSTREF( \
  r, data, indx, e_or_d_type) \
    WG_PP_FORWARDER_TYPE_MEMBERTYPE_FWDBYCONSTREF( \
      e_or_d_type, \
      WG_PP_FORWARDER_TYPE_MEMBER_COMMONTRANSFORM_ISTPL(data)) \
    WG_PP_FORWARDER_TYPE_MEMBERVARNAME( \
      WG_PP_FORWARDER_TYPE_MEMBER_COMMONTRANSFORM_VARROOTNAME(data), indx) ;

//----------
//Ctor Utils
//----------

#define WG_PP_FORWARDER_TYPE_CTOR_PARAMVARNAME(varrootname, indx) \
  BOOST_PP_CAT( \
    WG_PP_ID_CAT(param, varrootname), \
    indx)

//----------
//Ctor Dcln
//----------

#define WG_PP_FORWARDER_TYPE_CTOR_DCLN(frwdr_typename, symbtbl, specseq) \
  frwdr_typename \
    BOOST_PP_LPAREN() \
      WG_PP_FORWARDER_TYPE_CTOR_PARAMLIST(symbtbl, specseq) \
    BOOST_PP_RPAREN() \
    WG_PP_FORWARDER_TYPE_CTOR_INITLIST(symbtbl, specseq) \
    {}

//---------------
//Ctor Param List
//---------------

#define WG_PP_FORWARDER_TYPE_CTOR_PARAMLIST(symbtbl, specseq) \
  BOOST_PP_IF( \
    WG_PP_STUTIL_CALL_F1(TOTALXXX_SIZE, symbtbl, symbtbl), \
    WG_PP_SEQ_ENUM, \
    WG_PP_MAPTO_NOTHING_ARG1) \
      ( \
        WG_PP_FORWARDER_TYPE_MEMBER_COMMONTRANSFORM( \
          symbtbl, \
          specseq, \
          WG_PP_FORWARDER_TYPE_CTOR_PARAMLIST_ENTRY_REF, \
          WG_PP_FORWARDER_TYPE_CTOR_PARAMLIST_ENTRY_CONSTREF) \
      )

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_FORWARDER_TYPE_CTOR_PARAMLIST_ENTRY_REF( \
  r, data, indx, e_or_d_type) \
    BOOST_PP_LPAREN() \
      WG_PP_FORWARDER_TYPE_MEMBERTYPE_FWDBYREF( \
        e_or_d_type, \
        WG_PP_FORWARDER_TYPE_MEMBER_COMMONTRANSFORM_ISTPL(data)) \
      WG_PP_FORWARDER_TYPE_CTOR_PARAMVARNAME( \
        WG_PP_FORWARDER_TYPE_MEMBER_COMMONTRANSFORM_VARROOTNAME(data), indx) \
    BOOST_PP_RPAREN()

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_FORWARDER_TYPE_CTOR_PARAMLIST_ENTRY_CONSTREF( \
  r, data, indx, e_or_d_type) \
    BOOST_PP_LPAREN() \
      WG_PP_FORWARDER_TYPE_MEMBERTYPE_FWDBYCONSTREF( \
        e_or_d_type, \
        WG_PP_FORWARDER_TYPE_MEMBER_COMMONTRANSFORM_ISTPL(data)) \
      WG_PP_FORWARDER_TYPE_CTOR_PARAMVARNAME( \
        WG_PP_FORWARDER_TYPE_MEMBER_COMMONTRANSFORM_VARROOTNAME(data), indx) \
    BOOST_PP_RPAREN()

//--------------
//Ctor Init List
//--------------

#define WG_PP_FORWARDER_TYPE_CTOR_INITLIST(symbtbl, specseq) \
  BOOST_PP_IF( \
    WG_PP_STUTIL_CALL_F1(TOTALXXX_SIZE, symbtbl, symbtbl), \
    WG_PP_IDENTITY_ARG1(:) WG_PP_SEQ_ENUM, \
    WG_PP_MAPTO_NOTHING_ARG1) \
      ( \
        WG_PP_FORWARDER_TYPE_MEMBER_COMMONTRANSFORM( \
          symbtbl, \
          specseq, \
          WG_PP_FORWARDER_TYPE_CTOR_INITLISTENTRY, \
          WG_PP_FORWARDER_TYPE_CTOR_INITLISTENTRY) \
      )

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_FORWARDER_TYPE_CTOR_INITLISTENTRY( \
  r, data, indx, ignore_elem) \
    BOOST_PP_LPAREN() \
      WG_PP_FORWARDER_TYPE_MEMBERVARNAME( \
        WG_PP_FORWARDER_TYPE_MEMBER_COMMONTRANSFORM_VARROOTNAME(data), indx) \
      BOOST_PP_LPAREN() \
        WG_PP_FORWARDER_TYPE_CTOR_PARAMVARNAME( \
          WG_PP_FORWARDER_TYPE_MEMBER_COMMONTRANSFORM_VARROOTNAME(data), indx) \
      BOOST_PP_RPAREN() \
    BOOST_PP_RPAREN()

//---------
//Accessors
//---------

#define WG_PP_FORWARDER_TYPE_ACCESSORS(symbtbl, specseq) \
  WG_PP_FORWARDER_TYPE_MEMBER_COMMONTRANSFORM( \
    symbtbl, \
    specseq, \
    WG_PP_FORWARDER_TYPE_ACCESSORDCLN_REF, \
    WG_PP_FORWARDER_TYPE_ACCESSORDCLN_CONSTREF)

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_FORWARDER_TYPE_ACCESSORDCLN_REF( \
  r, data, indx, e_or_d_type) \
    WG_PP_FORWARDER_TYPE_MEMBERTYPE_FWDBYREF( \
      e_or_d_type, \
      WG_PP_FORWARDER_TYPE_MEMBER_COMMONTRANSFORM_ISTPL(data)) \
    WG_PP_FORWARDER_TYPE_ACCESSORDCLN_SIGANDBODY( \
      WG_PP_FORWARDER_TYPE_MEMBER_COMMONTRANSFORM_VARROOTNAME(data), indx)

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_FORWARDER_TYPE_ACCESSORDCLN_CONSTREF( \
  r, data, indx, e_or_d_type) \
    WG_PP_FORWARDER_TYPE_MEMBERTYPE_FWDBYCONSTREF( \
      e_or_d_type, \
      WG_PP_FORWARDER_TYPE_MEMBER_COMMONTRANSFORM_ISTPL(data)) \
    WG_PP_FORWARDER_TYPE_ACCESSORDCLN_SIGANDBODY( \
      WG_PP_FORWARDER_TYPE_MEMBER_COMMONTRANSFORM_VARROOTNAME(data), indx)

#define WG_PP_FORWARDER_TYPE_ACCESSORDCLN_SIGANDBODY( \
  varrootname, indx) \
    WG_PP_FORWARDER_TYPE_ACCESSORNAME(varrootname,indx) () const \
    { \
      return WG_PP_FORWARDER_TYPE_MEMBERVARNAME(varrootname,indx); \
    }

//-------------
//Obj Init List
//-------------

#define WG_PP_FORWARDER_OBJ_INITLIST(symbtbl, specseq) \
  WG_PP_SEQ_ENUM( \
    WG_PP_FORWARDER_EXPAND1( \
      BOOST_PP_CAT(WG_PP_SEQ_JOIN_ARG, WG_PP_SEQ_SIZE(specseq)) \
      BOOST_PP_LPAREN() \
        BOOST_PP_SEQ_ENUM( \
          BOOST_PP_SEQ_FOR_EACH( \
            WG_PP_FORWARDER_OBJ_INITLIST_SEQ, symbtbl, specseq) ) \
      BOOST_PP_RPAREN() \
    ))

// BOOST_PP_SEQ_FOR_EACH functor.
#define WG_PP_FORWARDER_OBJ_INITLIST_SEQ(r, symbtbl, spec) \
  ( \
    BOOST_PP_CAT( \
      WG_PP_FORWARDER_OBJ_INITLIST_SEQ_, \
      WG_PP_FORWARDER_SPEC_THISUPOLICY(spec)) (symbtbl, spec) \
  )

#define WG_PP_FORWARDER_OBJ_INITLIST_SEQ_REPLACETHISU(symbtbl, spec) \
  WG_PP_SEQ_REPLACE( \
    WG_PP_STUTIL_CALL_F2( \
      OBJSEQ, WG_PP_FORWARDER_SPEC_SUFFIX(spec), symbtbl, symbtbl), \
    WG_PP_STUTIL_CALL_F2( \
      OBJSEQ_THISU_MARKER, WG_PP_FORWARDER_SPEC_SUFFIX(spec), symbtbl, symbtbl), \
    this)

#define WG_PP_FORWARDER_OBJ_INITLIST_SEQ_DONOTREPLACETHISU(symbtbl, spec) \
  WG_PP_STUTIL_CALL_F2( \
    VALUESEQ, WG_PP_FORWARDER_SPEC_SUFFIX(spec), symbtbl, symbtbl)

#endif /* WG_PP_FORWARDER_HH_ */
